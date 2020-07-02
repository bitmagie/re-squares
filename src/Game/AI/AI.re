
/**
 * AI debug
 * 
 * show the values of the heuristic calculation in the fields
 */
let debug = false;
// -----------------------------------------------------------

type aiValue = float;
type humanValue = float;



type move = {
  position: (int, int),
  weight: int,
 // mutable value: (aiValue,humanValue)
  mutable value: float
};

type t = {
  mutable possibleMoves: list(move),
};




/** 
 * Heuristic
 */
let rec calcFieldValue = (p0,state:Game.state, color, patterns:list(SquarePattern.t)) => switch(patterns) {
  | [] => 0.
  | [pattern, ...restList] =>         
   
     let square:SquarePattern.t = {
            p0: p0,
            p1: p0->Position.add(pattern.p1),
            p2: p0->Position.add(pattern.p2),
            p3: p0->Position.add(pattern.p3),
            score: pattern.score,
        };
        
    switch(state.dim->SquarePattern.checkRange(square)){
      | Valid(square)  => {
        
        let field1:Game.field = square.p1->
          Game.getFieldAtPosition(state.board,_); 
        let field2:Game.field = square.p2->
          Game.getFieldAtPosition(state.board,_); 
        let field3:Game.field = square.p3->
          Game.getFieldAtPosition(state.board,_); 
        switch(
          field1,
          field2,
          field3        
        ){
          | (Empty,Empty,Empty) => 0.001 *.float_of_int(pattern.score) *. 0.25             
          | (Occupied(color1),Empty,Empty ) 
          | (Empty, Occupied(color1),Empty ) 
          | (Empty,Empty,Occupied(color1) ) when color1==color => 0.01 *.float_of_int(pattern.score) *. 0.5
          | (Occupied(color1),Occupied(color2),Empty)
          | (Occupied(color1),Empty,Occupied(color2))
          | (Empty,Occupied(color1),Occupied(color2)) when color1==color && color2==color  => 0.1  *.float_of_int(pattern.score) *. 0.75
          | (Occupied(color1),Occupied(color2),Occupied(color3)) when color1==color && color2==color && color3==color  => 10. *. float_of_int(pattern.score)
          | (_,_,_) => 0.
        }              
      }
      |_ => 0.  
    } +. calcFieldValue(p0, state, color, restList);    
}; 

let rec calcFieldValuesForPossibleMoves = (possibleMoves:list(move) ,state:Game.state, aiColor, humanColor) => switch(possibleMoves){  
  | [] => []
  | [move, ...restList] => 
    move.value = calcFieldValue(move.position,state, humanColor, state.patterns)
                    +. calcFieldValue(move.position, state, aiColor, state.patterns);    
    [ move, ...calcFieldValuesForPossibleMoves(restList, state, aiColor, humanColor)];
};

let calcFieldValues = (possibleMoves:list(move) , state:Game.state) => switch(state.ai,state.human){
     | (AI(aiColor,_),Human(humanColor,_)) =>      
      calcFieldValuesForPossibleMoves(possibleMoves, state, aiColor, humanColor);
     | _ => possibleMoves
   };


let calcWeight = (dim: int, pos: (int, int)): int => {
  let (i, j) = pos;
  dim - 1 + i * (dim - i - 1) + j * (dim - j - 1);
};

/**
 * Move generator
 */

let calcPos = (dim, n) => {
  let i = n mod dim;
  let j = (n - i) / dim;
  (i, j);
};

let rec generateMoveList = (state:Game.state, n, k) =>
  if (k >= n) {
    [];
  } else {
    let position = state.dim->calcPos(k);
    let weight = state.dim->calcWeight(position);
    
    let value =  calcFieldValue(position,state, Styles.aiColor, state.patterns) 
              +. calcFieldValue(position,state, Styles.humanColor, state.patterns);
    
    [{position, weight, value}, ...generateMoveList(state, n, k + 1)];
  };

let makeMoveList = (state) =>{  
  generateMoveList(state, state.dim * state.dim, 0)
  ->List.sort(
        (mov1, mov2) =>
          if (mov1.value > mov2.value) {
            1;
          } else if (mov1.value < mov2.value) {
            (-1);
          } else {
            0;
          },
        _,
      )
  ->List.rev(_)
};

let posEquals = (pos: (int, int), otherPos: (int, int)) => {
  let (i, j) = pos;
  let (k, l) = otherPos;
  i == k && j == l;
};

let getMove = ai => {
    if(List.length(ai.possibleMoves)>0){
        Some(List.hd(ai.possibleMoves));
    }else{
        None;
    };
};

let dropFromMoveList = (possibleMoves, pos) => {
  List.filter(move => {        
        !posEquals(pos, move.position)
        }, possibleMoves);  
};

let make = (state:Game.state) => {
  {    
    possibleMoves:
      makeMoveList(state),
  };
};



let maxMove = (move1,move2) => {
    if(move1.value > move2.value){
      move1
    } else{
      move2
    };
};

let getBestMove = (state:Game.state,possibleMoves)  => { 
  //List.fold_left f a [b1; ...; bn] is f (... (f (f a b1) b2) ...) bn.

  let move = List.fold_left(maxMove, {
      position: (-1,-1),
      weight: -1,
      value:-1.
    }, possibleMoves);

    switch(Position.checkRange(state.dim, move.position)){
      |Valid(position) => Some(move)
      |_ => None
    };
};


/**
 * Min Max with alpha-beta-pruning
 */

