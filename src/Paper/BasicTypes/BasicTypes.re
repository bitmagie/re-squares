

let radians = degrees => degrees *. Js.Math._PI /. 180.;
let degrees = radians => radians *. 180. /. Js.Math._PI;




type size = {
  width: float,
  height: float,
};
type point = {
  x: float,
  y: float,
  length: float,
  angle: float,
  angleInRadians: float,
  quadrant: float,
  selected: bool,
};
[@bs.deriving abstract]
type pointDescription = {
    [@bs.optional] x: float,
    [@bs.optional] y: float,   
    [@bs.optional]length: float,
    [@bs.optional]angle: float,
    [@bs.optional]angleInRadians: float,
  };

type matrix = {
  a: float,
  b: float,
  c: float,
  d: float,
  tx: float,
  ty: float,
  values: array(float),
  translation: point,
  scaling: point,
  rotation: float,
};
type rectangle = {
  x: float,
  y: float,
  width: float,
  height: float,
  point,
  size,
  left: float,
  top: float,
  right: float,
  bottom: float,
  center: point,
  topLeft: point,
  topRight: point,
  bottomLeft: point,
  bottomRight: point,
  leftCenter: point,
  topCenter: point,
  rightCenter: point,
  bottomCenter: point,
  area: float,
  selected: bool,
};



module Matrix = {
  type t = matrix;

  type otherMatrix = t;
  type resultMatrix = t;
  type resultPoint = point;
  type a = float;
  type b = float;
  type c = float;
  type d = float;
  type tx = float;
  type ty = float;
  type dx = float;
  type dy = float;
  type factor = float;
  type hor = float;
  type ver = float;
  type angle = float;
  type x = float;
  type y = float;

  type resultObject = {
    scaling: point,
    rotation: point,
    skewing: point,
  };

  type ctx;

  [@bs.module "paper"] [@bs.new] external create: unit => matrix = "Matrix";
  [@bs.module "paper"] [@bs.new]
  external createFromFloat: (a, b, b, d, tx, ty) => matrix = "Matrix";

  [@bs.send] external clone: matrix => resultMatrix = "clone";
  [@bs.send] external equals: (matrix, otherMatrix) => bool = "equals";
  [@bs.send] external toString: matrix => string = "toString";
  [@bs.send]
  external apply: (matrix, ~recursively: bool=?, unit) => bool = "apply";

  [@bs.send] external translate: (matrix, point) => resultMatrix = "translate";
  [@bs.send]
  external translateByNumber: (matrix, dx, dy) => resultMatrix = "translate";
  [@bs.send]
  external scale: (matrix, factor, ~center: point=?, unit) => resultMatrix =
    "scale";
  [@bs.send]
  external scaleByNumber:
    (matrix, hor, ver, ~center: point=?, unit) => resultMatrix =
    "scale";
  [@bs.send]
  external rotate: (matrix, angle, ~center: point=?, unit) => resultMatrix =
    "rotate";
  [@bs.send]
  external rotateByNumber: (matrix, angle, x, y) => resultMatrix = "rotate";
  [@bs.send]
  external shear: (matrix, point, ~center: point=?, unit) => resultMatrix =
    "shear";
  [@bs.send]
  external shearByNumber:
    (matrix, hor, ver, ~center: point=?, unit) => resultMatrix =
    "shear";
  [@bs.send]
  external skew: (matrix, point, ~center: point=?, unit) => resultMatrix =
    "skew";
  [@bs.send]
  external skewByNumber:
    (matrix, hor, ver, ~center: point=?, unit) => resultMatrix =
    "skew";

  [@bs.send]
  external appended: (matrix, otherMatrix) => resultMatrix = "appended";
  [@bs.send]
  external prepended: (matrix, otherMatrix) => resultMatrix = "prepended";
  [@bs.send] external inverted: matrix => resultMatrix = "inverted";

  [@bs.send] external isIdentity: matrix => bool = "isIdentity";
  [@bs.send] external isInvertible: matrix => bool = "isInvertible";
  [@bs.send] external isSingular: matrix => bool = "isSingular";

  [@bs.send] external transform: point => resultPoint = "inverted";
  [@bs.send]
  external inverseTransform: point => resultPoint = "inverseTransform";
  [@bs.send] external decompose: matrix => resultObject = "decompose";
  [@bs.send] external applyToContext: (matrix, ctx) => unit = "applyToContext";
};

module Size = {
  type t = size;

