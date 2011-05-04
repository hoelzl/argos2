//////
// LED
//////
//
// LED_RADIUS: float
// LED_COLOR: color specification -- full name or rgb<>
// IS_EYEBOT_LED: 0 for footbot and handbot, 1 for eyebot

#macro led(LED_RADIUS, LED_COLOR, IS_EYEBOT_LED)


union {

    sphere {
      0, LED_RADIUS
      hollow
     
     #if ((LED_COLOR.x = 0) & (LED_COLOR.y = 0) & (LED_COLOR.z = 0))
        pigment {color White transmit 0.8}

          finish
          { phong 0.9 phong_size 40
            reflection 0.0
          }
          interior
          { ior 1.5
          }

    #else
        texture { pigment { color transmit 1.0 } }
              interior { media { emission color LED_COLOR * 400.0 } }

    #end
    }
   
   



        #if (IS_EYEBOT_LED)
	        #if (!((LED_COLOR.x = 0) & (LED_COLOR.y = 0) & (LED_COLOR.z = 0)))
	            sphere {
	                0, LED_RADIUS * 15
	                hollow
	                pigment {rgbt <1,0,0,1>}
	                interior {
	                media {
	                     emission color LED_COLOR * 5             
	                }
	                }
	                scale <1,1,1>
	            }
            #else
		   // Draw the led core again - just to avoid a warning  (csg require at least two objects)
                    sphere {
                      0, LED_RADIUS
                      hollow
                      pigment {color White transmit 0.8}
                    }
            #end	            
        #else

            #if (!((LED_COLOR.x = 0) & (LED_COLOR.y = 0) & (LED_COLOR.z = 0)))
                sphere {
                    0, LED_RADIUS * 8
                    hollow
                    pigment {rgbt <1,0,0,1>}
                    interior {
                    media {
                         emission color LED_COLOR * 40
                         density {gradient -x scale 0.3}              
                    }
                    }
                    scale <0.5,1.06,1>
                }
            #else
		   // Draw the led core again - just to avoid a warning  (csg require at least two objects)
                    sphere {
                      0, LED_RADIUS
                      hollow
                      pigment {color White transmit 0.8}
                    }
            #end

        #end

}

 
 
#end


