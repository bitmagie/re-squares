type modifiers = {
    shift: bool,
    control: bool,
    alt: bool,
    meta: bool,
    capsLock: bool,
    space: bool,
    option: bool,
    command: bool,
};

type t = [ 
   |`enter
   |`space
   |`shift
   |`control
   |`alt
   |`meta
   |`capsLock
   |`left
   |`up
   |`right
   |`down
   |`escape
   |`delete
   |`invalidKey

];

let toString = key => switch(key){
   |`enter => "enter"
   |`space => "space"
   |`shift => "shift"
   |`control => "control"
   |`alt => "alt"
   |`meta => "meta"
   |`capsLock => "caps-lock"
   |`left => "left"
   |`up => "up"
   |`right => "right"
   |`down => "down"
   |`escape => "escape"
   |`delete => "delete"
   |`invalidKey => ""
};

let fromString = str => switch(str){
   |"enter"      => `enter        
   |"space"      => `space             
   |"shift"      => `shift              
   |"control"    => `control          
   |"alt"        => `alt                 
   |"meta"       => `meta               
   |"caps-lock"  => `capsLock             
   |"left"       => `left                   
   |"up"         => `up                 
   |"right"      => `right                 
   |"down"       => `down                
   |"escape"     => `escape              
   |"delete"     => `delete          
   |_           => `invalidKey
};

 
[@bs.module "paper"] [@bs.scope "Key"] external isDownExternal: string => bool = "isDown";

let isDown = key => toString(key) -> isDownExternal(_);
 
 
 
 
 
 
 
 
 
 
 