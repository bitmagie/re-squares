type tool = {
    mutable minDistance: float,
    mutable maxDistance: float,
    mutable fixedDistance: float,
};

type eventHandler = ToolEvent.t=>unit;


[@bs.module "paper"] [@bs.new]
  external create:  unit => tool = "Tool";

//[@bs.set] external setMinDistance: (tool,eventHandler) => unit = "onOnKeyUp";

[@bs.set] external setOnMouseDown: (tool,eventHandler) => unit = "onMouseDown" ;
[@bs.set] external setOnMouseDrag: (tool,eventHandler) => unit = "onMouseDrag";
[@bs.set] external setOnMouseMove: (tool,eventHandler) => unit = "onMouseMove";
[@bs.set] external setOnMouseUp: (tool,eventHandler) => unit = "onMouseUp";
[@bs.set] external setOnKeyDown: (tool,eventHandler) => unit = "onKeyDown";
[@bs.set] external setOnKeyUp: (tool,eventHandler) => unit = "onOnKeyUp";


[@bs.module "paper"][@bs.scope "tool"] external activate: unit => unit = "activate";
[@bs.module "paper"][@bs.scope "tool"] external remove: unit => unit = "remove";

[@bs.module "paper"][@bs.scope "tool"] external on: (string,eventHandler) => unit = "on";
[@bs.module "paper"][@bs.scope "tool"] external off: (string,eventHandler) => unit = "off";
[@bs.module "paper"][@bs.scope "tool"] external responds: (string) => bool = "responds";

// TODO: Event Handling  emit 
