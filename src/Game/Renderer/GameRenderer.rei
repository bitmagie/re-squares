
type t;
type playerScore = | Human(int) | AI(int) | Ghost;

let init: (~position: Paper.Point.t, ~format: Layout.format) => t;
let getFieldCoordinatesFromMousePosition: (t, Paper.Point.t) => option((int, int));
let timeTick: t => unit;
let timeReset: t => unit;
let blink: (t, playerScore) => unit;
let addScore: (t, playerScore) => unit;
let setPiece: (t, Position.t , string) => unit;
let moveTick: (t) => unit;
let showResult: (t, SquarePattern.t, int) => unit;