
exception InvalidStrokeCap(string);
type strokeCap = [
  |`round
  |`squared
  |`butt
];

let strokeCapToString = strokeCap => switch(strokeCap){
  | `round   => "round"
  | `squared => "squared"
  | `butt    => "butt"
};

let strokeCapFromString = strStrokeCap => switch(strStrokeCap){
    |"round"   => `round
    |"squared" => `squared 
    |"butt"    => `butt 
    |_ => raise(InvalidStrokeCap("invalid stroke cap")) 
};


exception InvalidFillRule(string);
type fillRule = [
  |`nonzero
  |`evenodd
];

let fillRuleToString = fillRule => switch(fillRule){
  | `nonzero => "nonzero"
  | `evenodd => "evenodd"
};

let fillRuleFromString = strFillRule => switch(strFillRule){
    |"nonzero" => `nonzero
    |"evenodd" => `evenodd 
    |_ => raise(InvalidFillRule("invalid fill rule")) 
};

exception InvalidStrokeJoin(string);
type strokeJoin = [
  |`miter
  |`round
  |`bevel
];

let strokeJoinToString = strokeJoin => switch(strokeJoin){
  | `miter => "miter"
  | `round => "round"
  | `bevel => "bevel"
};

let strokeJoinFromString = strStrokeJoin => switch(strStrokeJoin){
    |"miter" => `miter
    |"round" => `round 
    |"bevel" => `bevel 
    |_ => raise(InvalidStrokeJoin("invalid stroke join")) ;
};


type cssColor = string;

[@bs.deriving abstract]
type styleDescription = {
   [@bs.optional] strokeColor: cssColor ,
   [@bs.optional] strokeWidth: float,
   [@bs.optional] strokeCap: string,
   [@bs.optional] strokeJoin: string,
   [@bs.optional] strokeScaling: bool,
   [@bs.optional] dashOffset: float,
   [@bs.optional] dashArray: array(float),
   [@bs.optional] miterLimit: float,
   [@bs.optional] fillColor: cssColor,
   [@bs.optional] fillRule: string,
   [@bs.optional] shadowColor: cssColor,
   [@bs.optional] shadowBlur: float,
   [@bs.optional] shadowOffset: float,
   [@bs.optional] selectedColor: cssColor,
   [@bs.optional] fontFamily: string,
   [@bs.optional] fontWeight: string,
   [@bs.optional] fontSize: float,
   [@bs.optional] leading: float,
   [@bs.optional] justification: string,  
   [@bs.optional] opacity: float,
};



module rec GradientStop: {
  type t = {
    offset: float,
    color: Color.t,
  };
  type resultGradientStop = t;
  type gradientStop = t;
  type offSet = float;

  [@bs.module "paper"] [@bs.new]
  external create:
    (~color: Color.t=?, ~offset: float=?, unit) => resultGradientStop =
    "GradientStop";

