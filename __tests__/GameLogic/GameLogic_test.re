open Jest;
open Expect;

describe("GameLogic", () => {
  open GameLogic;

  describe("Valid Positions are inside 9x9 range ", () => {
    let invalidPosition = (int_of_float(infinity), int_of_float(infinity));
    let range = 9;
    let checkedAgainstRange = (position, range) =>
      switch (Position.checkRange(range, position)) {
      | Valid(position) => position
      | _ => invalidPosition
      };
    test("P(-1,-1) is Invalid", () => {
      ((-1), (-1))->checkedAgainstRange(range)->expect
      |> toEqual(invalidPosition)
    });
    test("P(0,-1) is Invalid", () => {
      (0, (-1))->checkedAgainstRange(range)->expect
      |> toEqual(invalidPosition)
    });
    test("P(-1,0) is Invalid", () => {
      ((-1), 0)->checkedAgainstRange(range)->expect
      |> toEqual(invalidPosition)
    });
    test("P(0,0) is Valid((0,0))", () => {
      (0, 0)->checkedAgainstRange(range)->expect |> toEqual((0, 0))
    });
    test("P(4,5) is Valid((4,5))", () => {
      (4, 5)->checkedAgainstRange(range)->expect |> toEqual((4, 5))
    });
    test("P(0,8) is Valid((0,8))", () => {
      (0, 8)->checkedAgainstRange(range)->expect |> toEqual((0, 8))
    });
    test("P(8,0) is Valid((8,0))", () => {
      (8, 0)->checkedAgainstRange(range)->expect |> toEqual((8, 0))
    });
    test("P(8,8) is Valid((8,8))", () => {
      (8, 8)->checkedAgainstRange(range)->expect |> toEqual((8, 8))
    });
    test("P(9,8) is Invalid", () => {
      (9, 8)->checkedAgainstRange(range)->expect |> toEqual(invalidPosition)
    });
    test("P(8,9) is Invalid", () => {
      (8, 9)->checkedAgainstRange(range)->expect |> toEqual(invalidPosition)
    });
    test("P(9,9) is Invalid", () => {
      (9, 9)->checkedAgainstRange(range)->expect |> toEqual(invalidPosition)
    });
    test("P(99,-99) is Invalid", () => {
      (99, (-99))->checkedAgainstRange(range)->expect
      |> toEqual(invalidPosition)
    });
  });
  describe("A field", () => {
    test("can be empty", () => {
      let field = Empty;
      field->isFieldEmpty->expect |> toBe(true);
    });
    test("can have an empty color", () => {
      let field = Empty;
      field->getFieldColor->expect |> toBe("");
    });
    test("can be occupied with a color", () => {
      let color: Styling.cssColor = "red";
      let field = Occupied(color);

      field->getFieldColor->expect |> toBe(color);
    });
  });
});
