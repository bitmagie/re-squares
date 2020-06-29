type t = {
  p0: Position.t,
  p1: Position.t,
  p2: Position.t,
  p3: Position.t,
  score: int,
};

let sqr = a => a * a;
let add = (a, b) => a + b;
let div = (a, b) => a / b;
let bias = d => d < 1 ? 0 : d + 1;
let calcScore = (p0, p1) =>
  p0
  ->Position.subtract(p1)
  ->Position.absComponents
  ->Position.maxComponents
  ->bias
  ->sqr;

let getScore = p2 =>
  p2
  ->Position.absComponents
  ->Position.multiply((1, 1))
  ->div(2)
  ->add(1)
  ->sqr;

let swapArrayElements = (arr, i, j) => {
  let p = Array.copy(arr);
  let tmp = p[i];
  p[i] = p[j];
  p[j] = tmp;
  p;
};

let sortCorners = pattern => {
  let p = [|[|pattern.p0, pattern.p1, pattern.p2, pattern.p3|]|];

  // identify p0
  for (i in 0 to 3) {
    if (p[0][i]->Position.equals((0, 0))) {
      p[0] = p[0]->swapArrayElements(i, 0);
    } else {
      ();
    };
  };

  let d = [|
    p[0][1]->Position.square,
    p[0][2]->Position.square,
    p[0][3]->Position.square,
  |];

  // identify p2
  if (d[0] == d[1]) {
    p[0] = p[0]->swapArrayElements(3, 2);
  } else if (d[1] == d[2]) {
    p[0] = p[0]->swapArrayElements(1, 2);
  } else {
    ();
  };

  // identify p1
  let (x2, y2) = p[0][2];
  let (xa, ya) = p[0][1];
  let (xb, yb) = p[0][3];

  if
    (x2 <= 0
     && y2 > 0
     && xb == min(xa, xb)
     || x2 < 0
     && y2 == 0
     && yb == min(ya, yb)
     || x2 <= 0
     && y2 < 0
     && xb == max(xa, xb)
     || x2 > 0
     && yb == max(ya, yb)) // y2 doesn't matter
 {
    p[0] = p[0]->swapArrayElements(3, 1);
  } else {
    ();
  };

  // counter-clockwise ordered corners
  {p0: p[0][0], p1: p[0][1], p2: p[0][2], p3: p[0][3], score: pattern.score};
};
let isValid = pattern => {
  let test = sortCorners(pattern);

  // for a square pattern applies p0 == (0,0) and p2 = p1 + p3 and p1*p1 == p3*p3
  // and a correct calculated score

  test.p0->Position.equals((0, 0))
  && test.p1->Position.add(test.p3)->Position.equals(test.p2)
  && test.p1->Position.square == test.p3->Position.square
  && test.p0->Position.equals(pattern.p0)
  && test.p1->Position.equals(pattern.p1)
  && test.p2->Position.equals(pattern.p2)
  && test.p3->Position.equals(pattern.p3)
  && pattern.score == test.p0->calcScore(test.p1);
};

let identicalWith = (square, otherSquare) =>
  Position.equals(square.p0, otherSquare.p0)
  && Position.equals(square.p1, otherSquare.p1)
  && Position.equals(square.p2, otherSquare.p2)
  && Position.equals(square.p3, otherSquare.p3)
  && square.score == otherSquare.score;

let make = (p1, p2, p3) => {
  let p0 = (0, 0);
  {p0, p1, p2, p3, score: calcScore(p0, p1)};
};



