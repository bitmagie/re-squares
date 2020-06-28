
type item = Paths.Path.t;

type t = {
    mutable position: BasicTypes.point,
    children: array(item),
    mutable fillColor: string,
    mutable transformContent: bool,
}
type group= t;

// [@bs.deriving abstract]
// type groupDescription = {
//    [@bs.optional] children: array(item) ,
//    [@bs.optional] transformContent: bool,
//    [@bs.optional] position: BasicTypes.point,
// };



[@bs.module "paper"] [@bs.new]
external create:  unit => group = "Group";


[@bs.set] external setChildren: (group,array(item)) => unit = "children";

[@bs.send] external appendTop: (group, item) => item = "appendTop";
[@bs.send] external addChild: (group, item) => item = "addChild";
