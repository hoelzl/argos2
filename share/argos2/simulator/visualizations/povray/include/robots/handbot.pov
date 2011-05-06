#include "textures.inc"
#include "common.inc"
#include "textures.inc"
#include "stdinc.inc" 
#include "metals.inc"
#include "shapesq.inc" 
#include "shapes.inc"
#include "shapes_lo.inc"



#macro handbot(
  HANDBOT_POSITION, HANDBOT_ROTATION, HANDBOT_HEAD_ROTATION, HANDBOT_ARM_ROTATION
  HANDBOT_LED1_COLOR,  HANDBOT_LED2_COLOR,  HANDBOT_LED3_COLOR,  HANDBOT_LED4_COLOR,
  HANDBOT_LED5_COLOR,  HANDBOT_LED6_COLOR,  HANDBOT_LED7_COLOR,  HANDBOT_LED8_COLOR,
  HANDBOT_LED9_COLOR,  HANDBOT_LED10_COLOR, HANDBOT_LED11_COLOR, HANDBOT_LED12_COLOR
)






////////////////////////////////////////////////////////////////////////////////////////////
//											  //
// 							HANDBOT MAIN BODY		  //
//											  //
////////////////////////////////////////////////////////////////////////////////////////////    


#local handbot_main_body = object {


	
	#local HANDBOT_MAIN_BODY_CUBIC_PART_WIDTH = 0.12;
	#local HANDBOT_MAIN_BODY_CUBIC_PART_LENGTH = 0.1;
	#local HANDBOT_MAIN_BODY_CUBIC_PART_HEIGHT = 0.085;
	#local HANDBOT_MAIN_BODY_EDGE_RADIUS = 0.008;
	#local HANDBOT_MAIN_BODY_CYLINDER_RADIUS = 0.06;

	#local HANDBOT_BATTERY_WIDTH = 0.019;
	#local HANDBOT_BATTERY_LENGTH = 0.14;
	#local HANDBOT_BATTERY_HEIGHT = 0.047;



	union {
		// Cubic part
		object {
			// Round_Box(A, B, WireRadius, Merge)
			Round_Box(<-HANDBOT_MAIN_BODY_CUBIC_PART_WIDTH / 2, -HANDBOT_MAIN_BODY_CUBIC_PART_LENGTH/2,0>,
			<HANDBOT_MAIN_BODY_CUBIC_PART_WIDTH / 2, HANDBOT_MAIN_BODY_CUBIC_PART_LENGTH/2,HANDBOT_MAIN_BODY_CUBIC_PART_HEIGHT>, 
			HANDBOT_MAIN_BODY_EDGE_RADIUS, 0)
			scale<1,1.04,1>
			translate<0,0.0015,0>
		}

		// The circular part (the rear)
		object {
			//Round_Cylinder(A,B,Radius,EdgeRadius,Merge)
			Round_Cylinder(		
			<0, 0, 0>,
			<0, 0, HANDBOT_MAIN_BODY_CUBIC_PART_HEIGHT>,
			HANDBOT_MAIN_BODY_CYLINDER_RADIUS  ,HANDBOT_MAIN_BODY_EDGE_RADIUS,0)
			translate<0,-HANDBOT_MAIN_BODY_CUBIC_PART_LENGTH/2,0>
			scale<1,0.85,1>
		}
	}
	
}


////////////////////////////////////////////////////////////////////////////////////////////
//											  //
// 							HANDBOT SHIELD			  //
//											  //
////////////////////////////////////////////////////////////////////////////////////////////    


#local handbot_shield = object {


	// The shield behind the head		
	cylinder {
		<0,0.05,0>,
		<0,0.053,0>
		0.05
		scale<1.1,1,1>
		translate<0,0,0.062>
	}
}


////////////////////////////////////////////////////////////////////////////////////////////
//											  //
// 							HANDBOT MAIN BODY DECO		  //
//											  //
////////////////////////////////////////////////////////////////////////////////////////////    


#local handbot_main_body_deco = union {

		// Battery
		union {
			box {
			<-HANDBOT_BATTERY_WIDTH/2, -HANDBOT_BATTERY_LENGTH / 2, -HANDBOT_BATTERY_HEIGHT/2>,
			< HANDBOT_BATTERY_WIDTH/2,  HANDBOT_BATTERY_LENGTH / 2,  HANDBOT_BATTERY_HEIGHT/2>
			pigment{ color White }
			translate <-0.035,-0.025,0.035>
			}

			// The pin
			cylinder{		
			<0, -0.05, 0.0>,
			<0, 0.05, 0.0>,
			0.004
			pigment{ color White }
			translate <-0.035,-0.05,0.035>
			}

		}

		// The black cylinder in the back of the handbot
		cylinder{		
		<0, -0.05, 0.02>,
		<0, 0.05, 0.02>,
		0.01
		pigment{ color Black }
		translate<0.02,-0.05,0>
		}

}



////////////////////////////////////////////////////////////////////////////////////////////
//											  //
// 							HANDBOT GRIPPABLE AREA		  //
//											  //
////////////////////////////////////////////////////////////////////////////////////////////    


#local handbot_grippable_area = union {

	// The cubic area
	object {

		difference {
			box {
			<-HANDBOT_MAIN_BODY_CUBIC_PART_WIDTH / 1.47, -HANDBOT_MAIN_BODY_CUBIC_PART_LENGTH/2,-0.03/2>,
			<HANDBOT_MAIN_BODY_CUBIC_PART_WIDTH / 1.47, HANDBOT_MAIN_BODY_CUBIC_PART_LENGTH/2,0.03/2> 
			}
			union {
				box {
				<-HANDBOT_MAIN_BODY_CUBIC_PART_WIDTH , -HANDBOT_MAIN_BODY_CUBIC_PART_LENGTH,-0.015/2>,
				<HANDBOT_MAIN_BODY_CUBIC_PART_WIDTH, HANDBOT_MAIN_BODY_CUBIC_PART_LENGTH,0.015/2> 
				}

				box {
				<-HANDBOT_MAIN_BODY_CUBIC_PART_WIDTH / 1.47 + 0.003, -HANDBOT_MAIN_BODY_CUBIC_PART_LENGTH,-0.03/2.5>,
				<HANDBOT_MAIN_BODY_CUBIC_PART_WIDTH / 1.47 - 0.003, HANDBOT_MAIN_BODY_CUBIC_PART_LENGTH,0.03/2.5> 
				}
			}

		}
		
		// Now set the transperancy			
		pigment { White transmit 0.3}
		//pigment { White }
		finish {
			ambient .2
			diffuse .2
			phong 0.9 
			phong_size 60
			specular .75
			roughness .1
			reflection {
			.1
			metallic
			}
		}
		translate<0,0,HANDBOT_MAIN_BODY_CUBIC_PART_HEIGHT - 0.008>


	}

	// The circular area
	object {
		difference {
			difference {
				cylinder {
					<0, 0, -0.03/2>,
					<0, 0, 0.03/2>,
					0.082
				}
				cylinder {
					<0, 0, -0.015/2>,
					<0, 0, 0.015/2>,
					0.082 + 0.02
				}

			}

			union {
				// The second cylidner that is carved out to get the 3D effect (hollow part inside)
				cylinder {
				<0, 0, -0.03/2>,
				<0, 0, 0.03/2>,
				0.082 - 0.003
				}

				// Now cut off half of the disc
				box {
					<-0.2,0,0.2>
					<0.2,0.2,-0.2>
				}

			}

			// Now set the transperancy			
			pigment { White transmit 0.3}
			//pigment { White }
			finish {
			ambient .2
			diffuse .2
			phong 0.9 
			phong_size 60
			specular .75
			roughness .1
			reflection {
			.1
			metallic
			}

			}


			
		}

		translate<0,-0.035,HANDBOT_MAIN_BODY_CUBIC_PART_HEIGHT - 0.008>
	}




}