  type otherSize = t;
  type resultSize = t;

  type number = float;
  type width = float;
  type height = float;

  type object_ = {
    x: float,
    y: float,
  };

  [@bs.module "paper"] [@bs.new]
  external create: (width, height) => resultSize = "Size";
  [@bs.module "paper"] [@bs.new]
  external createFromArray: array(float) => resultSize = "Size";
  [@bs.module "paper"] [@bs.new]
  external createFromObject: object_ => resultSize = "Size";

  [@bs.send] external equals: (size, otherSize) => bool = "equals";
  [@bs.send] external clone: size => resultSize = "clone";
  [@bs.send] external toString: size => string = "toString";

  [@bs.send] external isZero: size => bool = "isZero";

  [@bs.send] external round: size => resultSize = "round";
  [@bs.send] external floor: size => resultSize = "floor";
  [@bs.send] external abs: size => resultSize = "abs";

  [@bs.send] external add: (size, number) => resultSize = "add";
  [@bs.send] external addSize: (size, otherSize) => resultSize = "add";
  [@bs.send] external subtract: (size, number) => resultSize = "subtract";
  [@bs.send]
  external subtractSize: (size, otherSize) => resultSize = "subtract";
  [@bs.send] external multiply: (size, number) => resultSize = "multiply";
  [@bs.send]
  external multiplyBySize: (size, otherSize) => resultSize = "multiply";
  [@bs.send] external divide: (size, number) => resultSize = "divide";
  [@bs.send] external divideBySize: (size, otherSize) => resultSize = "divide";
  [@bs.send] external modulo: (size, number) => resultSize = "modulo";
  [@bs.send] external moduloBySize: (size, otherSize) => resultSize = "modulo";

  [@bs.module "paper"] [@bs.scope "Size"] [@bs.val]
  external min: (size, otherSize) => resultSize = "min";
  [@bs.module "paper"] [@bs.scope "Size"] [@bs.val]
  external max: (size, otherSize) => resultSize = "max";
  [@bs.module "paper"] [@bs.scope "Size"] [@bs.val]
  external random: unit => resultSize = "random";
};


module Point = {
  type t = point;

  type otherPoint = t;
  type resultPoint = t;

  type x = float;
  type y = float;
  type number = float;
  type angle = float;
  type center = point;
  type tolerance = float;
  type quadrant = int;

  

  type angleLength = {
    angle: float,
    length: float
  };

  [@bs.module "paper"] [@bs.new]
  external create: (x, y) => resultPoint = "Point";
  [@bs.module "paper"] [@bs.new]
  external createFromPoint: point => resultPoint = "Point";
  [@bs.module "paper"] [@bs.new]
  external createFromSize: size => resultPoint = "Point";
  [@bs.module "paper"] [@bs.new]
  external createFromArray: array(float) => resultPoint = "Point";
  [@bs.module "paper"] [@bs.new]
  external createFromObject: pointDescription => resultPoint = "Point";
  [@bs.module "paper"] [@bs.new]
  external createFromAngleLength: angleLength => resultPoint = "Point";

  [@bs.send] external equals: (point, otherPoint) => bool = "equals";
  [@bs.send] external clone: point => resultPoint = "clone";
  [@bs.send] external toString: point => string = "toString";
  
  // [@bs.send] external getAngle: (point, otherPoint) => float = "getAngle";
    
  [@bs.send]  
  external getAngleInRadians: (point, otherPoint) => float =  
    "getAngleInRadians";
  [@bs.send]
  external getAngleInRadiansSelf: (point) => float =
    "getAngleInRadians";
  [@bs.send]
  external getDirectedAngle: (point, otherPoint) => float = "getDirectedAngle";
  [@bs.send]
  external getDistance: (point, otherPoint, ~squared: bool=?, unit) => float =
    "getDistance";
  [@bs.send]
  external normalize: (point, ~length: float=?, unit) => resultPoint =
    "normalize";
  [@bs.send] external rotate: (point, angle, center) => resultPoint = "rotate";
  [@bs.send] external transform: (point, matrix) => resultPoint = "transform";

  [@bs.send] external isInside: (point, rectangle) => bool = "isInside";
  [@bs.send] external isClose: (point, tolerance) => bool = "isClose";
  [@bs.send] external isCollinear: (point, otherPoint) => bool = "isCollinear";
  [@bs.send]
  external isOrthogonal: (point, otherPoint) => bool = "isOrthogonal";
  [@bs.send] external isZero: point => bool = "isZero";
  [@bs.send] external isInQuadrant: (point, quadrant) => bool = "isInQuadrant";

