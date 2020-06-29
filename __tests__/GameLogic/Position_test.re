open Jest;
open Expect;

describe("Position", () => {
  describe("checkRange for a 9x9 game board", () =>      {
      test("(0,0) is a valid position",() => {
        Position.checkRange(9,(0, 0),)->expect |> toEqual(Position.Valid((0, 0)));    
      });
      test("(4,5) is a valid position",() => {
        Position.checkRange(9,(4, 5),)->expect |> toEqual(Position.Valid((4, 5)));    
      });
      test("(8,8) is a valid position",() => {
        Position.checkRange(9,(8, 8),)->expect |> toEqual(Position.Valid((8, 8)));    
      });
      test("(-1,0) is an invalid position",() => {
        Position.checkRange(9,(-1, 0),)->expect |> toEqual(Position.Invalid);    
      });
      test("(0,-1) is an invalid position",() => {
        Position.checkRange(9,(0, -1),)->expect |> toEqual(Position.Invalid);    
      });
      test("(-4,-5) is an invalid position",() => {
        Position.checkRange(9,(-4, -5),)->expect |> toEqual(Position.Invalid);    
      });
      test("(8,9) is an invalid position",() => {
        Position.checkRange(9,(8, 9),)->expect |> toEqual(Position.Invalid);    
      });
      test("(9,8) is an invalid position",() => {
        Position.checkRange(9,(9, 8),)->expect |> toEqual(Position.Invalid);    
      });
      test("(12,18) is an invalid position",() => {
        Position.checkRange(9,(12, 18),)->expect |> toEqual(Position.Invalid);    
      });
    });
  describe("add", () => {
    test("(1,1) + (1,1) == (2,2)", () => {
      Position.add((1, 1), (1, 1))->expect |> toEqual((2, 2))
    });
    test("(-1,2) + (3,-4) == (2,-2)", () => {
      Position.add(((-1), 2), (3, (-4)))->expect |> toEqual((2, (-2)))
    });
  });
  describe("subtract", () => {
    test("(1,1) - (1,1) == (0,0)", () => {
      Position.subtract((1, 1), (1, 1))->expect |> toEqual((0, 0))
    });
    test("(-1,2) - (3,-4) == (-4.6)", () => {
      Position.subtract(((-1), 2), (3, (-4)))->expect |> toEqual(((-4), 6))
    });
  });
  describe("multiply", () => {
    test("(1,1) * (1,1) == 2", () => {
      Position.multiply((1, 1), (1, 1))->expect |> toBe(2)
    });
    test("(-1,2) * (3,-4) == -11", () => {
      Position.multiply(((-1), 2), (3, (-4)))->expect |> toBe(-11)
    });
  });
  describe("square", () => {
    test("(1,1)^2  == 2", () => {
      Position.square((1, 1))->expect |> toBe(2)
    });
    test("(-1,2)^2  == 5", () => {
      Position.square(((-1), 2))->expect |> toBe(5)
    });
  });

  describe("absComponents", () => {
    test("absComponents((0,0) == (0,0)", () => {
      (0, 0)->Position.absComponents->expect |> toEqual((0, 0))
    });
    test("absComponents(-2,3) == (2,3)", () => {
      ((-2), 3)->Position.absComponents->expect |> toEqual((2, 3))
    });
    test("absComponents(-4,-5) == (4,5)", () => {
      ((-4), (-5))->Position.absComponents->expect |> toEqual((4, 5))
    });
    test("absComponents(6,7) == (6,7)", () => {
      (6, 7)->Position.absComponents->expect |> toEqual((6, 7))
    });
  });
  describe("minComponents", () => {
    test("minComponents(1,1) == 1", () => {
      Position.minComponents((1, 1))->expect |> toEqual(1)
    });
    test("minComponent(1,-2) == -2", () => {
      Position.minComponents((1, (-2)))->expect |> toEqual(-2)
    });
    test("minComponents(-3,-2) == -3", () => {
      Position.minComponents(((-3), (-2)))->expect |> toEqual(-3)
    });
    test("minComponents(3,2)=2", () => {
      Position.minComponents((3, 2))->expect |> toEqual(2)
    });
  });
  describe("maxComponents", () => {
    test("maxComponents(0,1) == 1", () => {
      Position.maxComponents((1, 1))->expect |> toEqual(1)
    });
    test("maxComponents(3,2) == 3", () => {
      Position.maxComponents((3, 2))->expect |> toEqual(3)
    });
    test("maxComponents(-1,-2) == -1", () => {
      Position.maxComponents(((-1), (-2)))->expect |> toEqual(-1)
    });
    test("maxComponents(-4,-5) == -4", () => {
      Position.maxComponents(((-5), (-4)))->expect |> toEqual(-4)
    });
  });
  describe("equals", () => {
    test("(-1,2) == (-1,2)", () => {
      Position.equals(((-1), 2), ((-1), 2))->expect |> toBe(true)
    });
    test("(2,-1) == (2,-1)", () => {
      Position.equals((2, (-1)), (2, (-1)))->expect |> toBe(true)
    });
    test("(0,0) == (0,0)", () => {
      Position.equals((0, 0), (0, 0))->expect |> toBe(true)
    });
    test("(1,1) == (1,1)", () => {
      Position.equals((1, 1), (1, 1))->expect |> toBe(true)
    });
  });
  describe("don't equals", () => {
    test("(-1,2) <> (2,-1)", () => {
      Position.equals(((-1), 2), (2, (-1)))->expect |> toBe(false)
    });
    test("(-2,1) <> (2,-1)", () => {
      Position.equals(((-2), 1), (2, (-1)))->expect |> toBe(false)
    });

    test("(-1,2) <> (3,-4)", () => {
      Position.equals(((-1), 2), (3, (-4)))->expect |> toBe(false)
    });
    test("(-1,2) <> (3,-4)", () => {
      Position.equals(((-1), 2), (3, (-4)))->expect |> toBe(false)
    });
  });
});
