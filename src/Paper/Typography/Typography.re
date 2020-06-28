
exception InvalidTextBaseline(string);
let exn = InvalidTextBaseline("invalid textBaseline value");
type textBaseline = [
  | `top
  | `hanging
  | `middle
  | `alphabetic
  | `ideographic
  | `bottom
];
let textBaselineToString = strokeJoin => switch(strokeJoin){
  | `top => "top"
  | `hanging => "hanging"
  | `middle => "middle"
  | `alphabetic => "alphabetic"
  | `ideographic => "ideographic"
  | `bottom => "bottom"
};

let textBaselineFromString = strStrokeJoin => switch(strStrokeJoin){
    |"top" => `top
    |"hanging" => `hanging 
    |"middle" => `middle 
    |"alphabetic" => `alphabetic 
    |"ideographic" => `ideographic 
    |"bottom" => `bottom 
  //  |_ => raise(InvalidTextBaseline("invalid textBaseline value")) ; //produces esling-warning "no-throw-literal" warning
    
    // Have a look at https://eslint.org/docs/rules/no-throw-literal#top 
    // Examples of correct code for this rule:
    // var err = "error";
    // throw err;

    |_ => raise(exn) ; // so this prevents an eslint warning
  //  |_ => Js.Exn.raiseError("invalid textBaseline value") ; // this, too.
};

type typographyContext = {
    mutable textBaseline: string // 
};

// let canvas = Paper.document##getElementById("canvas");
// let ctx = canvas##getContext("2d");
// ctx##textBaseline #= "middle";

[@bs.module "paper"] [@bs.scope "view"]
external getTypographyContext: unit => typographyContext = "getContext";


let setTextBaseline = textBaseline => {
    getTypographyContext().textBaseline = textBaselineToString(textBaseline);
    ();
};