////////////////////////////////////////////////////////////////////////////////////////////
//											  //
// 							HANDBOT LEDS		  //
//											  //
////////////////////////////////////////////////////////////////////////////////////////////    


#local handbot_leds = union {

	object { 
		handbot_main_body 
		scale <1.12,1.01,0.35>
		translate<0,-0.005,HANDBOT_MAIN_BODY_CUBIC_PART_HEIGHT - 0.023>

		// Now set the transperancy			
		pigment { White transmit 0.2}
		//pigment { White }
		finish {
			ambient .2
			diffuse .2
			phong 0.9 
			phong_size 60
			specular .75
			roughness .1
			reflection {
			.1
			metallic
			}
		}
	}


	// LEDS
	#include "robots/led.inc"	
	union {

	#local HANDBOT_LED_RADIUS = 0.01 / 4.0;



	object { led(HANDBOT_LED_RADIUS, HANDBOT_LED1_COLOR, 0) rotate<0,0,0> translate <HANDBOT_MAIN_BODY_CUBIC_PART_WIDTH/2 + 3 * HANDBOT_LED_RADIUS,HANDBOT_MAIN_BODY_CUBIC_PART_LENGTH/2 - 0.01,HANDBOT_MAIN_BODY_CUBIC_PART_HEIGHT-0.01>} 
	object { led(HANDBOT_LED_RADIUS, HANDBOT_LED2_COLOR, 0) rotate<0,0,0> translate <HANDBOT_MAIN_BODY_CUBIC_PART_WIDTH/2 + 3 * HANDBOT_LED_RADIUS,HANDBOT_MAIN_BODY_CUBIC_PART_LENGTH/2 - 0.01- 0.028,HANDBOT_MAIN_BODY_CUBIC_PART_HEIGHT-0.01>} 
	object { led(HANDBOT_LED_RADIUS, HANDBOT_LED3_COLOR, 0) rotate<0,0,0> translate <HANDBOT_MAIN_BODY_CUBIC_PART_WIDTH/2 + 3 * HANDBOT_LED_RADIUS,HANDBOT_MAIN_BODY_CUBIC_PART_LENGTH/2 - 0.01- 0.028 * 2,HANDBOT_MAIN_BODY_CUBIC_PART_HEIGHT-0.01>} 
	object { led(HANDBOT_LED_RADIUS, HANDBOT_LED4_COLOR, 0) rotate<0,0,0> translate <HANDBOT_MAIN_BODY_CUBIC_PART_WIDTH/2 + 3 * HANDBOT_LED_RADIUS,HANDBOT_MAIN_BODY_CUBIC_PART_LENGTH/2 - 0.01- 0.028 * 3,HANDBOT_MAIN_BODY_CUBIC_PART_HEIGHT-0.01>} 
	object { led(HANDBOT_LED_RADIUS, HANDBOT_LED5_COLOR, 0) rotate<0,0,315> translate <HANDBOT_MAIN_BODY_CUBIC_PART_WIDTH/2 + HANDBOT_LED_RADIUS/2 - 0.01,HANDBOT_MAIN_BODY_CUBIC_PART_LENGTH/2 - 0.015 - 0.028 * 4,HANDBOT_MAIN_BODY_CUBIC_PART_HEIGHT-0.01>} 
	object { led(HANDBOT_LED_RADIUS, HANDBOT_LED6_COLOR, 0) rotate<0,0,280> translate <0.02 - HANDBOT_LED_RADIUS/2,HANDBOT_MAIN_BODY_CUBIC_PART_LENGTH/2 - 0.005- 0.028 * 5,HANDBOT_MAIN_BODY_CUBIC_PART_HEIGHT-0.01>} 
	object { led(HANDBOT_LED_RADIUS, HANDBOT_LED7_COLOR, 0) rotate<0,0,270> translate <-0.02 + HANDBOT_LED_RADIUS/2,HANDBOT_MAIN_BODY_CUBIC_PART_LENGTH/2 - 0.005 - 0.028 * 5,HANDBOT_MAIN_BODY_CUBIC_PART_HEIGHT-0.01>} 
	object { led(HANDBOT_LED_RADIUS, HANDBOT_LED8_COLOR, 0) rotate<0,0,225> translate <-HANDBOT_MAIN_BODY_CUBIC_PART_WIDTH/2 - HANDBOT_LED_RADIUS/2 + 0.01,HANDBOT_MAIN_BODY_CUBIC_PART_LENGTH/2 - 0.015- 0.028 * 4,HANDBOT_MAIN_BODY_CUBIC_PART_HEIGHT-0.01>} 
	object { led(HANDBOT_LED_RADIUS, HANDBOT_LED9_COLOR, 0) rotate<0,0,180> translate <-HANDBOT_MAIN_BODY_CUBIC_PART_WIDTH/2- 3 * HANDBOT_LED_RADIUS,HANDBOT_MAIN_BODY_CUBIC_PART_LENGTH/2 - 0.01 - 0.028 * 3,HANDBOT_MAIN_BODY_CUBIC_PART_HEIGHT-0.01>} 
	object { led(HANDBOT_LED_RADIUS, HANDBOT_LED10_COLOR, 0) rotate<0,0,180> translate <-HANDBOT_MAIN_BODY_CUBIC_PART_WIDTH/2- 3 * HANDBOT_LED_RADIUS,HANDBOT_MAIN_BODY_CUBIC_PART_LENGTH/2 - 0.01 - 0.028 * 2,HANDBOT_MAIN_BODY_CUBIC_PART_HEIGHT-0.01>} 
	object { led(HANDBOT_LED_RADIUS, HANDBOT_LED11_COLOR, 0) rotate<0,0,180> translate <-HANDBOT_MAIN_BODY_CUBIC_PART_WIDTH/2- 3 * HANDBOT_LED_RADIUS,HANDBOT_MAIN_BODY_CUBIC_PART_LENGTH/2 - 0.01 - 0.028,HANDBOT_MAIN_BODY_CUBIC_PART_HEIGHT-0.01>} 
	object { led(HANDBOT_LED_RADIUS, HANDBOT_LED12_COLOR, 0) rotate<0,0,180> translate <-HANDBOT_MAIN_BODY_CUBIC_PART_WIDTH/2- 3 * HANDBOT_LED_RADIUS,HANDBOT_MAIN_BODY_CUBIC_PART_LENGTH/2 - 0.01,HANDBOT_MAIN_BODY_CUBIC_PART_HEIGHT-0.01>}
	}


}


  ////////////////////////////////////////////////////////////////////////////////////////////
  //												//
  // 							RANGE AND BEARING  MODULE		//
  //												//
  ////////////////////////////////////////////////////////////////////////////////////////////
  
  
  #local HANDBOT_RANGE_AND_BEARING_WHITE_PART_HEIGHT = 0.013;
  #local HANDBOT_RANGE_AND_BEARING_BLUE_PART_HEIGHT =  0.0015;
  #local HANDBOT_BASE_RADIUS = 0.085;
  #local HANDBOT_DOCKING_MINOR_RADIUS = 0.02;
  #local HANDBOT_DOCKING_MAJOR_RADIUS = HANDBOT_BASE_RADIUS - 0.01;

