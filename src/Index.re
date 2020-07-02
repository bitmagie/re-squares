// Entry point

/** 
 * init game render engine
 * 
*/
let style = Paper.document##createElement("style");
    Paper.document##head##appendChild(style);
    style##innerHTML #= Styles.css;

Paper.setup("canvas");

Typography.setTextBaseline(`middle);

// define view layers
let boardLayer = Paper.project.activeLayer;
let aiLayer = Paper.createLayer();
let resultLayer = Paper.createLayer();

let overlayLayer = Paper.createLayer();
let overlayPath =
  Paper.Point.create(0., 0.)
  ->Paper.Rectangle.createFromPoint(Paper.view.size)
  ->Paper.Path.rectangle(_, ())
  ->Paper.Path.setStyle(~path=_, ~style=Styles.overlayPathStyle);
let messageLayer = Paper.createLayer();
let clearOverlay = unit => {
  Paper.activateLayer(overlayLayer);
  overlayPath.opacity = 0.0;
  overlayLayer.visible = false;
  for (i in Array.length(messageLayer.children) - 1 downto 0) {
    Paper.Path.remove(messageLayer.children[i]);
  };
  ();
};
clearOverlay();

// define view format
let (viewWidth, viewHeight) = (
  Paper.view.size.width,
  Paper.view.size.height,
);

let format: Layout.format =
  if (viewHeight <= viewWidth) {
    Landscape(viewWidth, viewHeight);
  } else {
    Portrait(viewWidth, viewHeight);
  };


// init renderer
Paper.activateLayer(boardLayer);
let renderer = GameRenderer.init(~position=Paper.view.center, ~format);


let removeBoard = unit => {
  Paper.activateLayer(boardLayer);
  for (i in Array.length(boardLayer.children) - 1 downto 0) {
    GameRenderer.removeAllHandlersFromPath(boardLayer.children[i]);
    Paper.Path.remove(boardLayer.children[i]);
  };
  ();
};
let removeResults = unit => {
  Paper.activateLayer(resultLayer);
  for (i in Array.length(resultLayer.children) - 1 downto 0) {
    Paper.Path.remove(resultLayer.children[i]);
  };
  ();
};


/** 
 *  init logic system 
 * 
 */

let game:Game.t = Game.setup(~dim=Layout.fieldsPerSide, ~renderer);


// per default, the human begins the game
game.firstMove = game.state.human;
game.state = {
  ...game.state,
  currPlayer: game.state.human
};

// humans counterpart
let ai = game.state -> AI.make;


// TODO: remove ai teststuff ----------------------------------------------
let setText = (position, content) => {  
  
  switch(game.renderer->GameRenderer.getBoardPositionFromFieldCoordinates(position)){
    | Some(point) => point
        ->PointText.pointTextDescription(
          ~point=_,
          ~fillColor="#999",
          ~fontSize=14.,
          ~fontWeight = "normal",
          ~content=content,            
          ~justification="center",
          (),
        )
        ->PointText.createFromObject(_);    
        ();  
    | _ =>{ 
        let (i,j) = position;      
        BasicTypes.Point.create(float_of_int(i),float_of_int(j))
        ->PointText.pointTextDescription(
          ~point=_,
          ~fillColor="#999",
          ~fontSize=14.,
          ~fontWeight = "normal",
          ~content=content,            
          ~justification="center",
          (),
        )
        ->PointText.createFromObject(_); 
        ();
      }      
  };
  
};
let setText2 = (position, content) => {  
  
  switch(game.renderer->GameRenderer.getBoardPositionFromFieldCoordinates(position)){
    | Some(point) => point
    -> BasicTypes.Point.addPoint(BasicTypes.Point.create(0.,34.))
        ->PointText.pointTextDescription(
          ~point=_,
          ~fillColor="#0df",
          ~fontSize=10.,
          ~fontWeight = "normal",
          ~content=content,            
          ~justification="center",
          (),
        )
        ->PointText.createFromObject(_);      
        ();
    | _ =>{ 
        let (i,j) = position;      
        BasicTypes.Point.create(float_of_int(i),float_of_int(j))
        -> BasicTypes.Point.addPoint(BasicTypes.Point.create(0.,34.))
        ->PointText.pointTextDescription(
          ~point=_,
          ~fillColor="#0df",
          ~fontSize=12.,
          ~fontWeight = "normal",
          ~content=content,            
          ~justification="center",
          (),
        )
        ->PointText.createFromObject(_); 
        ();
      }      
  };
  
};
let setText3 = (position, content) => {  
  
  switch(game.renderer->GameRenderer.getBoardPositionFromFieldCoordinates(position)){
    | Some(point) => point
    -> BasicTypes.Point.addPoint(BasicTypes.Point.create(0.,-34.))
        ->PointText.pointTextDescription(
          ~point=_,
          ~fillColor="#ff0",
          ~fontSize=10.,
          ~fontWeight = "normal",
          ~content=content,            
          ~justification="center",
          (),
        )
        ->PointText.createFromObject(_);      
        ();
    | _ =>{ 
        let (i,j) = position;      
        BasicTypes.Point.create(float_of_int(i),float_of_int(j))
        -> BasicTypes.Point.addPoint(BasicTypes.Point.create(0.,-34.))
        ->PointText.pointTextDescription(
          ~point=_,
          ~fillColor="#ff0",
          ~fontSize=12.,
          ~fontWeight = "normal",
          ~content=content,            
          ~justification="center",
          (),
        )
        ->PointText.createFromObject(_); 
        ();
      }      
  };
  
};

let rec showFieldValues = (board, moveList: list(AI.move)):unit => switch(moveList){
  | [move, ...restList] => {      
    
    setText3(move.position,  string_of_int(move.weight));
    setText(move.position,  string_of_float(move.value));

    showFieldValues(board,restList);
  }
  | [] => ()
}; 

let removeAiStuff = unit => {
  Paper.activateLayer(aiLayer);
  for (i in Array.length(aiLayer.children) - 1 downto 0) {
    Paper.Path.remove(aiLayer.children[i]);
  };
  ();
};
// ------------------------------------------------------------------------





/**
 * Event System
 * 
 */
// the graphics library tool event system is used for both, the render system and the logic system
let tool = Tool.create(); 

// the human player interaction with the game logic is driven by the graphics library's onMouseUp event 
let interAction:Game.interAction(ToolEvent.t, Game.state) = (event, state) => {   
   let action:Game.action = switch(game.renderer -> GameRenderer.getFieldCoordinatesFromMousePosition(event.point) ){
     |Some(position) => `makeMove(position)
     | _ => `nothing
   };
  {
    ...state,
    action:action 
  };
};

let onMouseUpHandler = (event: ToolEvent.t) => {
   game.state = event -> interAction(game.state);
};
let onNewGameHandler = (_event: ToolEvent.t) => {
   let state =  game.state;
   
   game.state = {
      ...state,
      action: Game.(`newGame)
   };
   ();
};