  [@bs.send] external clone: gradientStop => resultGradientStop = "clone";
} = {
  type t = {
    offset: float,
    color: Color.t,
  };
  type resultGradientStop = t;
  type gradientStop = t;
  type offSet = float;

  [@bs.module "paper"] [@bs.new]
  external create:
    (~color: Color.t=?, ~offset: float=?, unit) => resultGradientStop =
    "GradientStop";

  [@bs.send] external clone: gradientStop => resultGradientStop = "clone";
}
and Gradient: {
  type t = {
    stops: array(GradientStop.t),
    radial: bool,
  };
  type resultGradient = t;
  type gradient = t;
  type otherGradient = t;
  
  type startColor = cssColor;
  type endColor = cssColor;
  type radial = bool;

  [@bs.module "paper"] [@bs.new]
  external create: ((startColor,endColor),radial) => t = "Gradient";


  [@bs.send] external clone: gradient => resultGradient = "clone";
  [@bs.send]
  external equals: (gradient, otherGradient) => resultGradient = "equals";
} = {
 type t = {
    stops: array(GradientStop.t),
    radial: bool,
  };
  type resultGradient = t;
  type gradient = t;
  type otherGradient = t;
  
  type startColor = cssColor;
  type endColor = cssColor;
  type radial = bool;

  [@bs.module "paper"] [@bs.new]
  external create: ((startColor,endColor),radial) => t = "Gradient";


  [@bs.send] external clone: gradient => resultGradient = "clone";
  [@bs.send]
  external equals: (gradient, otherGradient) => resultGradient = "equals";
}
and Color: {
  type t = {
    type_: string,
    components: array(float),
    alpha: float,
    red: float,
    green: float,
    blue: float,
    gray: float,
    mutable hue: float,
    saturation: float,
    brightness: float,
    lightness: float,
    gradient: Gradient.t,
    highlight: BasicTypes.Point.t,
  };
  type color = t;
  type otherColor = t;
  type resultColor = t;
  type red = float;
  type green = float;
  type blue = float;
  type gray = float;
  
  type hex = bool;
  type type_ = string;
  type matrix = BasicTypes.Matrix.t;
  type gradient = Gradient.t;
  type origin = BasicTypes.Point.t;
  type destination = BasicTypes.Point.t;
  type highlight = BasicTypes.Point.t;

  [@bs.module "paper"] [@bs.new] external create: cssColor => color = "Color";
  [@bs.module "paper"] [@bs.new]
  external createRGB: (red, green, blue, ~alpha: float=?, unit) => color =
    "Color";
  [@bs.module "paper"] [@bs.new]
  external createGray: (gray, ~alpha: float=?, unit) => color = "Color";
  [@bs.module "paper"] [@bs.new]
  external createGradient: (~gradient:gradient, ~origin:origin, ~destination:destination, ~highlight:highlight =?, unit) => color = "Color";

  [@bs.send] external convert: (color, type_) => resultColor = "convert"; // TODO: make option type
  [@bs.send] external hasAlpha: color => bool = "hasAlpha";
  [@bs.send] external equals: (color, otherColor) => resultColor = "equals";
  [@bs.send] external clone: color => resultColor = "clone";

  [@bs.send] external toString: color => string = "toString";
  [@bs.send] external toCSS: (color, hex) => string = "toCSS";
  [@bs.send] external transform: (color, matrix) => unit = "transform";

  [@bs.send] external add: (color, otherColor) => resultColor = "add";
  [@bs.send] external addFloat: (color, float) => resultColor = "add";
  [@bs.send]
  external subtract: (color, otherColor) => resultColor = "subtract";
  [@bs.send]
  external subtractFloat: (color, float) => resultColor = "subtract";
  [@bs.send]
  external multiply: (color, otherColor) => resultColor = "multiply";
  [@bs.send]
  external multiplyFloat: (color, float) => resultColor = "multiply";
  [@bs.send] external divide: (color, otherColor) => resultColor = "divide";
  [@bs.send] external divideFloat: (color, float) => resultColor = "divide";

  [@bs.module "paper"] [@bs.scope "Color"] [@bs.val]
  external random: unit => resultColor = "random";
} = {
  type t = {
    type_: string,
    components: array(float),
    alpha: float,
    red: float,
    green: float,
    blue: float,
    gray: float,
    mutable hue: float,
    saturation: float,
    brightness: float,
    lightness: float,
    gradient: Gradient.t,
    highlight: BasicTypes.Point.t,
  };
  type color = t;
  type otherColor = t;
  type resultColor = t;
  type red = float;
  type green = float;
  type blue = float;
  type gray = float;
  
  type hex = bool;
  type type_ = string;
  type matrix = BasicTypes.Matrix.t;
  type gradient = Gradient.t;
  type origin = BasicTypes.Point.t;
  type destination = BasicTypes.Point.t;
  type highlight = BasicTypes.Point.t;

  [@bs.module "paper"] [@bs.new] external create: cssColor => color = "Color";
  [@bs.module "paper"] [@bs.new]
  external createRGB: (red, green, blue, ~alpha: float=?, unit) => color =
    "Color";
  [@bs.module "paper"] [@bs.new]
  external createGray: (gray, ~alpha: float=?, unit) => color = "Color";
  [@bs.module "paper"] [@bs.new]
  external createGradient: (~gradient:gradient, ~origin:origin, ~destination:destination, ~highlight:highlight =?, unit) => color = "Color";

  [@bs.send] external convert: (color, type_) => resultColor = "convert"; // TODO: make option type
  [@bs.send] external hasAlpha: color => bool = "hasAlpha";
  [@bs.send] external equals: (color, otherColor) => resultColor = "equals";
  [@bs.send] external clone: color => resultColor = "clone";

  [@bs.send] external toString: color => string = "toString";
  [@bs.send] external toCSS: (color, hex) => string = "toCSS";
  [@bs.send] external transform: (color, matrix) => unit = "transform";

  [@bs.send] external add: (color, otherColor) => resultColor = "add";
  [@bs.send] external addFloat: (color, float) => resultColor = "add";
  [@bs.send]
  external subtract: (color, otherColor) => resultColor = "subtract";
  [@bs.send]
  external subtractFloat: (color, float) => resultColor = "subtract";
  [@bs.send]
  external multiply: (color, otherColor) => resultColor = "multiply";
  [@bs.send]
  external multiplyFloat: (color, float) => resultColor = "multiply";
  [@bs.send] external divide: (color, otherColor) => resultColor = "divide";
  [@bs.send] external divideFloat: (color, float) => resultColor = "divide";

  [@bs.module "paper"] [@bs.scope "Color"] [@bs.val]
  external random: unit => resultColor = "random";
};


