#include "textures.inc"
#include "common.inc"
#include "textures.inc"
#include "stdinc.inc" 
#include "metals.inc"
#include "shapesq.inc" 
#include "shapes.inc"
#include "shapes_lo.inc"


#macro eyebot(
  EYEBOT_POSITION, EYEBOT_ROTATION, EYEBOT_CAMERA_ROTATION, 
  EYEBOT_PROPELLER_ROTATION, EYEBOT_DISTANCE_SCANNER_ROTATION,
  EYEBOT_LED1_COLOR,  EYEBOT_LED2_COLOR,  EYEBOT_LED3_COLOR,  EYEBOT_LED4_COLOR,
  EYEBOT_LED5_COLOR,  EYEBOT_LED6_COLOR,  EYEBOT_LED7_COLOR,  EYEBOT_LED8_COLOR,
  EYEBOT_LED9_COLOR,  EYEBOT_LED10_COLOR, EYEBOT_LED11_COLOR, EYEBOT_LED12_COLOR,
  EYEBOT_LED13_COLOR,  EYEBOT_LED14_COLOR, EYEBOT_LED15_COLOR, EYEBOT_LED16_COLOR
)







////////////////////////////////////////////////////////////////////////////////////////////
//																						//
// 							EYEBOT RAB RING											//
//																						//
////////////////////////////////////////////////////////////////////////////////////////////    




#local EYEBOT_RAB_RING_ELEVATION = 0.165;

#local eyebot_rab_ring = object {
		
