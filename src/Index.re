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

// init board renderer
Paper.activateLayer(boardLayer);
let board = Board.make(~position=Paper.view.center, ~format);


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
   let action:GameLogic.action = switch(board -> Board.getFieldCoordinatesFromBoardPosition(event.point) ){
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
      Display.timeTick(~display=board.display);
      ();
    | t when t mod 30 == 0 =>   
      let playerScore:Display.playerScore = switch(state.currPlayer)  {
        | Human(_,score) => Human(score)
        | AI(_,score) => AI(score)
        | _ => Ghost
      };
      board.display -> Display.blink(playerScore);
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
                board -> Board.setPiece(position, color);
                board.display -> Display.timeReset;
                board.display -> Display.moveTick(~display=_);                

                let result = Game.findAllSquares(state,position);
                let action:GameLogic.action = if(List.length(result)>0){
                  `reduceResultList(result)
                }else{
                  GameLogic.(`togglePlayer);
                };
                {
                  ...state,                
                  action: action
                };     
              }
              | _ => {
                  ...state,                
                action: GameLogic.(`togglePlayer)
              }
            };
          }
          | _ => {
            ...state,                
            action: GameLogic.(`nothing)
          }
        };        
    }
    | `reduceResultList(result) =>           
      switch (int_of_float(event.count)) {                  
        | t when t mod 10 == 0 =>    
          switch(result){
            | [] => 
              {
                ...state, 
                action: GameLogic.(`togglePlayer)
              }
            | [square, ...restList] => 
               Paper.activateLayer(resultLayer);   
               board -> Board.showResult(square, List.length(result));  
              let playerScore:Display.playerScore = switch(state.currPlayer){         
                  | Human(color,_)=> Human(square.score)
                  | AI(color,_)  => AI(square.score)
                  | _ => Ghost
                };
                 
              Paper.activateLayer(boardLayer);             
              board.display -> Display.addScore(playerScore);

              {
                ...state, 
                action: GameLogic.(`reduceResultList(restList))
              };

          };
        | _ => state
    }
    | `showGameResult => {
      // TODO: display game result
      Js.log("*** showGameResult! ***");
      {
        ...state,
        action: GameLogic.(`nothing)
      };
    }
    | `aiNextStep(t) => if(t mod 120 == 0){            
        let move = state -> AI.getBestMove(ai.possibleMoves);
        let action = switch(move){
          |Some(move) => GameLogic.(`makeMove(move.position));
          | _ =>  GameLogic.(`showGameResult)
        };        
        {
          ...state,
          action: action
        };          
        }else{
          {
          ...state,
          action: GameLogic.(`aiNextStep(t+1))
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
        | AI(_,_) => GameLogic.(`aiNextStep(1))
        | _ => GameLogic.(`nothing)
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

