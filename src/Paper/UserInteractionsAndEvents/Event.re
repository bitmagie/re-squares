type t = {
    timeStamp: float,
    modifiers: Key.modifiers
};

exception InvalidType(string);

[@bs.module "paper"][@bs.scope "Event"] external preventDefault: unit => unit = "preventDefault";
[@bs.module "paper"][@bs.scope "Event"] external stopPropagation: unit => unit = "stopPropagation";
[@bs.module "paper"][@bs.scope "Event"] external stop: unit => unit = "stop";
