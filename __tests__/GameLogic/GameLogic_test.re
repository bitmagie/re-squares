open Jest;
open Expect;

describe("GameLogic", () => {
  open Game;


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
