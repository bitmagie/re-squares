type t = (int, int);


type checked = 
| Valid(t)
| Invalid
;


let checkRange = (dim, p) => {
    let (i, j) = p;
    (i >= dim || i < 0 || j >= dim || j < 0)
    ? Invalid:Valid((i,j));
};

let add = (v1, v2) => {
  let (i1, j1) = v1;
  let (i2, j2) = v2;

  (i1 + i2, j1 + j2);
};

let subtract = (v2, v1) => {
  let (i2, j2) = v2;
  let (i1, j1) = v1;

  (i2 - i1, j2 - j1);
};

let multiply = (v2, v1) => {
  let (i2, j2) = v2;
  let (i1, j1) = v1;

  i2 * i1 + j2 * j1;
};

let square = v => {
  let (i, j) = v;
  i * i + j * j;
};

let absComponents = v => {
  let (i, j) = v;
  (Js.Math.abs_int(i), Js.Math.abs_int(j));
};

let minComponents = v => {
  let (i, j) = v;
  Js.Math.min_int(i, j);
};

let maxComponents = v => {
  let (i, j) = v;
  Js.Math.max_int(i, j);
};

let equals = (v1, v2) => {
  let (i1, j1) = v1;
  let (i2, j2) = v2;

  i1 == i2 && j1 == j2;
};
