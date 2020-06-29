open Jest;
open Expect;

describe("SquarePattern", () => {
  describe("swap array elements in [|0,1,2,3,4|]", () => {
    test("swap elements 2 and 3 gives [|0,1,3,2,4|]", () => {
      [|0, 1, 2, 3, 4|]->SquarePattern.swapArrayElements(2, 3)->expect
      |> toEqual([|0, 1, 3, 2, 4|])
    });
    test("swap elements 1 and 4 gives [|0,4,3,2,1|]", () => {
      [|0, 1, 2, 3, 4|]->SquarePattern.swapArrayElements(1, 4)->expect
      |> toEqual([|0, 4, 2, 3, 1|])
    });
  });

  describe("sort square pattern corners", () => {
    test(
      "p0(-1,2), p1(-3,1), p2(2,-1), p3(0,0)  gives p0(0,0), p1(-1,2), p2(-3,1), p3(2,-1)",
      () => {
        let ordered: SquarePattern.t = {
          p0: (0, 0),
          p1: ((-1), 2),
          p2: ((-3), 1),
          p3: (2, (-1)),
          score: 4,
        };
        let unordered: SquarePattern.t = {
          p0: ((-1), 2),
          p1: ((-3), 1),
          p2: (2, (-1)),
          p3: (0, 0),
          score: 4,
        };
        unordered->SquarePattern.sortCorners->expect |> toEqual(ordered);
      },
    );
    test(
      "p0(2,3), p1(0,0), p2(3,-2), p3(5,1)  gives p0(0,0), p1(2,3), p2(5,1), p3(3,-2)",
      () => {
        let ordered: SquarePattern.t = {
          p0: (0, 0),
          p1: (2, 3),
          p2: (5, 1),
          p3: (3, (-2)),
          score: 16,
        };
        let unordered: SquarePattern.t = {
          p0: (2, 3),
          p1: (0, 0),
          p2: (3, (-2)),
          p3: (5, 1),
          score: 16,
        };
        unordered->SquarePattern.sortCorners->expect |> toEqual(ordered);
      },
    );
  });

  describe("any square pattern starts with corner P0(0,0)", () => {
    test("p0(0,0), p1(0,1), p2(1,1), p3(1,0) is a square pattern", () => {
      {p0: (0, 0), p1: (0, 1), p2: (1, 1), p3: (1, 0), score: 4}
      ->SquarePattern.isValid
      ->expect
      |> toEqual(true)
    })
  });

  describe(
    "the corners of any square pattern follow each other counterclockwise", () => {
    test("p0(0,1), p1(0,0), p2(1,1), p3(1,0) is not a square pattern", () => {
      {p0: (0, 1), p1: (0, 0), p2: (1, 1), p3: (1, 0), score: 4}
      ->SquarePattern.isValid
      ->expect
      |> toEqual(false)
    })
  });

  describe("calculate the square score for side p0 to p1 ", () => {
    test("p2(-5,1) gives 16", () => {
      SquarePattern.getScore(((-5), 1))->expect |> toBe(16)
    });
    test("p2(5,-3) gives 25", () => {
      SquarePattern.getScore((5, (-3)))->expect |> toBe(25)
    });
    test("p2(1,3) gives 9", () => {
      SquarePattern.getScore((1, 3))->expect |> toBe(9)
    });
  });
  describe("calculate the square score for corner p2", () => {
    test("p2(-5,1) gives 16", () => {
      SquarePattern.getScore(((-5), 1))->expect |> toBe(16)
    });
    test("p2(5,-3) gives 25", () => {
      SquarePattern.getScore((5, (-3)))->expect |> toBe(25)
    });
    test("p2(1,3) gives 9", () => {
      SquarePattern.getScore((1, 3))->expect |> toBe(9)
    });
  });
  describe("has a correct calculated score", () => {
    test("p0(0,0), p1(-1,-4), p2(-5,-3), p3(-4,1) has valid score = 25", () => {
      {
        p0: (0, 0),
        p1: ((-1), (-4)),
        p2: ((-5), (-3)),
        p3: ((-4), 1),
        score: 25,
      }
      ->SquarePattern.isValid
      ->expect
      |> toEqual(true)
    });
    test("p0(0,0), p1(-1,-4), p2(-5,-3), p3(-4,1) has invalid score = 24", () => {
      {
        p0: (0, 0),
        p1: ((-1), (-4)),
        p2: ((-5), (-3)),
        p3: ((-4), 1),
        score: 24,
      }
      ->SquarePattern.isValid
      ->expect
      |> toEqual(false)
    });
  });
  describe(
    "squarePattern p0(0,0), p1(-1,-4), p2(-5,-3), p3(-4,1) with score=25", () => {
    let squarePattern: SquarePattern.t = {
      p0: (0, 0),
      p1: ((-1), (-4)),
      p2: ((-5), (-3)),
      p3: ((-4), 1),
      score: 25,
    };

    test(
      "and otherSquarePattern p0(0,0), p1(-1,-4), p2(-5,-3), p3(-4,1) with score=25 are identical ",
      () => {
      {
        p0: (0, 0),
        p1: ((-1), (-4)),
        p2: ((-5), (-3)),
        p3: ((-4), 1),
        score: 25,
      }
      ->SquarePattern.identicalWith(squarePattern)
      ->expect
      |> toEqual(true)
    });
    test(
      "and otherSquarePattern p0(0,0), p1(0,1), p2(1,1), p3(1,0) with score=4 are not identical",
      () => {
      {p0: (0, 0), p1: (0, 1), p2: (1, 1), p3: (1, 0), score: 4}
      ->SquarePattern.identicalWith(squarePattern)
      ->expect
      |> toEqual(false)
    });
  });
  describe("SquarePattern.make((-1,-4), (-5,-3), (-4,1))", () => {
    test(
      "gives a valid SquarePattern p0(0,0), p1(-1,-4), p2(-5,-3), p3(-4,1) with score=25",
      () => {
      SquarePattern.make(((-1), (-4)), ((-5), (-3)), ((-4), 1))
      ->SquarePattern.isValid
      ->expect
      |> toEqual(true)
    })
  });
  describe("initSearchList",() =>{
    test("gives an empty list for a 0x0 field", () => {
      SquarePattern.initSearchList(0) -> expect |> toEqual([]);
    });
    test("gives an empty list for a 1x1 field", () => {
      SquarePattern.initSearchList(1) -> expect |> toEqual([]);
    });
    describe("for a 2x2 game board",()=>{
      test("it gives a list containing 4 squares", () => {        
        SquarePattern.initSearchList(2)  ->List.length -> expect |> toBe(4);
      });
      test("this list contains  pattern {p0:(0,0),p1:(-1,0),p2:(-1,1),p3:(0,1),score:4}", () => {
        let pattern:SquarePattern.t = {p0:(0,0),p1:(-1,0),p2:(-1,1),p3:(0,1),score:4};
        let identical = SquarePattern.identicalWith(pattern);
        let searchList = SquarePattern.initSearchList(2); 
         searchList -> List.exists(identical,_) -> expect |> toEqual(true);
      });      
    });
    describe("for a 3x3 game board",()=>{
      test("it gives a list containing 12 squares", () => {        
        SquarePattern.initSearchList(3)  ->List.length -> expect |> toBe(12);
      });
      test("this list contains  pattern {p0:(0,0),p1:(-1,0),p2:(-1,1),p3:(0,1),score:4} from 2x2 board", () => {
        let pattern:SquarePattern.t = {p0:(0,0),p1:(-1,0),p2:(-1,1),p3:(0,1),score:4};
        let identical = SquarePattern.identicalWith(pattern);
        let searchList = SquarePattern.initSearchList(3); 
         searchList -> List.exists(identical,_) -> expect |> toEqual(true);
      });
      test("this list contains  pattern {p0:(0,0),p1:(-2,0),p2:(-2,2),p3:(0,2),score:9}", () => {
        let pattern:SquarePattern.t = {p0:(0,0),p1:(-2,0),p2:(-2,2),p3:(0,2),score:9};
        let identical = SquarePattern.identicalWith(pattern);
        let searchList = SquarePattern.initSearchList(3); 
         searchList -> List.exists(identical,_) -> expect |> toEqual(true);
      });
      
    });
    describe("for a 9x9 game board",()=>{
      test("it gives a list containing 144 squares", () => {        
        SquarePattern.initSearchList(9)  ->List.length -> expect |> toBe(144);
      });
      test("this list contains  pattern {p0:(0,0),p1:(-1,0),p2:(-1,1),p3:(0,1),score:4} from 2x2 board", () => {
        let pattern:SquarePattern.t = {p0:(0,0),p1:(-1,0),p2:(-1,1),p3:(0,1),score:4};
        let identical = SquarePattern.identicalWith(pattern);
        let searchList = SquarePattern.initSearchList(9); 
         searchList -> List.exists(identical,_) -> expect |> toEqual(true);
      });
      test("this list contains  pattern {p0:(0,0),p1:(-2,0),p2:(-2,2),p3:(0,2),score:9} from 3x3 board", () => {
        let pattern:SquarePattern.t = {p0:(0,0),p1:(-2,0),p2:(-2,2),p3:(0,2),score:9};
        let identical = SquarePattern.identicalWith(pattern);
        let searchList = SquarePattern.initSearchList(9); 
         searchList -> List.exists(identical,_) -> expect |> toEqual(true);
      });
      test("this list contains  pattern {p0:(0,0),p1:(-5,0),p2:(-5,5),p3:(0,5),score:36} from 6x6 board", () => {
        let pattern:SquarePattern.t = {p0:(0,0),p1:(-5,0),p2:(-5,5),p3:(0,5),score:36};
        let identical = SquarePattern.identicalWith(pattern);
        let searchList = SquarePattern.initSearchList(9); 
         searchList -> List.exists(identical,_) -> expect |> toEqual(true);
      });
      test("this list contains  pattern {p0:(0,0),p1:(-8,0),p2:(-8,8),p3:(0,8),score:81} from 6x6 board", () => {
        let pattern:SquarePattern.t = {p0:(0,0),p1:(-8,0),p2:(-8,8),p3:(0,8),score:81};
        let identical = SquarePattern.identicalWith(pattern);
        let searchList = SquarePattern.initSearchList(9); 
         searchList -> List.exists(identical,_) -> expect |> toEqual(true);
      });
      
    });
    describe("findAllSquaresWithSameCorner for a position on a 9x9 board",()=>{
      test("for position (0,0) it gives 8 squares", () => {
        let p0:Position.t = (0,0);        
        let dim = 9;
        let searchList = SquarePattern.initSearchList(dim); 
        SquarePattern.findAllSquaresWithSameCorner(p0,searchList,dim)
        -> List.length -> expect |> toEqual(8);
      });
      test("one of them is pattern {p0:(0,0),p1:(0,1),p2:(1,1),p3:(1,0),score:4} ", () => {
        let pattern:SquarePattern.t = {p0:(0,0),p1:(0,1),p2:(1,1),p3:(1,0),score:4};
        let identical = SquarePattern.identicalWith(pattern);
        let p0:Position.t = (0,0);        
        let dim = 9;
        let searchList = SquarePattern.initSearchList(dim); 
        SquarePattern.findAllSquaresWithSameCorner(p0,searchList,dim) 
        -> List.exists(identical,_) -> expect |> toEqual(true);
      });
      test("for position (8,8) it gives 8 squares", () => {
        let p0:Position.t = (8,8);        
        let dim = 9;
        let searchList = SquarePattern.initSearchList(dim); 
        SquarePattern.findAllSquaresWithSameCorner(p0,searchList,dim)
        -> List.length -> expect |> toEqual(8);
      });
      test("one of them is pattern {p0:(8,8),p1:(8,7),p2:(7,7),p3:(7,8),score:4} ", () => {
        let pattern:SquarePattern.t = {p0:(8,8),p1:(8,7),p2:(7,7),p3:(7,8),score:4};
        let identical = SquarePattern.identicalWith(pattern);
        let p0:Position.t = (8,8);        
        let dim = 9;
        let searchList = SquarePattern.initSearchList(dim); 
        SquarePattern.findAllSquaresWithSameCorner(p0,searchList,dim) 
        -> List.exists(identical,_) -> expect |> toEqual(true);
      });
      test("for position (0,8) it gives 8 squares", () => {
        let p0:Position.t = (0,8);        
        let dim = 9;
        let searchList = SquarePattern.initSearchList(dim); 
        SquarePattern.findAllSquaresWithSameCorner(p0,searchList,dim)
        -> List.length -> expect |> toEqual(8);
      });
      test("one of them is pattern {p0:(0,8),p1:(1,8),p2:(1,7),p3:(0,7),score:4} ", () => {
        let pattern:SquarePattern.t = {p0:(0,8),p1:(1,8),p2:(1,7),p3:(0,7),score:4};
        let identical = SquarePattern.identicalWith(pattern);
        let p0:Position.t = (0,8);        
        let dim = 9;
        let searchList = SquarePattern.initSearchList(dim); 
        SquarePattern.findAllSquaresWithSameCorner(p0,searchList,dim) 
        -> List.exists(identical,_) -> expect |> toEqual(true);
      });
      test("for position (8,0) it gives 8 squares", () => {
        let p0:Position.t = (8,0);        
        let dim = 9;
        let searchList = SquarePattern.initSearchList(dim); 
        SquarePattern.findAllSquaresWithSameCorner(p0,searchList,dim)
        -> List.length -> expect |> toEqual(8);
      });
      test("one of them is pattern {p0:(8,0),p1:(7,0),p2:(7,1),p3:(8,1),score:4} ", () => {
        let pattern:SquarePattern.t = {p0:(8,0),p1:(7,0),p2:(7,1),p3:(8,1),score:4};
        let identical = SquarePattern.identicalWith(pattern);
        let p0:Position.t = (8,0);        
        let dim = 9;
        let searchList = SquarePattern.initSearchList(dim); 
        SquarePattern.findAllSquaresWithSameCorner(p0,searchList,dim) 
        -> List.exists(identical,_) -> expect |> toEqual(true);
      });
       test("for position (3,5) it gives 38 squares", () => {
        let p0:Position.t = (3,5);        
        let dim = 9;
        let searchList = SquarePattern.initSearchList(dim); 
        SquarePattern.findAllSquaresWithSameCorner(p0,searchList,dim)
        -> List.length -> expect |> toEqual(38);
      });
      test("one of them is pattern {p0:(3,5),p1:(3,4),p2:(2,4),p3:(2,5),score:4} ", () => {
        let pattern:SquarePattern.t = {p0:(3,5),p1:(3,4),p2:(2,4),p3:(2,5),score:4} ;
        let identical = SquarePattern.identicalWith(pattern);
        let p0:Position.t = (3,5);        
        let dim = 9;
        let searchList = SquarePattern.initSearchList(dim); 
        SquarePattern.findAllSquaresWithSameCorner(p0,searchList,dim) 
        -> List.exists(identical,_) -> expect |> toEqual(true);
      });
       test("for position (5,3) it gives 38 squares", () => {
        let p0:Position.t = (5,3);        
        let dim = 9;
        let searchList = SquarePattern.initSearchList(dim); 
        SquarePattern.findAllSquaresWithSameCorner(p0,searchList,dim)
        -> List.length -> expect |> toEqual(38);
      });
      test("one of them is pattern {p0:(5,3),p1:(4,3),p2:(4,4),p3:(5,4),score:4} ", () => {
        let pattern:SquarePattern.t = {p0:(5,3),p1:(4,3),p2:(4,4),p3:(5,4),score:4} ;
        let identical = SquarePattern.identicalWith(pattern);
        let p0:Position.t = (5,3);        
        let dim = 9;
        let searchList = SquarePattern.initSearchList(dim); 
        SquarePattern.findAllSquaresWithSameCorner(p0,searchList,dim) 
        -> List.exists(identical,_) -> expect |> toEqual(true);
      });
       test("for position (6,6) it gives 32 squares", () => {
        let p0:Position.t = (6,6);        
        let dim = 9;
        let searchList = SquarePattern.initSearchList(dim); 
        SquarePattern.findAllSquaresWithSameCorner(p0,searchList,dim)
        -> List.length -> expect |> toEqual(32);
      });
      test("one of them is pattern {p0:(6,6),p1:(6,7),p2:(7,7),p3:(7,6),score:4} ", () => {
        let pattern:SquarePattern.t = {p0:(6,6),p1:(6,7),p2:(7,7),p3:(7,6),score:4};
        let identical = SquarePattern.identicalWith(pattern);
        let p0:Position.t = (6,6);        
        let dim = 9;
        let searchList = SquarePattern.initSearchList(dim); 
        SquarePattern.findAllSquaresWithSameCorner(p0,searchList,dim) 
        -> List.exists(identical,_) -> expect |> toEqual(true);
      });
      
    });
  });
});