#local handbot_range_and_bearing_module = difference {

union {

    // 2D Sensors and Emitters
	  difference {
	    torus {
	      HANDBOT_DOCKING_MAJOR_RADIUS - 0.0065, HANDBOT_DOCKING_MINOR_RADIUS - 0.0055
	      rotate x * 90
	     translate z * 0.007	
	    }
	   union {
		cylinder {
		<0, 0, -0.01>,
		<0, 0, 0.01 + HANDBOT_RANGE_AND_BEARING_WHITE_PART_HEIGHT/3>,
		HANDBOT_DOCKING_MAJOR_RADIUS + 0.02

		}



		#local HANDBOT_RAB_SENSOR_CARVED_OUT_BOXES = 8;
		#local HANDBOT_RAB_SENSOR_CARVED_OUT_BOX_ANGLE = 360 / HANDBOT_RAB_SENSOR_CARVED_OUT_BOXES;

		#macro handbot_rab_sensor_carved_out_box(RAB_SENSOR_CARVED_OUT_BOX_ANGLE)


			#local EYEBOT_RAB_SENSOR_CARVED_OUT_BOX_LENGTH_WIDTH = 0.01;
			// the box that is carved out
			box {                 
			<-EYEBOT_RAB_SENSOR_CARVED_OUT_BOX_LENGTH_WIDTH /2,-EYEBOT_RAB_SENSOR_CARVED_OUT_BOX_LENGTH_WIDTH /2,-EYEBOT_RAB_SENSOR_CARVED_OUT_BOX_LENGTH_WIDTH /2>,
			<EYEBOT_RAB_SENSOR_CARVED_OUT_BOX_LENGTH_WIDTH /2,EYEBOT_RAB_SENSOR_CARVED_OUT_BOX_LENGTH_WIDTH /2,EYEBOT_RAB_SENSOR_CARVED_OUT_BOX_LENGTH_WIDTH /2>
			pigment { color White}
			translate <-HANDBOT_DOCKING_MAJOR_RADIUS,0,HANDBOT_RANGE_AND_BEARING_WHITE_PART_HEIGHT + 0.008>
			}


			rotate z * RAB_SENSOR_CARVED_OUT_BOX_ANGLE
		#end


		object { handbot_rab_sensor_carved_out_box(360) }
		object { handbot_rab_sensor_carved_out_box(360 -     HANDBOT_RAB_SENSOR_CARVED_OUT_BOX_ANGLE  ) }
		object { handbot_rab_sensor_carved_out_box(360 -(2 * HANDBOT_RAB_SENSOR_CARVED_OUT_BOX_ANGLE) ) }
		object { handbot_rab_sensor_carved_out_box(360 -(3 * HANDBOT_RAB_SENSOR_CARVED_OUT_BOX_ANGLE) ) }
		object { handbot_rab_sensor_carved_out_box(360 -(4 * HANDBOT_RAB_SENSOR_CARVED_OUT_BOX_ANGLE) ) }
		object { handbot_rab_sensor_carved_out_box(360 -(5 * HANDBOT_RAB_SENSOR_CARVED_OUT_BOX_ANGLE) ) }
		object { handbot_rab_sensor_carved_out_box(360 -(6 * HANDBOT_RAB_SENSOR_CARVED_OUT_BOX_ANGLE) ) }
		object { handbot_rab_sensor_carved_out_box(360 - (7 * HANDBOT_RAB_SENSOR_CARVED_OUT_BOX_ANGLE) ) }




	}
		pigment {color White}
	   }      



      #local HANDBOT_RAB_SENSORS = 8;
      #local HANDBOT_RAB_SENSOR_ANGLE = 360 / HANDBOT_RAB_SENSORS;
      #local HANDBOT_RAB_SENSOR_PHASE = 0;
      #local HANDBOT_RAB_SENSOR_RADIUS = 0.0020;


	// Sensors
      #macro handbot_rab_sensor(RAB_SENSOR_ANGLE)


	union {


		#local EYEBOT_RAB_SENSOR_BOX_LENGTH_WIDTH = 0.005;
		box {                 
		   	<-EYEBOT_RAB_SENSOR_BOX_LENGTH_WIDTH/2,-EYEBOT_RAB_SENSOR_BOX_LENGTH_WIDTH/2,-EYEBOT_RAB_SENSOR_BOX_LENGTH_WIDTH / 1.5>,
		   	<EYEBOT_RAB_SENSOR_BOX_LENGTH_WIDTH/2,EYEBOT_RAB_SENSOR_BOX_LENGTH_WIDTH/2,EYEBOT_RAB_SENSOR_BOX_LENGTH_WIDTH/ 1.5>
			pigment { color Black}
		}


		object{
		Round_Cylinder
		(<-0.01, 0, 0>, <0.004, 0, 0>, HANDBOT_RAB_SENSOR_RADIUS + 0.000001, HANDBOT_RAB_SENSOR_RADIUS,1)
		pigment {color Black transmit 0.4}

		  finish
		  { phong 0.9 phong_size 40  // A highlight
		    reflection 0.0  // Glass reflects a bit
		  }
		  interior
		  { ior 1.5 // Glass refraction
		  }
		} 

		translate <HANDBOT_DOCKING_MAJOR_RADIUS - 0.003,0,HANDBOT_RANGE_AND_BEARING_WHITE_PART_HEIGHT + 0.006>
		rotate z * RAB_SENSOR_ANGLE

	}
      #end

