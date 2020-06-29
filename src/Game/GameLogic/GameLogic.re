type cssColor = Styling.cssColor;
type score = int;

type field= 
    | Occupied(cssColor)
    | Empty
    ;

type fieldMatrix = array(array(field));
   
type player =
    | Human(cssColor,score)
    | AI(cssColor,score)
    | Ghost
; 

type checkedMove = Position.checked;

type listOfSquarePatterns = list(SquarePattern.t);

type square = SquarePattern.t;

type searchResult = list(square);

type action = [
| `makeMove((int,int))
| `reduceResultList(list(square))
| `togglePlayer
| `aiNextStep(int)
| `showGameResult
| `nothing
];

let isFieldEmpty = (field) => {
    switch(field){
        |Empty => true
        |_ => false
    };
};

let getFieldColor = field => switch(field){
    | Occupied(color) => color
    | _ => ""
};
