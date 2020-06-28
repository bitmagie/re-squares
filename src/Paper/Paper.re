include Project;
include View;
include BasicTypes;
include Styling;
include Paths;

[@bs.val] external document: Js.t({..}) = "document";
[@bs.val] external window: Js.t({..}) = "window";

[@bs.module "paper"] external setup: string => unit = "setup";
[@bs.module "paper"] external version: string = "version";
