type view={
    size: BasicTypes.size,
    center: BasicTypes.point,
    zoom: float,
    rotation: float,
    scaling: BasicTypes.point,
};

type onMouseMove;
type onFrame;


[@bs.module "paper"] external view: view = "view";

[@bs.module "paper"] [@bs.scope "view"]
external drawView: unit => unit = "draw";

[@bs.set] external setOnMouseMove: (view,MouseEvent.t=>unit) => unit = "onMouseMove";
[@bs.set] external setOnFrame: (view,ToolEvent.t=>unit) => unit = "onFrame";
