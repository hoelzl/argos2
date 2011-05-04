#include "colors.inc"
#include "robots/handbot.pov"
#include "robots/footbot.pov"
#include "shapes_lo.inc"


background{color Blue}

camera {

	location <-0.45,0.2,0.25>      
	sky   <0,0,13>
	right  <-1.33,0,0> 
	look_at <0,0.0,0.1>
}

handbot (
    <0.0,0.0,0>, <0,0,0>, <0,0,0>, <0,0,0>,
    rgb<0,0,0>, rgb<0,0,0>, rgb<0,0,0>, rgb<0,0,0>,
    rgb<0,0,0>, rgb<0,0,0>, rgb<0,0,0>, rgb<0,0,0>,
    rgb<0,0,0>, rgb<0,0,0>, rgb<0,0,0>, rgb<0,0,0>
)


//footbot (
//    <-0.18,0,0.0>, <0,0,0>, rgb<0,0,0>, 0,
//    <0,0,0>,<0,0,0>,0
//    rgb<0,0,0>, rgb<0,0,0>, rgb<0,0,0>, rgb<0,0,0>,
//    rgb<0,0,0>, rgb<0,0,0>, rgb<0,0,0>, rgb<0,0,0>,
//    rgb<0,0,0>, rgb<0,0,0>, rgb<0,0,0>, rgb<0,0,0>
//)


plane { <0, 0, 1>, 0
   pigment {color Grey}
  }
 

light_source { <-0.3, 0,0.3> color White shadowless }




