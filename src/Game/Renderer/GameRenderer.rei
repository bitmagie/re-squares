
type t;
type playerScore = | Human(int) | AI(int) | Ghost;

let init: (~position: Paper.Point.t, ~format: Layout.format) => t;
let getFieldCoordinatesFromMousePosition: (t, Paper.Point.t) => option((int, int));
let getBoardPositionFromFieldCoordinates: (t, (int, int)) => option(Paper.Point.t); 
let timeTick: t => unit;
let timeReset: t => unit;
let blink: (t, playerScore) => unit;
let setScore: (t, playerScore) => unit;
let setPiece: (t, Position.t , string) => unit;
let moveTick: (t) => unit;
let showResult: (t, SquarePattern.t, int) => unit;
let showWinMessage: (t,string) => unit;
let removeAllHandlersFromPath: Paper.Path.t => unit;