      object { handbot_rab_sensor(360 -                	         HANDBOT_RAB_SENSOR_PHASE) }
      object { handbot_rab_sensor(360 -     HANDBOT_RAB_SENSOR_ANGLE  - HANDBOT_RAB_SENSOR_PHASE) }
      object { handbot_rab_sensor(360 -(2 * HANDBOT_RAB_SENSOR_ANGLE) - HANDBOT_RAB_SENSOR_PHASE) }
      object { handbot_rab_sensor(360 -(3 * HANDBOT_RAB_SENSOR_ANGLE) - HANDBOT_RAB_SENSOR_PHASE) }
      object { handbot_rab_sensor(360 -(4 * HANDBOT_RAB_SENSOR_ANGLE) - HANDBOT_RAB_SENSOR_PHASE) }
      object { handbot_rab_sensor(360 -(5 * HANDBOT_RAB_SENSOR_ANGLE) - HANDBOT_RAB_SENSOR_PHASE) }
      object { handbot_rab_sensor(360 -(6 * HANDBOT_RAB_SENSOR_ANGLE) - HANDBOT_RAB_SENSOR_PHASE) }
      object { handbot_rab_sensor(360 - (7 * HANDBOT_RAB_SENSOR_ANGLE) - HANDBOT_RAB_SENSOR_PHASE) }





       // Emitters 
     #local HANDBOT_RAB_EMITTERS = 16;
     #local HANDBOT_RAB_EMITTER_RADIUS = HANDBOT_RAB_SENSOR_RADIUS / 1.7;
     #local HANDBOT_RAB_EMITTER_ANGLE = 360 / HANDBOT_RAB_EMITTERS;
     #local HANDBOT_RAB_EMITTER_PHASE = HANDBOT_RAB_EMITTER_ANGLE / 2;

      #macro handbot_rab_emitter(RAB_EMITTER_ANGLE)

	object{
	  Round_Cylinder
		(<-0.01, 0, 0>, <0.003, 0, 0>, HANDBOT_RAB_EMITTER_RADIUS + 0.000001, HANDBOT_RAB_EMITTER_RADIUS,1)
		pigment {color Black transmit 0.8}

		  finish
		  { phong 0.9 phong_size 40  // A highlight
		    reflection 0.0  // Glass reflects a bit
		  }
		  interior
		  { ior 1.5 // Glass refraction
		  }

		translate <HANDBOT_DOCKING_MAJOR_RADIUS,0,HANDBOT_RANGE_AND_BEARING_WHITE_PART_HEIGHT + 0.008>
		rotate z * RAB_EMITTER_ANGLE
	} 
      #end

      object { handbot_rab_emitter(360 -                	         HANDBOT_RAB_EMITTER_PHASE) }
      object { handbot_rab_emitter(360 -     HANDBOT_RAB_EMITTER_ANGLE  - HANDBOT_RAB_EMITTER_PHASE) }
      object { handbot_rab_emitter(360 -(2 * HANDBOT_RAB_EMITTER_ANGLE) - HANDBOT_RAB_EMITTER_PHASE) }
      object { handbot_rab_emitter(360 -(3 * HANDBOT_RAB_EMITTER_ANGLE) - HANDBOT_RAB_EMITTER_PHASE) }
      object { handbot_rab_emitter(360 -(4 * HANDBOT_RAB_EMITTER_ANGLE) - HANDBOT_RAB_EMITTER_PHASE) }
      object { handbot_rab_emitter(360 -(5 * HANDBOT_RAB_EMITTER_ANGLE) - HANDBOT_RAB_EMITTER_PHASE) }
      object { handbot_rab_emitter(360 -(6 * HANDBOT_RAB_EMITTER_ANGLE) - HANDBOT_RAB_EMITTER_PHASE) }
      object { handbot_rab_emitter(360 - (7 * HANDBOT_RAB_EMITTER_ANGLE) - HANDBOT_RAB_EMITTER_PHASE) }
      object { handbot_rab_emitter(360 -(8 * HANDBOT_RAB_EMITTER_ANGLE) - HANDBOT_RAB_EMITTER_PHASE) }
      object { handbot_rab_emitter(360 -(9 * HANDBOT_RAB_EMITTER_ANGLE) - HANDBOT_RAB_EMITTER_PHASE) }
      object { handbot_rab_emitter(360 -(10 * HANDBOT_RAB_EMITTER_ANGLE) - HANDBOT_RAB_EMITTER_PHASE) }
      object { handbot_rab_emitter(360 -(11 * HANDBOT_RAB_EMITTER_ANGLE) - HANDBOT_RAB_EMITTER_PHASE) }
      object { handbot_rab_emitter(360 -(12 * HANDBOT_RAB_EMITTER_ANGLE) - HANDBOT_RAB_EMITTER_PHASE) }
      object { handbot_rab_emitter(360 - (13 * HANDBOT_RAB_EMITTER_ANGLE) - HANDBOT_RAB_EMITTER_PHASE) }
      object { handbot_rab_emitter(360 -(14 * HANDBOT_RAB_EMITTER_ANGLE) - HANDBOT_RAB_EMITTER_PHASE) }
      object { handbot_rab_emitter(360 - (15 * HANDBOT_RAB_EMITTER_ANGLE) - HANDBOT_RAB_EMITTER_PHASE) }






 	// 3D Sensors and Emitters
      cylinder {
        <0, 0, 0.022>,
        <0, 0, 0.022 + HANDBOT_RANGE_AND_BEARING_BLUE_PART_HEIGHT>,
        HANDBOT_DOCKING_MAJOR_RADIUS
        pigment {
          image_map {
            png "textures/robots/swarmanoid/handbot/rab_circuit.png"
            once
            interpolate 2
            
          }
          scale <.15, .15, .15>
          translate <-0.075,-0.075,0>
         }
      }
    
   }



	// Carve out the part at the bottom of the launcher tube
	object { Egg  // = Egg_Shape (1.15,1.55)
		pigment {color Grey}
		rotate < 0,0, 180>
		scale<0.037,0.04,0.045>
		translate < 0,0.065, 0.04>
        }



}

