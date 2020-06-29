/**
 * A position on the game board is a pair of integers
 * and some operations defined on it.
 *
 */

type t = (int, int);

type checked =
  | Valid(t)
  | Invalid;

let checkRange: (int, t) => checked;

let equals: ((int, int), (int, int)) => bool;

let add: ((int, int), (int, int)) => (int, int);
let subtract: ((int, int), (int, int)) => (int, int);
let multiply: ((int, int), (int, int)) => int;
let square: ((int, int)) => int;

let absComponents: ((int, int)) => (int, int);
let minComponents: ((int, int)) => int;
let maxComponents: ((int, int)) => int;
