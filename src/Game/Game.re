open GameLogic;
type state = {
    dim: Layout.dim,
    human: player,
    ai: player, 
    currPlayer: player,
    board: fieldMatrix,
    patterns: listOfSquarePatterns,  
    result: searchResult,
    action: action,
  };
type t = {
  mutable state: state
};

type loop('event,'state) = ('event, 'state) => state;
type interAction('event,'state) = ('event, 'state) => state;

let setup = (~dim:int):t => {  
  {
    state: {
        dim,
        human:Human(Styles.humanColor,0),
        ai: AI(Styles.aiColor,0), 
        currPlayer: Ghost,   
        board: Array.make_matrix(dim, dim, Empty),
        patterns: SquarePattern.initSearchList(dim),
        result: [],
        action: `nothing,
    }
  };
};

let newGame = ( dim ):state => {    
    {
        dim,
        human:Human(Styles.humanColor,0),
        ai: AI(Styles.aiColor,0),    
        currPlayer: Ghost,
        board: Array.make_matrix(dim, dim, Empty),
        patterns: SquarePattern.initSearchList(dim),
        result: [],       
        action: `nothing,
    };
};

let incrementPlayerHiScore = (player, score) => {
    switch(player){
        |Human(color,hiScore) => Human(color,hiScore+score)
        |AI(color,hiScore) => AI(color,hiScore+score)
        |_ => Ghost
    };
};

let getOtherPlayer = (state, player) => {    
    switch(player){
        | Human(_,_) => state.ai
        | AI(_,_)  => state.human
        | _ => Ghost
    };
};

let makeMove = (state, position, color):checkedMove => {
    let p0 = state.dim->Position.checkRange(position);
    switch(p0){
       |Valid(position) => {
           let (i,j) = position; 
           
           switch(state.board[i][j]){
               |Empty =>              
                    state.board[i][j] = Occupied(color);
                    Valid(position);               
               | _ => Invalid
           };
       }
       | _ => Invalid
    };
}; 

let undoMove = (state, position):checkedMove => {
    let p0 = state.dim->Position.checkRange(position);
    switch(p0){
       |Valid(position) => {
           let (i,j) = position; 
           
           switch(state.board[i][j]){
               |Occupied(_) =>              
                    state.board[i][j] = Empty;
                    Valid(position);               
               | _ => Invalid
           };
       }
       | _ => Invalid
    };
}; 

let getFieldAtPosition = (board,position) =>{ 
    let (i,j) = position;    
    board[i][j];    
};

let patternCoversSquare = (board: fieldMatrix, pattern:SquarePattern.t ) => {    
    let getField = getFieldAtPosition(board);
    switch(getField(pattern.p0),getField(pattern.p1),getField(pattern.p2),getField(pattern.p3),){
        | (Occupied(color0),Occupied(color1),Occupied(color2),Occupied(color3))  when color1==color0 && color2==color0 && color3==color0 =>
            pattern
        |_=> SquarePattern.null()
    };
};

let findAllSquares = (state, position) => { 

   SquarePattern.findAllSquaresWithSameCorner(position, state.patterns, state.dim)
    |> List.map(patternCoversSquare(state.board))
    |> List.filter(SquarePattern.notNull)
};