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


let removeResults = unit => {
  Paper.activateLayer(resultLayer);
  for (i in Array.length(resultLayer.children) - 1 downto 0) {
    Paper.Path.remove(resultLayer.children[i]);
  };
  ();
};

let overlayLayer = Paper.createLayer();

let overlayPathStyle = Styling.styleDescription(~fillColor="#ff0000", ());
let overlayPath =
  Paper.Point.create(0., 0.)
  ->Paper.Rectangle.createFromPoint(Paper.view.size)
  ->Paper.Path.rectangle(_, ())
  ->Paper.Path.setStyle(~path=_, ~style=overlayPathStyle);
overlayPath.opacity = 0.0;
overlayLayer.visible = false;

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


/** 
 *  init logic system  
 * 
 */

let game:Game.t = Game.setup(~dim=Layout.fieldsPerSide);
// per default, the human begins the game
game.state = {
  ...game.state,
  currPlayer: game.state.human
};

// humans counterpart
let ai = game.state -> AI.make;


/**
 * Event System
 * 
 */
// the graphics library tool event system is used for both, the render system and the logic system
let tool = Tool.create(); 

// the human player interaction with the game logic is driven by the graphics library's onMouseUp event 
let interAction:Game.interAction(ToolEvent.t, Game.state) = (event, state) => {   
   let action:Game.action = switch(renderer -> GameRenderer.getFieldCoordinatesFromMousePosition(event.point) ){
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

Tool.setOnMouseUp(tool, onMouseUpHandler);

// the game loop
let loop:Game.loop(ToolEvent.t, Game.state) = (event, state) => {  
  
  // game clock
  switch (int_of_float(event.count)) {
    | t when t mod 60 == 0 =>      
      GameRenderer.timeTick(renderer);
      ();
    | t when t mod 30 == 0 =>   
      let playerScore:GameRenderer.playerScore = switch(state.currPlayer)  {
        | Human(_,score) => Human(score)
        | AI(_,score) => AI(score)
        | _ => Ghost
      };
      renderer -> GameRenderer.blink(playerScore);
      ();       
    | _ => ()
    };
   
 switch(state.action){
    | `makeMove(position) => {
        switch(state.currPlayer){         
          | Human(color,_)
          | AI(color,_)  => {            
            switch(state -> Game.makeMove(position, color) ){
              | Valid(position) => {   
                removeResults();
                let possibleMoves = ai.possibleMoves -> AI.dropFromMoveList(position);
                ai.possibleMoves = possibleMoves;

                ai.possibleMoves->AI.calcFieldValues(state);
                
                Paper.activateLayer(boardLayer);                         
                renderer -> GameRenderer.setPiece(position, color);
                renderer -> GameRenderer.timeReset;
                renderer -> GameRenderer.moveTick;                

                let result = Game.findAllSquares(state,position);
                let action:Game.action = if(List.length(result)>0){
                  `reduceResultList(result)
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
    | `reduceResultList(result) =>           
      switch (int_of_float(event.count)) {                  
        | t when t mod 10 == 0 =>    
          switch(result){
            | [] => 
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
            
            | [square, ...restList] => 
               Paper.activateLayer(resultLayer);   
               renderer -> GameRenderer.showResult(square, List.length(result));  

              

              let human:Game.player = switch(state.currPlayer){         
                  | Human(color,score)=> {
                      Js.log2("human score = ", score + square.score);
                      Human(color,score + square.score);
                    }
                  | _ => state.human
                };
              let ai:Game.player = switch(state.currPlayer){                           
                  | AI(color,score)  => {
                    Js.log2("ai score = ", score + square.score);
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
              renderer -> GameRenderer.setScore(playerScore);

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

      let message = switch(winner){
          | Human(_, _) => "You win!"
          | AI(_, _) => "I win!"
          | _ => "?????????????"
      }
      
      Paper.activateLayer(overlayLayer);   
      overlayPath.opacity = 0.5;
      overlayLayer.visible = true; 
      renderer->GameRenderer.showGameResult( message);
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

// the game loop is driven by the 'onFrame' event of the renderer loop 
let onFrameHandler = (event: ToolEvent.t) => {
    game.state = event -> loop(game.state);
};

View.setOnFrame(Paper.view, onFrameHandler);

