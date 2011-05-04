#include "colors.inc"
#include "robots/footbot.pov"
#include "robots/led.inc"  
#include "textures.inc"

#include "stones1.inc"
#include "stones2.inc"
#include "stones.inc"
#include "woods.inc"


background{color Blue}

 camera {

  location <0.55,0.25,0.4>  
  sky   <0,0,13>
  right  <-1.33,0,0> 
  look_at <0,0.0,0.15>
 }

  plane { <0, 0, 1>, 0
    texture {Aluminum}
  }


footbot (
    <0.0,-0.1,0.0>, <0,0,180>, rgb<0,0,0>, 0,
    <0,0,0>,<0,0,0>,0
    rgb<0,0,0>, rgb<0,0,0>, rgb<0,0,0>, rgb<0,0,0>,
    rgb<0,0,0>, rgb<0,0,0>, rgb<0,0,0>, rgb<0,0,0>,
    rgb<0,0,0>, rgb<0,0,0>, rgb<0,0,0>, rgb<0,0,0>
)

footbot (
    <0.05,-0.3,0.0>, <0,0,220>, rgb<1,0,0>, 1,
    <0,0,0>,<0,0,0>,0
    rgb<1,0,0>, rgb<1,0,0>, rgb<1,0,0>, rgb<1,0,0>,
    rgb<1,0,0>, rgb<1,0,0>, rgb<1,0,0>, rgb<1,0,0>,
    rgb<1,0,0>, rgb<1,0,0>, rgb<1,0,0>, rgb<1,0,0>
)

footbot (
    <0.0,0.1,0.0>, <0,0,0>, rgb<1,1,0>, 1,
    <0,0,0>,<0,0,0>,1
    rgb<0,0,1>, rgb<0,0,1>, rgb<0,0,1>, rgb<0,0,1>,
    rgb<0,0,1>, rgb<0,0,1>, rgb<0,1,0>, rgb<0,1,0>,
    rgb<0,1,0>, rgb<0,1,0>, rgb<0,1,0>, rgb<0,1,0>
)


plane { <0, 0, 1>, 0
   pigment {
      checker color White, color White
    }
  }
 

light_source { <1, 1,0.3> color White}