#local EYEBOT_RAB_RING_THICKNESS = 0.001;
#local EYEBOT_RAB_RINGS_GAP = 0.015;
#local EYEBOT_RAB_RING_EXTERNAL_RADIUS = 0.25;
#local EYEBOT_RAB_RING_INTERNAL_RADIUS = 0.225;
#local EYEBOT_RAB_INNER_RING_EXTERNAL_RADIUS = 0.04;
#local EYEBOT_RAB_INNER_RING_INTERNAL_RADIUS = 0.015;
#local EYEBOT_RAB_RING_AXES_WIDTH = 0.01;

	#local eyebot_rab_single_ring = difference {	

	  cylinder {
	    <0, 0, 0>,
	    <0, 0, EYEBOT_RAB_RING_THICKNESS>,
	   EYEBOT_RAB_RING_EXTERNAL_RADIUS     
	  }
	  cylinder {
	    <0, 0, -2 *EYEBOT_RAB_RING_THICKNESS>,
	    <0, 0, 2 *EYEBOT_RAB_RING_THICKNESS>,
	   EYEBOT_RAB_RING_INTERNAL_RADIUS   
	  }
	}
	
	#local eyebot_rab_single_inner_ring =   difference { 
	   cylinder {
	    <0, 0, 0>,
	    <0, 0, EYEBOT_RAB_RING_THICKNESS>,
	   EYEBOT_RAB_INNER_RING_EXTERNAL_RADIUS     
	  }
	cylinder {
	    <0, 0, -2 *EYEBOT_RAB_RING_THICKNESS>,
	    <0, 0, 2 *EYEBOT_RAB_RING_THICKNESS>,
	   EYEBOT_RAB_INNER_RING_INTERNAL_RADIUS  
	  }

	}


	// The two axes that goes through the RAB ring
	#local eyebot_rab_ring_axes =  difference { 
		union { 
		  box {
		    <-EYEBOT_RAB_RING_EXTERNAL_RADIUS, -EYEBOT_RAB_RING_AXES_WIDTH/2,   0>,
		    < EYEBOT_RAB_RING_EXTERNAL_RADIUS,  EYEBOT_RAB_RING_AXES_WIDTH/2, EYEBOT_RAB_RINGS_GAP>
		  }

		  box {
		    <-EYEBOT_RAB_RING_EXTERNAL_RADIUS, -EYEBOT_RAB_RING_AXES_WIDTH/2,   0>, 
		    < EYEBOT_RAB_RING_EXTERNAL_RADIUS,  EYEBOT_RAB_RING_AXES_WIDTH/2, EYEBOT_RAB_RINGS_GAP> 
			rotate z * 90
		  }
		}
		cylinder {
		    <0, 0, -0.1>,
		    <0, 0, 0.1>,
		   EYEBOT_RAB_INNER_RING_INTERNAL_RADIUS  
		}
	}

	// Two legs on each side of the axes that goes through the RAB ring
	#local eyebot_legs_pair = union {
	  box {
	    <-EYEBOT_RAB_RING_EXTERNAL_RADIUS, -0.0005,   EYEBOT_RAB_RINGS_GAP + 2 * EYEBOT_RAB_RING_THICKNESS>,
	    <-EYEBOT_RAB_RING_EXTERNAL_RADIUS-0.009,  0.0005, -EYEBOT_RAB_RING_ELEVATION>
	    pigment {color Black}
	  }

	  box {
	    <EYEBOT_RAB_RING_EXTERNAL_RADIUS, -0.0005,   EYEBOT_RAB_RINGS_GAP + 2 * EYEBOT_RAB_RING_THICKNESS>,
	    <EYEBOT_RAB_RING_EXTERNAL_RADIUS+0.009,  0.0005, -EYEBOT_RAB_RING_ELEVATION>
	    pigment {color Black}
	  }
	}






    // LEDS 
    #local eyebot_leds = union {
      #local EYEBOT_LEDS = 16;
      #local EYEBOT_LED_ANGLE = 360 / EYEBOT_LEDS;
      #local EYEBOT_LED_PHASE = EYEBOT_LED_ANGLE / 2;
      #local EYEBOT_LED_RADIUS = 0.01 / 7.0;

      #include "robots/led.inc"   

	// The leds pointing downwards   
      #macro eyebot_led(LED_COLOR, LED_ANGLE)
        object {
          led(EYEBOT_LED_RADIUS, LED_COLOR, 1)
          translate <EYEBOT_RAB_RING_EXTERNAL_RADIUS - EYEBOT_LED_RADIUS,0,-EYEBOT_LED_RADIUS>
          rotate z * LED_ANGLE
        }
      #end

      object { eyebot_led(EYEBOT_LED1_COLOR,  360 -                   	         EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED2_COLOR,  360 -        EYEBOT_LED_ANGLE  - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED3_COLOR,  360 -   (2 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED4_COLOR,  360 -   (3 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED5_COLOR,  360 -   (4 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED6_COLOR,  360 -   (5 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED7_COLOR,  360 -   (6 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED8_COLOR,  360 -   (7 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED9_COLOR,  360 -   (8 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED10_COLOR, 360 -   (9 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED11_COLOR, 360 -   (10 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED12_COLOR, 360 -   (11 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED13_COLOR, 360 -   (12 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED14_COLOR, 360 -   (13 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED15_COLOR, 360 -   (14 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED16_COLOR, 360 -   (15 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      
      // The led that cant be controlled
        object {
          led(EYEBOT_LED_RADIUS, rgb<1,0,0>, 1)
           translate <(EYEBOT_RAB_RING_INTERNAL_RADIUS + 2 * EYEBOT_LED_RADIUS),0,-2 * EYEBOT_LED_RADIUS>
          rotate z * 135
        }
      

      // The leds pointing sidewards    
      #macro eyebot_led(LED_COLOR, LED_ANGLE)
        object {
          led(EYEBOT_LED_RADIUS, LED_COLOR, 1)
          translate <EYEBOT_RAB_RING_EXTERNAL_RADIUS + EYEBOT_LED_RADIUS/2,0, EYEBOT_RAB_RINGS_GAP + EYEBOT_LED_RADIUS / 2>
          rotate z * LED_ANGLE
        }
      #end

      object { eyebot_led(EYEBOT_LED1_COLOR,  360 -                   	         EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED2_COLOR,  360 -        EYEBOT_LED_ANGLE  - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED3_COLOR,  360 -   (2 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED4_COLOR,  360 -   (3 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED5_COLOR,  360 -   (4 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED6_COLOR,  360 -   (5 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED7_COLOR,  360 -   (6 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED8_COLOR,  360 -   (7 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED9_COLOR,  360 -   (8 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED10_COLOR, 360 -   (9 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED11_COLOR, 360 -   (10 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED12_COLOR, 360 -   (11 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED13_COLOR, 360 -   (12 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED14_COLOR, 360 -   (13 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED15_COLOR, 360 -   (14 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
      object { eyebot_led(EYEBOT_LED16_COLOR, 360 -   (15 * EYEBOT_LED_ANGLE) - EYEBOT_LED_PHASE) }
    }




	#local eyebot_rab_emitters = union {
	    	#local EYEBOT_EMITTER_GROUPS = 16;
	      	#local EYEBOT_EMITTER_GROUPS_ANGLE = 360 / EYEBOT_EMITTER_GROUPS;
	      	#local EYEBOT_EMITTER_GROUPS_PHASE = EYEBOT_EMITTER_GROUPS_ANGLE / 2;

	  
		#macro eyebot_rab_emitter_group_top(EYEBOT_EMITTER_GROUPS_ANGLE)
			object {
			Segment_of_Torus( 0.06, 0.0025, -50)
			pigment{color Black}
			translate <EYEBOT_RAB_RING_INTERNAL_RADIUS - 0.045,0, EYEBOT_RAB_RINGS_GAP/2>
			rotate <0,0,EYEBOT_EMITTER_GROUPS_ANGLE>
			//scale <0.6,0.7,1>
		
		}
		#end

		#macro eyebot_rab_emitter_group_bottom(EYEBOT_EMITTER_GROUPS_ANGLE)
			object {
			Segment_of_Torus( 0.06, 0.0025, 50)
			pigment{color Black}
			translate <EYEBOT_RAB_RING_INTERNAL_RADIUS - 0.045,0, EYEBOT_RAB_RINGS_GAP/2>
			rotate <0,0,EYEBOT_EMITTER_GROUPS_ANGLE>
			//scale <0.6,0.7,1>
		
		}
		#end

	      object { eyebot_rab_emitter_group_top(360 -                   	         EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_top(360 -        EYEBOT_EMITTER_GROUPS_ANGLE  - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_top(360 -   (2 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_top(360 -   (3 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_top(360 -   (4 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_top(360 -   (5 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_top(360 -   (6 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_top(360 -   (7 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_top(360 -   (8 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_top(360 -   (9 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_top(360 -   (10 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_top(360 -   (11 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_top(360 -   (12 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_top(360 -   (13 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_top(360 -   (14 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_top(360 -   (15 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }


	      object { eyebot_rab_emitter_group_bottom(360 -                   	         EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_bottom(360 -        EYEBOT_EMITTER_GROUPS_ANGLE  - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_bottom(360 -   (2 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_bottom(360 -   (3 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_bottom(360 -   (4 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_bottom(360 -   (5 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_bottom(360 -   (6 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_bottom(360 -   (7 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_bottom(360 -   (8 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_bottom(360 -   (9 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_bottom(360 -   (10 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_bottom(360 -   (11 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_bottom(360 -   (12 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_bottom(360 -   (13 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_bottom(360 -   (14 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }
	      object { eyebot_rab_emitter_group_bottom(360 -   (15 * EYEBOT_EMITTER_GROUPS_ANGLE) - EYEBOT_EMITTER_GROUPS_PHASE) }

	}





















	// ROTOR 
	#local eyebot_rotor = union {
		#local EYEBOT_ROTOR_BLACK_CYLINDER_HEIGHT = 0.015;
		#local EYEBOT_ROTOR_BLUE_CYLINDER_HEIGHT = 0.02;

		// Cylindric parts
		#local eyebot_rotor_cylindric_parts = union {
			cylinder {
			    <0, 0, 0>,
			    <0, 0, -EYEBOT_ROTOR_BLACK_CYLINDER_HEIGHT>,
			   0.025 
			  pigment {color Black}
			}
			cylinder {
			    <0, 0, -EYEBOT_ROTOR_BLACK_CYLINDER_HEIGHT >,
			    <0, 0, -EYEBOT_ROTOR_BLACK_CYLINDER_HEIGHT -EYEBOT_ROTOR_BLUE_CYLINDER_HEIGHT>,
			   0.018 
			   pigment {color Blue}
			}
		}
		// One pair of wings
		#local eyebot_rotor_wing_pair = object {
			#declare Stren = 1.00;
			#declare R1 = 1.00;
			blob{
			 threshold 0.65
			 // center
			 sphere{ <0,0,0>, R1, Stren scale<1,2,1> texture { T_Chrome_2A} }
			 // wings
			 #local Nr = 0; 
			 #local EndNr = 2; 
			 #while (Nr< EndNr)
			  cylinder{<0,0,0>,< 1.5,0,0>, R1, Stren
				    scale<0.95,0.3,1>
				    rotate<-30,0,0>
				    translate<1.25,0,0>
				    rotate<0,Nr * 360/EndNr,0>}
			 #local Nr = Nr + 1; 
			 #end
			 scale 0.03
			 rotate<90,0,0>
			 translate<0,0,0>
			texture { T_Chrome_2A}
		} 

		}

		// Putting all together
		object { eyebot_rotor_cylindric_parts }
		object { eyebot_rotor_wing_pair  rotate <0,0,EYEBOT_PROPELLER_ROTATION.z> translate <0, 0,-EYEBOT_ROTOR_BLACK_CYLINDER_HEIGHT - EYEBOT_ROTOR_BLUE_CYLINDER_HEIGHT - 0.03>}
		object { eyebot_rotor_wing_pair  rotate <0,0,EYEBOT_PROPELLER_ROTATION.z>  translate <0, 0,-EYEBOT_ROTOR_BLACK_CYLINDER_HEIGHT - EYEBOT_ROTOR_BLUE_CYLINDER_HEIGHT - 0.01>  rotate z * 90}
	
	}

	// CAMERA 
	#local eyebot_camera = union {

		#local EYEBOT_CAMERA_BOX_WIDTH = 0.015;
		#local EYEBOT_CAMERA_BOX_HEIGHT = 0.045;
		#local EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT = 0.022;
		#local EYEBOT_CAMERA_BOX_ON_PLATFORM_WIDTH = 0.005;
		#local EYEBOT_CAMERA_BOX_ON_PLATFORM_LENGTH = 0.021;
		#local EYEBOT_CAMERA_BOX_CONNECTING_CYLINDER_HEIGHT = 0.0025;

		// The 4 legs which supports the camera's platform
		object {
		 // Wire_Box(A, B, WireRadius, Merge)
		 Wire_Box(<-EYEBOT_CAMERA_BOX_WIDTH,-EYEBOT_CAMERA_BOX_WIDTH,0>,<EYEBOT_CAMERA_BOX_WIDTH,EYEBOT_CAMERA_BOX_WIDTH,-EYEBOT_CAMERA_BOX_HEIGHT>, 0.001, 0)
		 texture{
		   pigment{ color Black}
		   finish {  phong 1}
		 } 
		} 
		// The surface to which the camera is attached
		box {
		<-EYEBOT_CAMERA_BOX_WIDTH - 0.003,-EYEBOT_CAMERA_BOX_WIDTH - 0.003,-EYEBOT_CAMERA_BOX_HEIGHT + 0.001>,
		<EYEBOT_CAMERA_BOX_WIDTH + 0.003,EYEBOT_CAMERA_BOX_WIDTH,-EYEBOT_CAMERA_BOX_HEIGHT - 0.001>
		}
		// The part that is on top of the surface
		box {
		<-EYEBOT_CAMERA_BOX_ON_PLATFORM_LENGTH/2,-EYEBOT_CAMERA_BOX_ON_PLATFORM_WIDTH/2,-EYEBOT_CAMERA_BOX_HEIGHT - 0.001 - 0.004 + EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT>,
		<EYEBOT_CAMERA_BOX_ON_PLATFORM_LENGTH/2,EYEBOT_CAMERA_BOX_ON_PLATFORM_WIDTH/2,-EYEBOT_CAMERA_BOX_HEIGHT - 0.001 - 0.004 >
		pigment{ color Black}
		}
		// The cylindric part that connects the two bigger parts of the camera
		cylinder {
		    <EYEBOT_CAMERA_BOX_ON_PLATFORM_LENGTH/2 - EYEBOT_CAMERA_BOX_CONNECTING_CYLINDER_HEIGHT, 0, -EYEBOT_CAMERA_BOX_HEIGHT - 0.001 - 0.004  >,
		    <EYEBOT_CAMERA_BOX_ON_PLATFORM_LENGTH/2 - EYEBOT_CAMERA_BOX_CONNECTING_CYLINDER_HEIGHT, 0, -EYEBOT_CAMERA_BOX_HEIGHT - 0.001 - 0.004 - 0.007>,
		   0.0025 
		   pigment {color White}
		}
		// The part that can PAN
		union {
			// Bigger part
			box {
			<-EYEBOT_CAMERA_BOX_ON_PLATFORM_LENGTH/2,-EYEBOT_CAMERA_BOX_ON_PLATFORM_WIDTH,-EYEBOT_CAMERA_BOX_HEIGHT - 0.001 - 0.004 - 0.005>,
			<EYEBOT_CAMERA_BOX_ON_PLATFORM_LENGTH/2,EYEBOT_CAMERA_BOX_ON_PLATFORM_WIDTH, -EYEBOT_CAMERA_BOX_HEIGHT - 0.001 - 0.004 - 0.005 - EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT>
			pigment{ color Black}
			//translate < 0.01,0,0>
			}
			// The second cylindric part 
			cylinder {
			    <0, 0, -EYEBOT_CAMERA_BOX_HEIGHT  - 0.004 - EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT  >,
			    <0.004 - 0.01 + 1.1 * EYEBOT_CAMERA_BOX_ON_PLATFORM_LENGTH, 0, -EYEBOT_CAMERA_BOX_HEIGHT -  0.004 -  EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT>,
			   0.0025 
			   pigment {color White}
			}
			// The part that can TILT
			union {
				// The part that connects the laser pointer and the camera and the blue part to the bigger box
				box {
				<0.004 - 0.01 + EYEBOT_CAMERA_BOX_ON_PLATFORM_LENGTH, -EYEBOT_CAMERA_BOX_ON_PLATFORM_WIDTH,-EYEBOT_CAMERA_BOX_HEIGHT -  EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT>,
				<0.004 - 0.01 + EYEBOT_CAMERA_BOX_ON_PLATFORM_LENGTH + 0.002, EYEBOT_CAMERA_BOX_ON_PLATFORM_WIDTH,-EYEBOT_CAMERA_BOX_HEIGHT -  EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT - 0.7 * EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT >
				pigment{ color Black}
				}
				// The longest part to which the laser pointer and the camera is attached to
				box {
				<0.11/2 - 0.01,-EYEBOT_CAMERA_BOX_ON_PLATFORM_WIDTH,-EYEBOT_CAMERA_BOX_HEIGHT -  EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT - 0.7 * EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT >,
				<-0.11/2 - 0.01,EYEBOT_CAMERA_BOX_ON_PLATFORM_WIDTH,-EYEBOT_CAMERA_BOX_HEIGHT -  EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT - 0.7 * EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT - 0.001>
				pigment{ color Black}
				}
				// The laser pointer
				union {
					// the black cap
					cylinder {
					    <0.11/2 - 0.0025 - 0.01,-EYEBOT_CAMERA_BOX_ON_PLATFORM_WIDTH/2 + 0.0025,-EYEBOT_CAMERA_BOX_HEIGHT -  EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT - 0.7 * EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT>,
					    <0.11/2 - 0.0025 - 0.01,-EYEBOT_CAMERA_BOX_ON_PLATFORM_WIDTH/2 + 0.0025,-EYEBOT_CAMERA_BOX_HEIGHT -  EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT - 0.7 * EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT - 0.007>,
					   0.0025 
					   pigment {color Black}
					}
					// the golden part
					cylinder {
					    <0.11/2 - 0.0025 - 0.01,-EYEBOT_CAMERA_BOX_ON_PLATFORM_WIDTH/2 + 0.0025,-EYEBOT_CAMERA_BOX_HEIGHT -  EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT - 0.7 * EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT>,
					    <0.11/2 - 0.0025 - 0.01,-EYEBOT_CAMERA_BOX_ON_PLATFORM_WIDTH/2 + 0.0025,-EYEBOT_CAMERA_BOX_HEIGHT -  EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT - 0.7 * EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT - 0.015>,
					   0.002 
					   texture {T_Gold_1D}
					}
				}
				// The camera
				union {
					box {
					<-0.005 - 0.01,-EYEBOT_CAMERA_BOX_ON_PLATFORM_WIDTH,-EYEBOT_CAMERA_BOX_HEIGHT -  EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT - 0.7 * EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT - 0.001>,
					<0.005 - 0.01,EYEBOT_CAMERA_BOX_ON_PLATFORM_WIDTH,-EYEBOT_CAMERA_BOX_HEIGHT -  EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT - 0.7 * EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT - 0.01>
					pigment{ color Black}
					}
					cylinder {
					< - 0.01,0,-EYEBOT_CAMERA_BOX_HEIGHT -  EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT - 0.7 * EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT - 0.01>,
					< - 0.01,0,-EYEBOT_CAMERA_BOX_HEIGHT -  EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT - 0.7 * EYEBOT_CAMERA_BOX_ON_PLATFORM_HEIGHT - 0.011>,
					 0.005 
					pigment{ color Black}
					}
				}
			// The tilt feature should be somewhere here
			//rotate<30,0,0>
			//translate < 0.01,0,0>
			}
		 rotate EYEBOT_CAMERA_ROTATION
		 translate < 0.01,0,0>
		}
	}

	union {
		object { eyebot_rab_single_ring}
		object { 
			eyebot_rab_single_ring
			translate z * EYEBOT_RAB_RINGS_GAP
		}
		object { eyebot_rab_single_inner_ring}
		object { 
			eyebot_rab_single_inner_ring
			translate z * EYEBOT_RAB_RINGS_GAP
		}
		object { eyebot_rab_ring_axes}
		object { eyebot_rab_emitters}
		object { eyebot_legs_pair}
		object { eyebot_legs_pair
			rotate z* 90
		}
	    	object { eyebot_leds }
		object { eyebot_rotor  rotate <EYEBOT_PROPELLER_ROTATION.x, EYEBOT_PROPELLER_ROTATION.y, 30 +  EYEBOT_PROPELLER_ROTATION.z> translate <0, EYEBOT_RAB_RING_EXTERNAL_RADIUS - 0.12,EYEBOT_ROTOR_BLACK_CYLINDER_HEIGHT> }
		object { eyebot_rotor  rotate <EYEBOT_PROPELLER_ROTATION.x, EYEBOT_PROPELLER_ROTATION.y, 60 + EYEBOT_PROPELLER_ROTATION.z> translate <0,-EYEBOT_RAB_RING_EXTERNAL_RADIUS + 0.12,EYEBOT_ROTOR_BLACK_CYLINDER_HEIGHT> }
		object { eyebot_rotor  rotate <EYEBOT_PROPELLER_ROTATION.x, EYEBOT_PROPELLER_ROTATION.y, 120 + EYEBOT_PROPELLER_ROTATION.z> translate <-EYEBOT_RAB_RING_EXTERNAL_RADIUS + 0.12,0,EYEBOT_ROTOR_BLACK_CYLINDER_HEIGHT> }
		object { eyebot_rotor  rotate <EYEBOT_PROPELLER_ROTATION.x, EYEBOT_PROPELLER_ROTATION.y, 150 + EYEBOT_PROPELLER_ROTATION.z> translate <EYEBOT_RAB_RING_EXTERNAL_RADIUS - 0.12, 0, EYEBOT_ROTOR_BLACK_CYLINDER_HEIGHT> }
		object { eyebot_camera }


	}

}



////////////////////////////////////////////////////////////////////////////////////////////
//																						//
// 							EYEBOT MAIN BODY											//
//																						//
////////////////////////////////////////////////////////////////////////////////////////////    



#local eyebot_main_body = object {

	#local EYEBOT_MAIN_BODY_WIDTH = 0.07;
	#local EYEBOT_MAIN_BODY_HEIGHT = 0.23;

	box {
	<-EYEBOT_MAIN_BODY_WIDTH/2, -EYEBOT_MAIN_BODY_WIDTH/2,   0>, 
	< EYEBOT_MAIN_BODY_WIDTH/2, EYEBOT_MAIN_BODY_WIDTH/2, EYEBOT_MAIN_BODY_HEIGHT>
	}

}


////////////////////////////////////////////////////////////////////////////////////////////
//																						//
// 							EYEBOT DISTANCE SCANNER											//
//																						//
////////////////////////////////////////////////////////////////////////////////////////////    



#local eyebot_distance_scanner = object {

	#local EYEBOT_DISTANCE_SCANNER_BASE_CYLINDER_RADIUS = EYEBOT_MAIN_BODY_WIDTH/2;
	#local EYEBOT_DISTANCE_SCANNER_BASE_CYLINDER_HEIGHT = 0.002;
	#local EYEBOT_DISTANCE_SCANNER_MODULE_HEIGHT = 0.135;

	#local EYEBOT_DISTANCE_SCANNER_HEIGHT = 0.05;
	#local EYEBOT_DISTANCE_SCANNER_WIDTH = 0.01;
	#local EYEBOT_DISTANCE_SCANNER_LENGTH = 0.06;


	#local EYEBOT_DISTANCE_SCANNER_CONNECTION_TUBE_HEIGHT = EYEBOT_DISTANCE_SCANNER_MODULE_HEIGHT/3;

	union  {


		// The distance scanner connection tube
		cylinder {
		<0,0,EYEBOT_DISTANCE_SCANNER_MODULE_HEIGHT>,
		<0,0, EYEBOT_DISTANCE_SCANNER_MODULE_HEIGHT- EYEBOT_DISTANCE_SCANNER_CONNECTION_TUBE_HEIGHT>,
		EYEBOT_DISTANCE_SCANNER_BASE_CYLINDER_RADIUS/8
		pigment{ color Black}
		}

		// The distance scanner
		difference {
			box {
			<-EYEBOT_DISTANCE_SCANNER_WIDTH/2,-EYEBOT_DISTANCE_SCANNER_LENGTH/2, 0>, 
			<EYEBOT_DISTANCE_SCANNER_WIDTH/2,EYEBOT_DISTANCE_SCANNER_LENGTH/2, EYEBOT_DISTANCE_SCANNER_HEIGHT>
			}

			box {
			<-EYEBOT_DISTANCE_SCANNER_WIDTH,-EYEBOT_DISTANCE_SCANNER_LENGTH/2, 0.005>, 
			<EYEBOT_DISTANCE_SCANNER_WIDTH,EYEBOT_DISTANCE_SCANNER_LENGTH/2, EYEBOT_DISTANCE_SCANNER_HEIGHT- 0.005>
			rotate<0,0,90>
			}
		rotate EYEBOT_DISTANCE_SCANNER_ROTATION
		translate<0,0,EYEBOT_DISTANCE_SCANNER_MODULE_HEIGHT- EYEBOT_DISTANCE_SCANNER_CONNECTION_TUBE_HEIGHT - EYEBOT_DISTANCE_SCANNER_HEIGHT>
		}

		// Two discs covering the distance scanner
		disc{ <0,0,0>, <0,0,0.1>, EYEBOT_DISTANCE_SCANNER_MODULE_HEIGHT/2, 0.115/2
		rotate<0,90,0>
		translate<0,0,EYEBOT_DISTANCE_SCANNER_MODULE_HEIGHT/2 + EYEBOT_DISTANCE_SCANNER_BASE_CYLINDER_HEIGHT>
		scale<1,0.85,0.95>
		pigment{ color Black}
		}


		disc{ <0,0,0>, <0,0,0.1>, EYEBOT_DISTANCE_SCANNER_MODULE_HEIGHT/2, 0.115/2
		rotate<90,90,0>
		translate<0,0,EYEBOT_DISTANCE_SCANNER_MODULE_HEIGHT/2 + EYEBOT_DISTANCE_SCANNER_BASE_CYLINDER_HEIGHT>
		scale<1,0.85,1.0>
		pigment{ color Black}
		}


		// The base
		cylinder {
		<0,0,0>,
		<0,0,EYEBOT_DISTANCE_SCANNER_BASE_CYLINDER_HEIGHT>,
		EYEBOT_DISTANCE_SCANNER_BASE_CYLINDER_RADIUS
		pigment{ color Black}
		}


	}

}

////////////////////////////////////////////////////////////////////////////////////////////
//																						//
// 							EYEBOT MAGNET MODULE											//
//																						//
////////////////////////////////////////////////////////////////////////////////////////////    



#local eyebot_magnet_module = object {

		#local EYEBOT_MAGNET_HEIGHT=0.04;

		union {
			// Magnet
			cylinder {
			<0,0,0>,
			<0,0, EYEBOT_MAGNET_HEIGHT>,
			0.01
			pigment{ color Black}
			}

			object {
				Segment_of_Torus( 0.045, 0.0045, 180)
				pigment{color Black}
				translate<0,0,EYEBOT_MAGNET_HEIGHT>
			}

		}


}




////////////////////////////////////////////////////////////////////////////////////////////
//																						//
// 							EYEBOT COMPOSITION											//
//																						//
////////////////////////////////////////////////////////////////////////////////////////////    


	union {
    		object { eyebot_rab_ring 
			translate  z * EYEBOT_RAB_RING_ELEVATION 
		}

 		object { eyebot_main_body 
			translate  z *(EYEBOT_RAB_RING_ELEVATION + EYEBOT_RAB_RINGS_GAP + 2 * EYEBOT_RAB_RING_THICKNESS)
		}
 		object { eyebot_distance_scanner 
			translate  z *(EYEBOT_RAB_RING_ELEVATION + EYEBOT_RAB_RINGS_GAP + 2 * EYEBOT_RAB_RING_THICKNESS + EYEBOT_MAIN_BODY_HEIGHT)
		}
    		object { eyebot_magnet_module
			translate  z *(EYEBOT_RAB_RING_ELEVATION + EYEBOT_RAB_RINGS_GAP + 2 * EYEBOT_RAB_RING_THICKNESS + EYEBOT_MAIN_BODY_HEIGHT + EYEBOT_DISTANCE_SCANNER_MODULE_HEIGHT)
		}

	pigment {color Black}
    	rotate EYEBOT_ROTATION
    	translate EYEBOT_POSITION
  }

#end