////////////////////////////////////////////////////////////////////////////////////////////
//											  //
// 							HANDBOT LAUNCHER MODULE		  //
//											  //
////////////////////////////////////////////////////////////////////////////////////////////  
#local handbot_launcher_module = union {

	// The launcher tube
	cylinder {
		<0,0,0>
		<0,0,0.15>
		0.02
		pigment {color Black}
	}


    // The fan
    #local handbot_fan = union {
		#local HANDBOT_FAN_RADIUS_OUTER_CYLINDER = 0.031;
		#local HANDBOT_FAN_RADIUS_INNER_CYLINDER =  HANDBOT_FAN_RADIUS_OUTER_CYLINDER - 0.01 * 0.1;
		#local HANDBOT_FAN_CYLINDER_LENGTH =  0.04;
		#local HANDBOT_FAN_HEIGHT = 0.075;
		#local HANDBOT_FAN_DISTANCE_BETWEEN_EACH_OTHER = 0.12;
		
	    // The cover
	    difference {
	       union  {
	       	// The black part
	        cylinder  {
	                <0,-HANDBOT_FAN_CYLINDER_LENGTH/2,0>,
	                <0,HANDBOT_FAN_CYLINDER_LENGTH/2,0>
	                HANDBOT_FAN_RADIUS_OUTER_CYLINDER
	                pigment {color Black}
	            }
	        // The white part
		        cylinder  {
		                <0,-HANDBOT_FAN_CYLINDER_LENGTH/20,0>,
		                <0,HANDBOT_FAN_CYLINDER_LENGTH/20,0>
		                HANDBOT_FAN_RADIUS_OUTER_CYLINDER * 1.2
		                pigment {color White}
		                translate <0,0.005,0>
		            }	 
	        }
	        cylinder  {
	                <0,-HANDBOT_FAN_CYLINDER_LENGTH * 2,0>,
	                <0,HANDBOT_FAN_CYLINDER_LENGTH * 2,0>
	                HANDBOT_FAN_RADIUS_INNER_CYLINDER
	            }

	    }
	    // The fan
	    object {
	    	#declare Stren = 1.00;
			#declare R1 = 1.00;
			blob{
			 threshold 0.65
			 // center
			 sphere{ <0,0,0>, R1, Stren scale<3,6,3>  pigment { color Yellow} }
			 // wings
			 #local Nr = 0; 
			 #local EndNr = 6; 
			 #while (Nr< EndNr)
			  cylinder{<0,0,0>,< 1.5,0,0>, R1, Stren
				    scale<1,0.3,1>
				    rotate<-30,0,0>
				    translate<1.25,0,0>
				    rotate<0,Nr * 360/EndNr,0>}
			 #local Nr = Nr + 1; 
			 #end
			 scale 0.0095
			 rotate<0,0,0>
			 translate<0,0,0>
			pigment { color Yellow}
		    }
	    
       }
    }
    
    // Placing the fans
    object { handbot_fan         translate <-HANDBOT_FAN_DISTANCE_BETWEEN_EACH_OTHER/2,-HANDBOT_FAN_CYLINDER_LENGTH/1.5,HANDBOT_FAN_HEIGHT> }
    object { handbot_fan         translate <HANDBOT_FAN_DISTANCE_BETWEEN_EACH_OTHER/2,-HANDBOT_FAN_CYLINDER_LENGTH/1.5,HANDBOT_FAN_HEIGHT> }
    
           
      // The white connecting part between the fans
      union {
	      box {
	    	<-HANDBOT_FAN_DISTANCE_BETWEEN_EACH_OTHER/4,-HANDBOT_FAN_CYLINDER_LENGTH/20,-HANDBOT_FAN_RADIUS_INNER_CYLINDER / 2>,
	    	<HANDBOT_FAN_DISTANCE_BETWEEN_EACH_OTHER/4,HANDBOT_FAN_CYLINDER_LENGTH/20,HANDBOT_FAN_RADIUS_INNER_CYLINDER / 2>
	    	pigment {color White}
	    	translate <0,-0.02,HANDBOT_FAN_HEIGHT>
	      }
	      	cylinder {
			<0,0,-HANDBOT_FAN_RADIUS_INNER_CYLINDER / 8>
			<0,0,HANDBOT_FAN_RADIUS_INNER_CYLINDER / 8>
			0.023
			pigment {color White}
			translate <0,0,HANDBOT_FAN_HEIGHT>
			}
      }
    
	// The magnet
	cylinder {
		<0,0,0>
		<0,0,0.035>
		0.015
		pigment {color Black}
		translate <0,0,0.15>
	}


	// The  umbrella shaped plastic piece on top
	merge {
		difference {
			object{ Bicorn
				sturm
				scale 0.06
		       }
			object{ Bicorn
				sturm
				scale <0.055,0.055,0.055>
		       }
			pigment {color MediumGoldenrod transmit 0.2}
			rotate <-90,0,0>
			translate <0,0,0.15 + 0.04>
		}

		cylinder {
			<0,0,0>
			<0,0,0.025>
			0.03
			pigment {color MediumGoldenrod transmit 0.2}
			translate <0,0,0.15 - 0.025/2>
		}
	}

	// The smaller tube next to the launcher
	cylinder {
	<0,0,0>
	<0,0,0.035>
	0.0075
	pigment {color Black}
	translate<0,-0.03,0>
	}

	// Distance scanner facing the ceiling
	# local HANDBOT_DISTANCE_SCANNER_WIDTH = 0.02;
	# local HANDBOT_DISTANCE_SCANNER_LENGTH = 0.04;
	# local HANDBOT_DISTANCE_SCANNER_HEIGHT = 0.04;

	box {
		<-HANDBOT_DISTANCE_SCANNER_WIDTH/2,-HANDBOT_DISTANCE_SCANNER_LENGTH/2,0>
		<HANDBOT_DISTANCE_SCANNER_WIDTH/2,HANDBOT_DISTANCE_SCANNER_LENGTH/2,HANDBOT_DISTANCE_SCANNER_HEIGHT>
		pigment {color Black}
		translate<0,-0.075,0>
	}

	translate<0,0,HANDBOT_MAIN_BODY_CUBIC_PART_HEIGHT>
}


////////////////////////////////////////////////////////////////////////////////////////////
//											  //
// 							HANDBOT ARMS			  //
//											  //
////////////////////////////////////////////////////////////////////////////////////////////  

#local HANDBOT_ARM_WIDTH = 0.01;
#local HANDBOT_ARM_LENGTH = 0.138;
#local HANDBOT_ARM_HEIGHT = 0.01;

#local HANDBOT_ARM_WIDTH_OFFSET = 0.015;
#local HANDBOT_ARM_LENGTH_OFFSET = 0.01;
#local HANDBOT_ARM_LENGTH_OFFSET_BETWEEN_ULNA_AND_SPOKE = 0.025;

#local HANDBOT_ARM_ULNA_SPOKE_CONNECTION_BOX_WIDTH = 0.015;
#local HANDBOT_ARM_ULNA_SPOKE_CONNECTION_BOX_HEIGHT= 0.015;
#local HANDBOT_ARM_ULNA_SPOKE_CONNECTION_BOX_LENGTH = 0.04;



