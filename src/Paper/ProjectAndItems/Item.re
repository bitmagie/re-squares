type t = {
    id: float,
    _type: option(string),
    className: string,
    name: string,    
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
    mutable style: Styling.styleDescription,
    mutable strokeColor: Styling.Color.t,
    mutable fillColor: Styling.Color.t,
};

[@bs.send] external remove: t => bool = "remove";