let initSearchList = dim => {
        let q = 0;
        let _G = 1;
        let b = 2;
        let lauf = [|0, 0, 0|];
        let i1 = 0;
        let j1 = 1;
        let i2 = 2;
        let j2 = 3;
        let i3 = 4;
        let j3 = 5;
        let ij = [|0, 0, 0, 0, 0, 0|];
        let x1 = 0;
        let y1 = 1;
        let x2 = 2;
        let y2 = 3;
        let x3 = 4;
        let y3 = 5;
        let xy = [|0, 0, 0, 0, 0, 0|];

        let getScore = calcScore((0,0));

        let patterns = [|[||]|];

        for (n in 2 to dim) {

            ij[i1] = (-1);
            ij[j1] = (-1);
            ij[i2] = (-2);
            ij[j2] = 2;
            ij[i3] = (-1);
            ij[j3] = 1;

            lauf[_G] = n - 1;
            lauf[b] = 0;
            lauf[q] = 0;

            xy[x1] = lauf[_G];
            xy[y1] = 0;
            xy[x2] = lauf[_G];
            xy[y2] = - lauf[_G];
            xy[x3] = 0;
            xy[y3] = - lauf[_G];


            let pattern:t ={
                    p0:(0, 0),
                    p1:(xy[x1], xy[y1]),
                    p2: (xy[x2], xy[y2]),
                    p3: (xy[x3], xy[y3]),
                    score: getScore((xy[x1], xy[y1])),
                };
            
            patterns[0] =
            Array.append(
                patterns[0],
                [|pattern|],
            );
            for (m in 2 to 4 * (n - 1)) {
            xy[x1] = xy[x1] + ij[i1];
            xy[y1] = xy[y1] + ij[j1];
            xy[x3] = xy[x3] + ij[i3];
            xy[y3] = xy[y3] + ij[j3];

            lauf[q] = lauf[q] + 1;
            if (lauf[b] == 0) {
                xy[x2] = xy[x2] + ij[i2];
                ij[i2] = (
                if (Js.Math.abs_int(xy[x2]) == lauf[_G]) {
                    ij[i2] * (-1);
                } else {
                    ij[i2];
                }
                );
            } else {
                xy[y2] = xy[y2] + ij[j2];
                ij[j2] = (
                if (Js.Math.abs_int(xy[y2]) == lauf[_G]) {
                    ij[j2] * (-1);
                } else {
                    ij[j2];
                }
                );
            };
            
            patterns[0] =
                Array.append(
                patterns[0],
                [|
                    {
                    p0:(0, 0),
                    p1:(xy[x1], xy[y1]),
                    p2: (xy[x2], xy[y2]),
                    p3: (xy[x3], xy[y3]),
                    score: getScore((xy[x1], xy[y1])),
                    },
                |],
                );

            ij[i1] = (
                if (lauf[_G] == Js.Math.abs_int(xy[x1])) {
                ij[i1] * (-1);
                } else {
                ij[i1];
                }
            );
            ij[j1] = (
                if (lauf[_G] == Js.Math.abs_int(xy[y1])) {
                ij[j1] * (-1);
                } else {
                ij[j1];
                }
            );
            ij[i3] = (
                if (lauf[_G] == Js.Math.abs_int(xy[x3])) {
                ij[i3] * (-1);
                } else {
                ij[i3];
                }
            );
            ij[j3] = (
                if (lauf[_G] == Js.Math.abs_int(xy[y3])) {
                ij[j3] * (-1);
                } else {
                ij[j3];
                }
            );

            if (lauf[q] mod n >= lauf[_G]) {
                lauf[q] = 0;
                lauf[b] = (
                if (lauf[b] == 0) {
                    1;
                } else {
                    0;
                }
                );
            };
            ignore(m);
            };
            ();
        };
        
        patterns[0] -> Array.to_list;
    };

let null = (unit) => { 
            p0: (0,0),
            p1: (0,0),
            p2: (0,0),
            p3: (0,0),
            score: 0
            };   
let isNull = (square) => square.score <= 0;
let notNull = (square) => !isNull(square);

type checked = 
| Valid(t)
| Invalid
;

let checkRange = (dim, square) => {
    let isCornerOutOfRange = dim -> Position.checkRange;
        switch( 
            isCornerOutOfRange(square.p0), 
            isCornerOutOfRange(square.p1), 
            isCornerOutOfRange(square.p2), 
            isCornerOutOfRange(square.p3)
        ){
            |(Valid(_),Valid(_),Valid(_),Valid(_)) => Valid(square)
            | _ => Invalid
        };
    };     

let mapPatternToSquare = (dim, p0, pattern) => {        
        let square = {
            p0: p0,
            p1: p0->Position.add(pattern.p1),
            p2: p0->Position.add(pattern.p2),
            p3: p0->Position.add(pattern.p3),
            score: pattern.score,
        };
        
        switch(dim->checkRange(square)){
            |Valid(square) => square               
            |_ => null()
        };     
    };

let findAllSquaresWithSameCorner = (p0, patterns, dim) => {
    patterns
    |> List.map(mapPatternToSquare(dim,p0)) 
    |> List.filter(notNull)     
};    


