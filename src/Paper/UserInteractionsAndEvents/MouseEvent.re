
type eventType = [
    |`mousedown
    |`mouseup
    |`mousedrag
    |`click
    |`doubleclick
    |`mousemove
    |`mouseenter
    |`mouseleave
];

let toString = eventType => switch(eventType){
    |`mousedown     => "mousedown"  
    |`mouseup       => "mouseup"    
    |`mousedrag     => "mousedrag"
    |`click         => "click"
    |`doubleclick   => "doubleclick"
    |`mousemove     => "mousemove"
    |`mouseenter    => "mouseenter"
    |`mouseleave    => "mouseleave"
};


let fromString = strEventType => switch(strEventType){
    |"mousedown"    => `mousedown      
    |"mouseup"      => `mouseup        
    |"mousedrag"    => `mousedrag      
    |"click"        => `click          
    |"doubleclick"  => `doubleclick    
    |"mousemove"    => `mousemove      
    |"mouseenter"   => `mouseenter     
    |"mouseleave"   => `mouseleave     
    |_ => raise(Event.InvalidType("invalid event type")) 
};

type t = {
    type_:string,
    point: BasicTypes.point,
    target: Js.Nullable.t(Item.t),
    currentTarget: Item.t,
    delta: BasicTypes.point,
    timeStamp: float,
    modifiers: Key.modifiers,
};

[@bs.module "paper"][@bs.scope "MouseEvent"] external preventDefault: unit => unit = "preventDefault";
[@bs.module "paper"][@bs.scope "MouseEvent"] external stopPropagation: unit => unit = "stopPropagation";
[@bs.module "paper"][@bs.scope "MouseEvent"] external stop: unit => unit = "stop";