#local handbot_wrist = union {

	cylinder {
		<0,0,0>,
		<0,0.004,0>,
		0.005
		pigment {color Wheat}
	}

	cylinder {
		<0,0.004,0>,
		<0,0.008,0>,
		0.008
		pigment {color Wheat}
	}

	difference {
		prism {
			linear_sweep
			linear_spline
			0, // sweep the following shape from here ...
			0.041, // ... up through here
			7, // the number of points making up the shape ...
			<0.03,0.03>, <-0.03,0.03>, <-0.03,0.03-0.011>, <-0.02,-0.03>, <0.02,-0.03>, <0.03,0.03-0.011>,<0.03,0.03>
			pigment { Black }
			rotate <-90,0,0>
			translate<0, HANDBOT_ARM_LENGTH_OFFSET_BETWEEN_ULNA_AND_SPOKE/2 + HANDBOT_ARM_LENGTH_OFFSET/2 + HANDBOT_ARM_ULNA_SPOKE_CONNECTION_BOX_LENGTH/2,0.02>

		}

		box {
		 <-1,0.02,-0.038/2>,
		 <1,0.065,0.038/2>
		pigment {color Black}
		}

	}

	// Cylinders inside the wrist
	cylinder {
		<0,0.008,0>,
		<0,0.066,0>,
		0.006
		pigment {color White}
		translate<-0.01,0,-0.005>
	}
	cylinder {
		<0,0.008,0>,
		<0,0.066,0>,
		0.006
		pigment {color White}
		translate<0.01,0,0.005>
	}

	// The final plate for the proximity sensors
	box {
		<-0.02,0.001,0.03>,
		<0.02,-0.001,-0.03>
		pigment {color Black}
		translate<0,0.066,0>
	}

}


#local HANDBOT_GRIPPER_CLAW_WIDTH = 0.005;
#local HANDBOT_GRIPPER_CLAW_LENGTH = 0.058;
#local HANDBOT_GRIPPER_CLAW_HEIGHT = 0.038;



#local handbot_claw = object {

	difference {
		Round_Box(
			<-HANDBOT_GRIPPER_CLAW_WIDTH ,-HANDBOT_GRIPPER_CLAW_LENGTH/2,-HANDBOT_GRIPPER_CLAW_HEIGHT/2>,
			<HANDBOT_GRIPPER_CLAW_WIDTH ,HANDBOT_GRIPPER_CLAW_LENGTH/2,HANDBOT_GRIPPER_CLAW_HEIGHT/2>,
			0.003,
			0
		)
		Round_Box(
			<-HANDBOT_GRIPPER_CLAW_WIDTH-0.005 ,-HANDBOT_GRIPPER_CLAW_LENGTH/2+0.005,-HANDBOT_GRIPPER_CLAW_HEIGHT/2+0.005>,
			<HANDBOT_GRIPPER_CLAW_WIDTH+0.005,HANDBOT_GRIPPER_CLAW_LENGTH/2+0.005,HANDBOT_GRIPPER_CLAW_HEIGHT/2-0.005>,
			0.003,
			0
		)
	}


}


#local handbot_right_claw = union {

	object {
	handbot_claw
		rotate <0,0,-10>
	}
	difference {
		union {

			// The horizontal part
			object {
				Round_Box(
					<-HANDBOT_GRIPPER_CLAW_WIDTH-0.0019 ,-HANDBOT_GRIPPER_CLAW_LENGTH/2+0.006,-HANDBOT_GRIPPER_CLAW_HEIGHT/2+0.006>,
					<HANDBOT_GRIPPER_CLAW_WIDTH+0.002,HANDBOT_GRIPPER_CLAW_LENGTH/2+0.006,HANDBOT_GRIPPER_CLAW_HEIGHT/2-0.006>,
					0.003,
					0
				)
				pigment {color Wheat}
			}


			object {
				Round_Box(
					<-HANDBOT_GRIPPER_CLAW_WIDTH-0.002 ,-HANDBOT_GRIPPER_CLAW_LENGTH/2+0.006,-HANDBOT_GRIPPER_CLAW_HEIGHT/2+0.006>,
					<-HANDBOT_GRIPPER_CLAW_WIDTH-0.0019,HANDBOT_GRIPPER_CLAW_LENGTH/2+0.006,HANDBOT_GRIPPER_CLAW_HEIGHT/2-0.006>,
					0.003,
					0
				)
				pigment {color Red}
			}




			// The vertical part
			object {
				Round_Box(
					<-HANDBOT_GRIPPER_CLAW_WIDTH-0.0019,0,-HANDBOT_GRIPPER_CLAW_HEIGHT/2>,
					<-HANDBOT_GRIPPER_CLAW_WIDTH,0.03,HANDBOT_GRIPPER_CLAW_HEIGHT/2>,
					0.003,
					0
				)
				pigment {color Wheat}
	
			}

			object {
				Round_Box(
					<-HANDBOT_GRIPPER_CLAW_WIDTH-0.002,0,-HANDBOT_GRIPPER_CLAW_HEIGHT/2>,
					<-HANDBOT_GRIPPER_CLAW_WIDTH-0.0019 ,0.03,HANDBOT_GRIPPER_CLAW_HEIGHT/2>,
					0.003,
					0
				)
				pigment {color Red}
	
			}


			rotate <0,0,-20>
			translate <-0.008,0,0>
		}




		// The proximity sensors in the claw
		union {

			cylinder {
				<-HANDBOT_GRIPPER_CLAW_WIDTH-0.003,0,0>,
				<-1,0,0>
				0.004
				pigment {color Black}
				translate <0,-0.008,0>
			}

			cylinder {
				<-HANDBOT_GRIPPER_CLAW_WIDTH-0.003,0,0>,
				<-1,0,0>
				0.004
				pigment {color Black}
				translate <0,-0.008 + 0.018,0>
			}

			cylinder {
				<-HANDBOT_GRIPPER_CLAW_WIDTH-0.002,0,0>,
				<-1,0,0>
				0.004
				pigment {color Black}
				translate <0,-0.008 + 0.018 + 0.018,0>
			}

		}

	}

	pigment {color Wheat}
}



