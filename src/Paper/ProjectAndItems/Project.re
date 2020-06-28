
type item;



[@bs.deriving abstract]
type hitOptions = {
	[@bs.optional] segments: bool,
	[@bs.optional] stroke: bool,
	[@bs.optional] fill: bool,
	[@bs.optional] tolerance: float
};


type layer = {
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
    children: array(Paths.Path.t)
};

type project = {
	activeLayer: layer
};


[@bs.module "paper"] external project: project = "project";
[@bs.set] external setCurrentStyle: (project,Styling.styleDescription) => unit = "currentStyle";

[@bs.send] external hitTest: (project, BasicTypes.Point.t, ~hitOptions:hitOptions) => option(HitResult.t)  = "hitTest";


[@bs.module "paper"] [@bs.new]
  external createLayer: unit => layer = "Layer";
  
[@bs.send] external activateLayer: layer => unit  = "activate";
[@bs.send] external addChildPathToLayer: (layer,Paths.Path.t) => unit  = "addChild";
