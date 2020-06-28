


[@bs.deriving abstract]
type pointTextDescription = {
   [@bs.optional] point: BasicTypes.point ,
   [@bs.optional] content: string ,
   [@bs.optional] strokeColor: string ,
   [@bs.optional] strokeWidth: float,
   [@bs.optional] strokeCap: string,
   [@bs.optional] strokeJoin: string,
   [@bs.optional] strokeScaling: bool,
   [@bs.optional] dashOffset: float,
   [@bs.optional] dashArray: array(float),
   [@bs.optional] miterLimit: float,
   [@bs.optional] fillColor: string,
   [@bs.optional] fillRule: string,
   [@bs.optional] shadowColor: string,
   [@bs.optional] shadowBlur: float,
   [@bs.optional] shadowOffset: float,
   [@bs.optional] selectedColor: string,
   [@bs.optional] fontFamily: string,
   [@bs.optional] fontWeight: string,
   [@bs.optional] fontSize: float,
   [@bs.optional] leading: float,
   [@bs.optional] justification: string,  
};


type t = {
    point: BasicTypes.point,
    id: float,
    className: string,
    name: string,
    mutable style: Styling.styleDescription,
    locked: bool,
    visible: bool,
    blendMode: string,
    opacity: float,
    selected: bool,
    clipMask: bool,
    data: string,
    mutable position: BasicTypes.point,
    pivot: option(BasicTypes.point),
    bounds: BasicTypes.rectangle,
    strokeBounds: BasicTypes.rectangle,
    handleBounds: BasicTypes.rectangle,
    internalBounds: BasicTypes.rectangle,
    rotation: float,
    scaling:BasicTypes.point,
    matrix: BasicTypes.matrix,
    globalMatrix: BasicTypes.matrix,
    viewMatrix: BasicTypes.matrix,
    applyMatrix: bool,
    mutable strokeColor: Styling.Color.t,
    mutable strokeWidth: float,
    mutable strokeCap: string,
    mutable strokeJoin: string,
    mutable dashOffset: float,
    mutable strokeScaling: bool,
    mutable dashArray: array(float),
    mutable miterLimit: float,
    mutable fillColor: Styling.Color.t,
    mutable fillRule: string,

    mutable shadowColor: Styling.Color.t,
    mutable shadowBlur: float,
    mutable shadowOffset: BasicTypes.point,

    mutable content: string,

    mutable fontFamily: string,
    mutable fontWeight: string,
    mutable fontSize: float,
    mutable leading: float,
    mutable justification: string 
};

[@bs.module "paper"] [@bs.new]
  external create: (BasicTypes.point) => t = "Path";
[@bs.module "paper"] [@bs.new]
  external createFromObject: (pointTextDescription) => t = "PointText";