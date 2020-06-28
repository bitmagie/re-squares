type eventType = [
    |`mousedown
    |`mouseup
    |`mousemove
    |`mousedrag
];

let toString = eventType => switch(eventType){
    |`mousedown     => "mousedown"  
    |`mouseup       => "mouseup"    
    |`mousedrag     => "mousedrag"
    |`mousemove     => "mousemove"
    
};


let fromString = strEventType => switch(strEventType){
    |"mousedown"    => `mousedown      
    |"mouseup"      => `mouseup        
    |"mousemove"    => `mousemove      
    |"mousedrag"    => `mousedrag     
    |_ => raise(Event.InvalidType("invalid event type")) 
};

type t = {
    _type: string,
    point: BasicTypes.point,
    lastPoint: BasicTypes.point,
    downPoint: BasicTypes.point,
    middlePoint: BasicTypes.point,
    delta: BasicTypes.point,
    count: float,
    item: Js.Nullable.t(Item.t),
    timeStamp: float,
    modifiers: Key.modifiers,
};



[@bs.module "paper"][@bs.scope "ToolEvent"] external preventDefault: unit => unit = "preventDefault";
[@bs.module "paper"][@bs.scope "ToolEvent"] external stopPropagation: unit => unit = "stopPropagation";
[@bs.module "paper"][@bs.scope "ToolEvent"] external stop: unit => unit = "stop";

