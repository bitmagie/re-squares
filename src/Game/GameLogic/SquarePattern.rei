/**
 * Square pattern are both, abstract templates for recognizing 
 * squares on the game board, as well as the representations of 
 * concrete squares, after they have been recognized.
 */

type t = {
  p0: Position.t,
  p1: Position.t,
  p2: Position.t,
  p3: Position.t,
  score: int,
};

let null: (unit) => t;

let isNull: t => bool;
let notNull: t => bool;

type checked = 
| Valid(t)
| Invalid
;

let checkRange: (int, t) => checked;

let identicalWith: (t, t) => bool;
let calcScore: (Position.t, Position.t) => int;
let getScore: Position.t => int;
let isValid: t => bool;

let swapArrayElements: (array('a), int, int) => array('a);
let sortCorners: t => t;

let make: (Position.t, Position.t, Position.t) => t;

let initSearchList: int => list(t);

let findAllSquaresWithSameCorner: (Position.t, list(t), int) => list(t);