#local handbot_left_claw = union {


	object {
	handbot_claw
		rotate <0,0,10>
	}

	difference {
		union {
			// The horizontal part
			object {
				Round_Box(
					<-HANDBOT_GRIPPER_CLAW_WIDTH-0.002 ,-HANDBOT_GRIPPER_CLAW_LENGTH/2+0.006,-HANDBOT_GRIPPER_CLAW_HEIGHT/2+0.006>,
					<HANDBOT_GRIPPER_CLAW_WIDTH+0.0019,HANDBOT_GRIPPER_CLAW_LENGTH/2+0.006,HANDBOT_GRIPPER_CLAW_HEIGHT/2-0.006>,
					0.003,
					0
				)
				pigment {color Wheat}
			}

			object {
				Round_Box(
					<HANDBOT_GRIPPER_CLAW_WIDTH+0.0019,-HANDBOT_GRIPPER_CLAW_LENGTH/2+0.006,-HANDBOT_GRIPPER_CLAW_HEIGHT/2+0.006>,
					<HANDBOT_GRIPPER_CLAW_WIDTH+0.002,HANDBOT_GRIPPER_CLAW_LENGTH/2+0.006,HANDBOT_GRIPPER_CLAW_HEIGHT/2-0.006>,
					0.003,
					0
				)
				pigment {color Red}
			}

			// The vertical part
			object {
				Round_Box(
					<-HANDBOT_GRIPPER_CLAW_WIDTH ,0,-HANDBOT_GRIPPER_CLAW_HEIGHT/2>,
					<HANDBOT_GRIPPER_CLAW_WIDTH+0.0019,0.03,HANDBOT_GRIPPER_CLAW_HEIGHT/2>,
					0.003,
					0
				)
				pigment {color Wheat}
	
			}

			object {
				Round_Box(
					<HANDBOT_GRIPPER_CLAW_WIDTH+0.0019,0,-HANDBOT_GRIPPER_CLAW_HEIGHT/2>,
					<HANDBOT_GRIPPER_CLAW_WIDTH+0.002,0.03,HANDBOT_GRIPPER_CLAW_HEIGHT/2>,
					0.003,
					0
				)
				pigment {color Red}
	
			}

			rotate <0,0,20>
			translate <0.008,0,0>

		}

		// The proximity sensors in the claw
		union {

			cylinder {
				<HANDBOT_GRIPPER_CLAW_WIDTH+0.002,0,0>,
				<1,0,0>
				0.004
				pigment {color Black}
				translate <0,-0.008,0>
			}

			cylinder {
				<HANDBOT_GRIPPER_CLAW_WIDTH+0.002,0,0>,
				<1,0,0>
				0.004
				pigment {color Black}
				translate <0,-0.008 + 0.018,0>
			}

			cylinder {
				<HANDBOT_GRIPPER_CLAW_WIDTH+0.002,0,0>,
				<1,0,0>
				0.004
				pigment {color Black}
				translate <0,-0.008 + 0.018 + 0.018,0>
			}
		}

	}
	pigment {color Wheat}
}


#local handbot_right_arm = union {

	merge {
		union {
			// The first bar (the one closer to the head)
			box {
				<HANDBOT_ARM_WIDTH_OFFSET,HANDBOT_ARM_WIDTH /2 + HANDBOT_ARM_LENGTH_OFFSET,-HANDBOT_ARM_HEIGHT/2>,
				<HANDBOT_ARM_WIDTH_OFFSET + HANDBOT_ARM_LENGTH,-HANDBOT_ARM_WIDTH /2 + HANDBOT_ARM_LENGTH_OFFSET,HANDBOT_ARM_HEIGHT/2>
			}

			box {
				<HANDBOT_ARM_WIDTH_OFFSET,HANDBOT_ARM_WIDTH /2 + HANDBOT_ARM_LENGTH_OFFSET + HANDBOT_ARM_LENGTH_OFFSET_BETWEEN_ULNA_AND_SPOKE,-HANDBOT_ARM_HEIGHT/2>,
				<HANDBOT_ARM_WIDTH_OFFSET + HANDBOT_ARM_LENGTH,-HANDBOT_ARM_WIDTH /2 + HANDBOT_ARM_LENGTH_OFFSET  + HANDBOT_ARM_LENGTH_OFFSET_BETWEEN_ULNA_AND_SPOKE,HANDBOT_ARM_HEIGHT/2>
			}
			pigment {color Black}
		}



		object {
			// Round_Box(A, B, WireRadius, Merge)
			Round_Box(

				<	HANDBOT_ARM_WIDTH_OFFSET  + HANDBOT_ARM_LENGTH - HANDBOT_ARM_ULNA_SPOKE_CONNECTION_BOX_WIDTH/2,
					HANDBOT_ARM_LENGTH_OFFSET_BETWEEN_ULNA_AND_SPOKE/2 + HANDBOT_ARM_LENGTH_OFFSET + HANDBOT_ARM_ULNA_SPOKE_CONNECTION_BOX_LENGTH/2,
					- HANDBOT_ARM_ULNA_SPOKE_CONNECTION_BOX_HEIGHT/2
				>,
				<	HANDBOT_ARM_WIDTH_OFFSET  + HANDBOT_ARM_LENGTH + HANDBOT_ARM_ULNA_SPOKE_CONNECTION_BOX_WIDTH/2,
					HANDBOT_ARM_LENGTH_OFFSET_BETWEEN_ULNA_AND_SPOKE/2 + HANDBOT_ARM_LENGTH_OFFSET - HANDBOT_ARM_ULNA_SPOKE_CONNECTION_BOX_LENGTH/2,
					HANDBOT_ARM_ULNA_SPOKE_CONNECTION_BOX_HEIGHT/2
				>
				0.0005, 
				0)
			pigment {color White}
		}

		
	}


	object { 
		handbot_wrist
		translate<-HANDBOT_ARM_WIDTH_OFFSET  - HANDBOT_ARM_LENGTH, HANDBOT_ARM_LENGTH_OFFSET_BETWEEN_ULNA_AND_SPOKE/2 + HANDBOT_ARM_LENGTH_OFFSET + HANDBOT_ARM_ULNA_SPOKE_CONNECTION_BOX_LENGTH/2,0>
	}



	// The left claw
	object {
		handbot_left_claw
		translate<HANDBOT_ARM_WIDTH_OFFSET  + HANDBOT_ARM_LENGTH - 0.035, HANDBOT_ARM_LENGTH_OFFSET_BETWEEN_ULNA_AND_SPOKE/2 + HANDBOT_ARM_LENGTH_OFFSET + HANDBOT_ARM_ULNA_SPOKE_CONNECTION_BOX_LENGTH/2 + 0.095,0>

	}

	// The right claw
	object {
		handbot_right_claw
		translate<HANDBOT_ARM_WIDTH_OFFSET  + HANDBOT_ARM_LENGTH + 0.035, HANDBOT_ARM_LENGTH_OFFSET_BETWEEN_ULNA_AND_SPOKE/2 + HANDBOT_ARM_LENGTH_OFFSET + HANDBOT_ARM_ULNA_SPOKE_CONNECTION_BOX_LENGTH/2 + 0.095,0>

	}


rotate HANDBOT_ARM_ROTATION

}

