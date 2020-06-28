
type eventType=[
    |`keydown
    |`keyup
];

let toString = eventType => switch(eventType){
    |`keydown => "keydown"
    |`keyup => "keyup"
};

let fromString = strEventType => switch(strEventType){
    |"keydown" => `keydown
    |"keyup"   => `keyup 
    |_ => raise(Event.InvalidType("invalid event type")) 
};


type t = {
    type_: string,
    character: string,
    key: string,
    timeStamp: float,
    modifiers: Key.modifiers,
};

[@bs.module "paper"][@bs.scope "KeyEvent"] external preventDefault: unit => unit = "preventDefault";
[@bs.module "paper"][@bs.scope "KeyEvent"] external stopPropagation: unit => unit = "stopPropagation";
[@bs.module "paper"][@bs.scope "KeyEvent"] external stop: unit => unit = "stop";
