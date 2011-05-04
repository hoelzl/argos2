#include "colors.inc"
#include "robots/eyebot.pov"
#include "misc/book.pov"
#include "robots/led.inc"  

background{color Blue}

 camera {
  //location <0.3,0.3,0.6> // to y-axis
  //location <-0.15,0,0.035> // to x-axis
 //location <0.0,0.08,0.08>    // birds-eye
  //location <0.07,0.0,0.08> // to -y-axis
  //location <-0.05,0.1,0.1>
  location <0.8,0.8,0.5>  
//location <0.0,0.0,0.01>  
  sky   <0,0,13>			// fake the sky to make the camera tilt
  right  <-1.33,0,0> 	// describes the direction to the right of the camera
//look_at <0.0,0.0,1>		// should be the last item in the camera statement
 look_at <1,1,0>
 }

book (
    <1,1,0.1>, <0,0,150>
)

eyebot (
    <0.0,0.0,0.1>, <0,0,0>, <0,0,0>, <0,0,340>,<0,0,0>,
    rgb<0,0,0>, rgb<0,0,0>, rgb<0,0,0>, rgb<0,0,0>,
    rgb<0,0,0>, rgb<0,0,0>, rgb<0,0,0>, rgb<0,0,0>,
    rgb<0,0,0>, rgb<0,0,0>, rgb<0,0,0>, rgb<0,0,0>,
    rgb<0,0,0>, rgb<0,1,0>, rgb<0,1,0>, rgb<0,0,0>
)



plane { <0, 0, 1>, 0
   pigment {
      checker color White, color White
    }
  }
 

light_source { <0.5, 0.1,0.5> color White shadowless}