#local handbot_left_arm = union {

	merge {
		union {
			// The first bar (the one closer to the head)
			box {
				<-HANDBOT_ARM_WIDTH_OFFSET,HANDBOT_ARM_WIDTH /2 + HANDBOT_ARM_LENGTH_OFFSET,-HANDBOT_ARM_HEIGHT/2>,
				<-HANDBOT_ARM_WIDTH_OFFSET - HANDBOT_ARM_LENGTH,-HANDBOT_ARM_WIDTH /2 + HANDBOT_ARM_LENGTH_OFFSET,HANDBOT_ARM_HEIGHT/2>
			}
			// The second bar
			box {
				<-HANDBOT_ARM_WIDTH_OFFSET,HANDBOT_ARM_WIDTH /2 + HANDBOT_ARM_LENGTH_OFFSET + HANDBOT_ARM_LENGTH_OFFSET_BETWEEN_ULNA_AND_SPOKE,-HANDBOT_ARM_HEIGHT/2>,
				<-HANDBOT_ARM_WIDTH_OFFSET - HANDBOT_ARM_LENGTH,-HANDBOT_ARM_WIDTH /2 + HANDBOT_ARM_LENGTH_OFFSET  + HANDBOT_ARM_LENGTH_OFFSET_BETWEEN_ULNA_AND_SPOKE,HANDBOT_ARM_HEIGHT/2>
			}
			pigment {color Black}
		}


		// The connecting piece at the end of the bars
		object {
			// Round_Box(A, B, WireRadius, Merge)
			Round_Box(

				<	-HANDBOT_ARM_WIDTH_OFFSET  - HANDBOT_ARM_LENGTH - HANDBOT_ARM_ULNA_SPOKE_CONNECTION_BOX_WIDTH/2,
					HANDBOT_ARM_LENGTH_OFFSET_BETWEEN_ULNA_AND_SPOKE/2 + HANDBOT_ARM_LENGTH_OFFSET + HANDBOT_ARM_ULNA_SPOKE_CONNECTION_BOX_LENGTH/2,
					- HANDBOT_ARM_ULNA_SPOKE_CONNECTION_BOX_HEIGHT/2
				>,
				<	-HANDBOT_ARM_WIDTH_OFFSET  - HANDBOT_ARM_LENGTH + HANDBOT_ARM_ULNA_SPOKE_CONNECTION_BOX_WIDTH/2,
					HANDBOT_ARM_LENGTH_OFFSET_BETWEEN_ULNA_AND_SPOKE/2 + HANDBOT_ARM_LENGTH_OFFSET - HANDBOT_ARM_ULNA_SPOKE_CONNECTION_BOX_LENGTH/2,
					HANDBOT_ARM_ULNA_SPOKE_CONNECTION_BOX_HEIGHT/2
				>
				0.0005, 
				0)
			pigment {color White}
		}

		
	}



	object { 
		handbot_wrist
		translate<HANDBOT_ARM_WIDTH_OFFSET  + HANDBOT_ARM_LENGTH, HANDBOT_ARM_LENGTH_OFFSET_BETWEEN_ULNA_AND_SPOKE/2 + HANDBOT_ARM_LENGTH_OFFSET + HANDBOT_ARM_ULNA_SPOKE_CONNECTION_BOX_LENGTH/2,0>
	}


	// The left claw
	object {
		handbot_left_claw
		translate<-HANDBOT_ARM_WIDTH_OFFSET  - HANDBOT_ARM_LENGTH - 0.035, HANDBOT_ARM_LENGTH_OFFSET_BETWEEN_ULNA_AND_SPOKE/2 + HANDBOT_ARM_LENGTH_OFFSET + HANDBOT_ARM_ULNA_SPOKE_CONNECTION_BOX_LENGTH/2 + 0.095,0>

	}

	// The right claw
	object {
		handbot_right_claw
		translate<-HANDBOT_ARM_WIDTH_OFFSET  - HANDBOT_ARM_LENGTH + 0.035, HANDBOT_ARM_LENGTH_OFFSET_BETWEEN_ULNA_AND_SPOKE/2 + HANDBOT_ARM_LENGTH_OFFSET + HANDBOT_ARM_ULNA_SPOKE_CONNECTION_BOX_LENGTH/2 + 0.095,0>

	}

rotate <HANDBOT_ARM_ROTATION.x,HANDBOT_ARM_ROTATION.y,360 -HANDBOT_ARM_ROTATION.z>

}


////////////////////////////////////////////////////////////////////////////////////////////
//											  //
// 							HANDBOT HEAD			  //
//											  //
////////////////////////////////////////////////////////////////////////////////////////////  

#local handbot_head = union {


	// The main body of the head
	difference {

		union {

			union {
				// The head
				object{
					Round_Cylinder
					(<0,-0.102/2,0.0>,<0,0.102/2,0.0>,0.03001,0.030,1)
					pigment {color White} 
				}
				// The camera
				#local HANDBOT_HEAD_CAMERA_RADIUS = 0.0075;
				cylinder {
					<0,-0.105/2,0>
					<0,0.105/2,>
					HANDBOT_HEAD_CAMERA_RADIUS
					pigment {color Black}
				}
			}

			// The two cylinders
			// Top left
			union {
				cylinder {
					<-0.018,0.015,0>,
					<-0.018,0.015,0.038>
					0.009
					pigment {color White}
				}

				cylinder {
					<-0.018,0.015,0.038>,
					<-0.018,0.015,0.062>
					0.011
					pigment {color Black}
				}

				cylinder {
					<-0.018,0.015,0.062>,
					<-0.018,0.015,0.065>
					0.009
					pigment {color Black}
				}
			}

			// Right bottom
			union {
				cylinder {
					<0.018,0.015,0>,
					<0.018,0.015,-0.038>
					0.009
					pigment {color White}
				}

				cylinder {
					<0.018,0.015,-0.038>,
					<0.018,0.015,-0.062>
					0.011
					pigment {color Black}
				}
				cylinder {
					<0.018,0.015,-0.062>,
					<0.018,0.015,-0.065>
					0.009
					pigment {color Black}
				}
			}
		}
		union {
			// To slice the round cylinder in two
			box {
				<-1,-0.1,0>,
				<1,0.0,1>
				translate <0,0,-0.075>
			}
			// The slots for the arms
			box {
				<-1,-0.02 + 0.025,-0.006>,
				<1,0.02 + 0.025,0.006>
			}
		}
	}



	// The arms
	object { handbot_right_arm}
	object { handbot_left_arm}


}

////////////////////////////////////////////////////////////////////////////////////////////
//											  //
// 							HANDBOT COMPOSITION		  //
//											  //
////////////////////////////////////////////////////////////////////////////////////////////    


union {
	object { 
		handbot_main_body 		
		pigment{ color Wheat}
	}
	object { handbot_main_body_deco }
	object { handbot_grippable_area }
	object { handbot_leds }
	object { 
		handbot_range_and_bearing_module 
		translate <0,-HANDBOT_DOCKING_MAJOR_RADIUS/2.2,HANDBOT_MAIN_BODY_CUBIC_PART_HEIGHT-0.006>
	}
	object { handbot_launcher_module }
	object { 
		handbot_shield 
		pigment{ color Wheat}
	}
	object { 
		handbot_head 
		rotate HANDBOT_HEAD_ROTATION
		translate <0,0.054,0.08>
	}
	pigment {color Black}
	rotate HANDBOT_ROTATION
	translate HANDBOT_POSITION
}

#end