  [@bs.send] external dot: (point, otherPoint) => float = "dot";
  [@bs.send] external cross: (point, otherPoint) => float = "cross";
  [@bs.send] external project: (point, otherPoint) => resultPoint = "project";

  [@bs.send] external round: point => resultPoint = "round";
  [@bs.send] external ceil: point => resultPoint = "ceil";
  [@bs.send] external floor: point => resultPoint = "floor";
  [@bs.send] external abs: point => resultPoint = "floor";

  [@bs.send] external add: (point, number) => resultPoint = "add";
  [@bs.send] external addPoint: (point, otherPoint) => resultPoint = "add";
  [@bs.send] external subtract: (point, number) => resultPoint = "subtract";
  [@bs.send] external subtractPoint: (point, otherPoint) => resultPoint = "subtract";
  
  [@bs.send] external multiply: (point, number) => resultPoint = "multiply";  
  [@bs.send] external multiplyPoint: (point, otherPoint) => resultPoint = "multiply";
  [@bs.send] external divide: (point, number) => resultPoint = "divide";
  [@bs.send] external dividePoint: (point, otherPoint) => resultPoint = "divide";
  [@bs.send] external modulo: (point, number) => resultPoint = "modulo";
  [@bs.send] external moduloPoint: (point, otherPoint) => resultPoint = "modulo";

  [@bs.module "paper"] [@bs.scope "Point"] [@bs.val]
  external min: (point, otherPoint) => resultPoint = "min";
  [@bs.module "paper"] [@bs.scope "Point"] [@bs.val]
  external max: (point, otherPoint) => resultPoint = "max";
  [@bs.module "paper"] [@bs.scope "Point"] [@bs.val]
  external random: unit => resultPoint = "random";

  let getAngle = (point, otherPoint) =>{
    let d = point -> subtractPoint(otherPoint);
    atan2(d.y, d.x) -> degrees(_) ;    
  }; 

};

module Rectangle = {
  type t = rectangle;

  type otherRectangle = t;
  type resultRectangle = t;
  type x = float;
  type y = float;
  type width = float;
  type height = float;
  type hor = float;
  type ver = float;
  type from = point;
  type to_ = point;
  type number = float;
  type object_ = {
    x: float,
    y: float,
    width: float,
    height: float,
  };

  [@bs.module "paper"] [@bs.new]
  external create: (x, y, width, height) => resultRectangle = "Rectangle";
  [@bs.module "paper"] [@bs.new]
  external createFromObject: object_ => resultRectangle = "Rectangle";
  [@bs.module "paper"] [@bs.new]
  external createFromPoint: (point, size) => resultRectangle = "Rectangle";
  [@bs.module "paper"] [@bs.new]
  external createFromPoints: (from, to_) => resultRectangle = "Rectangle";

  [@bs.send] external clone: rectangle => resultRectangle = "clone";
  [@bs.send] external equals: (rectangle, otherRectangle) => bool = "equals";
  [@bs.send] external toString: rectangle => string = "toString";
  [@bs.send] external isEmpty: rectangle => bool = "isEmpty";

  [@bs.send] external containsPoint: (rectangle, point) => bool = "contains";
  [@bs.send]
  external containsRectangle: (rectangle, otherRectangle) => bool = "contains";
  [@bs.send]
  external intersects:
    (rectangle, otherRectangle, ~epsilon: float=?, unit) => bool =
    "intersects";

  [@bs.send]
  external intersect: (rectangle, otherRectangle) => resultRectangle =
    "intersect";
  [@bs.send]
  external unite: (rectangle, otherRectangle) => resultRectangle = "unite";
  [@bs.send]
  external include_: (rectangle, point) => resultRectangle = "include";
  [@bs.send]
  external expand: (rectangle, hor, ver) => resultRectangle = "expand";
  [@bs.send]
  external expandByNumber: (rectangle, number) => resultRectangle = "expand";
  [@bs.send]
  external expandBySize: (rectangle, size) => resultRectangle = "expand";
  [@bs.send]
  external expandByPoint: (rectangle, point) => resultRectangle = "expand";
  [@bs.send]
  external scale: (rectangle, hor, ver) => resultRectangle = "scale";
  [@bs.send]
  external scaleByNumber: (rectangle, number) => resultRectangle = "scale";
};