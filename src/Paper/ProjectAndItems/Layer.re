type t = {
    id: float,
    className: string,
    name: string,    
    mutable locked: bool,
    mutable visible: bool,
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
    mutable style: Styling.styleDescription,
    mutable strokeColor: Styling.Color.t,
    mutable fillColor: Styling.Color.t,
    children: array(Item.t)
};

type layer = t;

[@bs.module "paper"] [@bs.new]
  external create: unit => layer = "Layer";
  
[@bs.send] external activate: layer => unit  = "activate";
[@bs.send] external addChildPath: (layer,Paper.Path.t) => unit  = "addChild";