Tool.setOnMouseUp(tool, onMouseUpHandler);

// the game loop
let loop:Game.loop(ToolEvent.t, Game.state) = (event, state) => {  
  
  // game clock
  switch (int_of_float(event.count)) {
    | t when t mod 60 == 0 =>      
      GameRenderer.timeTick(game.renderer);
      ();
    | t when t mod 30 == 0 =>   
      let playerScore:GameRenderer.playerScore = switch(state.currPlayer)  {
        | Human(_,score) => Human(score)
        | AI(_,score) => AI(score)
        | _ => Ghost
      };
      game.renderer -> GameRenderer.blink(playerScore);
      ();       
    | _ => ()
    };
   
 switch(state.action){
   |`newGame => {

      if (Tool.responds("mouseup")) {            
            ();
           
             Tool.off("mouseup", onNewGameHandler);    
          } else {    
            ();    
          };  
           let currPlayer:Game.player = switch(game.firstMove){
            | Human(color,_) =>{             
               Human(color,0);
            }
            | AI(color,_)  => {              
              AI(color,0)
            }               
            | _ => Ghost
          };
          let firstMove:Game.player = switch(game.firstMove){
            | Human(color,_) =>{             
               AI(color,0);
            }
            | AI(color,_)  => {              
              Human(color,0)
            }               
            | _ => Ghost
          };

          game.firstMove = firstMove;
                               
          removeAiStuff();
          clearOverlay();
          removeResults();
          removeBoard();
          let newState = Game.newGame(Layout.fieldsPerSide);    
          ai.possibleMoves = AI.makeMoveList(newState);
          game.renderer = GameRenderer.init(~position=Paper.view.center, ~format);

      {
          ...newState,             
          currPlayer, 
                action: Game.(`togglePlayer)
              };    

   }
    | `makeMove(position) => {
        switch(state.currPlayer){         
          | Human(color,_)
          | AI(color,_)  => {            
            switch(state -> Game.makeMove(position, color) ){
              | Valid(position) => {   
                
                let possibleMoves = ai.possibleMoves -> AI.dropFromMoveList(position);
                ai.possibleMoves = possibleMoves;

                ai.possibleMoves->AI.calcFieldValues(state);

                if(AI.debug){                 
                  // TODO: remove ai teststuff -----
                    Paper.activateLayer(aiLayer);                         
                    removeAiStuff();
                    game.renderer -> showFieldValues(ai.possibleMoves);
                  //--------------------------------
                }else{
                  ();
                }  
                
                Paper.activateLayer(boardLayer);                         
                game.renderer -> GameRenderer.setPiece(position, color);
                game.renderer -> GameRenderer.timeReset;
                game.renderer -> GameRenderer.moveTick;                

                let result = Game.findAllSquares(state,position);
                let action:Game.action = if(List.length(result)>0){
                  Game.(`reduceResultList(result));
                }else{
                  Game.(`togglePlayer);
                };
                {
                  ...state,                
                  action: action
                };     
              }
              | _ => {
                  ...state,                
                action: Game.(`togglePlayer)
              }
            };
          }
          | _ => {
            ...state,                
            action: Game.(`nothing)
          }
        };        
    }
    | `showMoveResult(t) =>  if(t mod 75 == 0){ 
          removeResults();
              // let winner = Game.getWinner(state.human,state.ai); // arguments order doesn't matter
              let winner = Game.getWinner(state.ai,state.human);

              let action = switch(winner){
                | Ghost => Game.(`togglePlayer)
                | _ => Game.(`showGameResult(winner))
              };
          {
            ...state,
            action: action
          }
    
    }else{
          {
            ...state,
            action: Game.(`showMoveResult(t+1))
          }
    } 
    | `reduceResultList(result) =>           
      switch (int_of_float(event.count)) {                  
        | t when t mod 10 == 0 =>    
          switch(result){
            | [] => 
            
              {
                ...state, 
                action: Game.(`showMoveResult(1))
              }
            
            | [square, ...restList] => 
               Paper.activateLayer(resultLayer);   
               game.renderer -> GameRenderer.showResult(square, List.length(result));  

              

              let human:Game.player = switch(state.currPlayer){         
                  | Human(color,score)=> {                     
                      Human(color,score + square.score);
                    }
                  | _ => state.human
                };
              let ai:Game.player = switch(state.currPlayer){                           
                  | AI(color,score)  => {                 
                    AI(color,score + square.score);
                    }
                  | _ => state.ai
                };
                
              let currPlayer:Game.player = switch(state.currPlayer){         
                  | Human(color,score)=> human                           
                  | AI(color,score)=> ai
                  | _ => state.currPlayer
                };

              let playerScore:GameRenderer.playerScore = switch(currPlayer){         
                  | Human(_,score)=> Human(score)                  
                  | AI(_,score)  => AI(score)
                  | _ => Ghost
                };  
                 
              Paper.activateLayer(boardLayer);    
              
              game.renderer -> GameRenderer.setScore(playerScore);

              {
                ...state, 
                human,
                ai,
                currPlayer,
                action: Game.(`reduceResultList(restList))
              };

          };
        | _ => state
    }
    | `showGameResult(winner) => {
      // TODO: display game result

      let whoWins = switch(winner){
          | Human(_, _) => "You win!"
          | AI(_, _) => "I win!"
          | _ => "?????????????"
      }
       

      Paper.activateLayer(overlayLayer); 
      overlayPath.opacity = 0.8;
      overlayLayer.visible = true; 
      Paper.activateLayer(messageLayer);
      game.renderer->GameRenderer.showWinMessage( whoWins);
      
      if (Tool.responds("mouseup")) {            
            ();
             Tool.off("mouseup", onMouseUpHandler);    
          } else {    
            ();    
          };  
         
          Tool.on("mouseup", onNewGameHandler);    

      {
        ...state,
        action: Game.(`nothing)
      };
    }
    | `aiNextStep(t) => if(t mod 120 == 0){            
        let move = state -> AI.getBestMove(ai.possibleMoves);
        let action = switch(move){
          |Some(move) => Game.(`makeMove(move.position));
          | _ =>  Game.(`showGameResult(Game.(Ghost)))
        };        
        { 
          ...state,
          action: action
        };          
        }else{
          {
          ...state,
          action: Game.(`aiNextStep(t+1))
          }
        };
      
    | `togglePlayer => {
      
      let currPlayer = Game.getOtherPlayer(state, state.currPlayer);
      // disable or enable interaction mode for the human player
      switch(currPlayer){
        | Human(_,_) => 
          if (Tool.responds("mouseup")) {      
            ();
          } else {
            Tool.on("mouseup", onMouseUpHandler);
            overlayLayer.visible = false;
            ();    
          };
        | _ => if (Tool.responds("mouseup")) { 
            Tool.off("mouseup", onMouseUpHandler);
            overlayLayer.visible = true;     
            ();
          } else {        
            ();    
          };
      };
      let action = switch(currPlayer){
        | AI(_,_) => Game.(`aiNextStep(1))
        | _ => Game.(`nothing)
      };
      {
        ...state,
        currPlayer: currPlayer,
        action: action
      };
    }
    | _ => state
  };      
};

// the game loop is driven by the 'onFrame' event of the game.renderer loop 
let onFrameHandler = (event: ToolEvent.t) => {
    game.state = event -> loop(game.state);
};

View.setOnFrame(Paper.view, onFrameHandler);

