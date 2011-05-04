#include "textures.inc"
#include "common.inc"
#include "textures.inc"
#include "stdinc.inc" 
#include "metals.inc"
#include "glass.inc"
#include "stones2.inc"


#macro footbot(
  FOOTBOT_POSITION, FOOTBOT_ROTATION, FOOTBOT_BEACON_COLOR, FOOTBOT_BATTERY_INSERTED,
  FOOTBOT_DISTANCE_SCANNER_ROTATION, FOOTBOT_TURRET_ROTATION, FOOTBOT_GRIPPER_APPERTURE,
  FOOTBOT_LED1_COLOR,  FOOTBOT_LED2_COLOR,  FOOTBOT_LED3_COLOR,  FOOTBOT_LED4_COLOR,
  FOOTBOT_LED5_COLOR,  FOOTBOT_LED6_COLOR,  FOOTBOT_LED7_COLOR,  FOOTBOT_LED8_COLOR,
  FOOTBOT_LED9_COLOR,  FOOTBOT_LED10_COLOR, FOOTBOT_LED11_COLOR, FOOTBOT_LED12_COLOR
)
	  	
 
	  	
		  	
  // TEXTURES
  #local footbot_white_texture = pigment { color White }
  #local footbot_pneumatic_texture = pigment { color Black }
  
  
  
  
  
  
  ////////////////////////////////////////////////////////////////////////////////////////////
  //																						//
  // 							FOOTBOT BASE MODULE											//
  //																						//
  ////////////////////////////////////////////////////////////////////////////////////////////    




  // INTERNAL PLASTIC WHITE WHEEL
  #local FOOTBOT_WHEEL_INTERNAL_WIDTH = 0.025;
  #local FOOTBOT_WHEEL_INTERNAL_RADIUS = 0.02017;
  #local footbot_internal_plastic_wheel_right = union {
  	
	  	difference {
		    cylinder {
		    <0, -FOOTBOT_WHEEL_INTERNAL_WIDTH / 2, 0>,
		    <0,  FOOTBOT_WHEEL_INTERNAL_WIDTH / 2, 0>,
		    FOOTBOT_WHEEL_INTERNAL_RADIUS
		    texture { footbot_white_texture }
		 	}
		 	
		     cylinder {
		    <0, - FOOTBOT_WHEEL_INTERNAL_WIDTH / 2 + 0.0025, 0>,
		    <0,  - FOOTBOT_WHEEL_INTERNAL_WIDTH / 2 - 0.0025, 0>,
		    FOOTBOT_WHEEL_INTERNAL_RADIUS - 0.004
		 	}
		 }
	 	
		// Nut
		union {
			intersection{
			  box {<-1, 0.0,-1>,< 1,1.0,1> rotate<0, 0,0>}
			  box {<-1,-0.1,-1>,< 1,1.1,1> rotate<0,45,0>}
			  scale <0.0035,0.0015,0.0035>
			  translate <0,  - FOOTBOT_WHEEL_INTERNAL_WIDTH/2 + 0.001, 0>
			}
			
		    cylinder {
			    <0, - FOOTBOT_WHEEL_INTERNAL_WIDTH / 2 + 0.0025, 0>,
			    <0,  - FOOTBOT_WHEEL_INTERNAL_WIDTH / 2 + 0.0005, 0>,
			    0.0023
		 	}		
		 	
		 			  
		  	texture{T_Stone37}
		}
	
 	
 	} 	
 	
  #local footbot_internal_plastic_wheel_left = union {
  	
  		difference {
		    cylinder {
		    <0, -FOOTBOT_WHEEL_INTERNAL_WIDTH / 2, 0>,
		    <0,  FOOTBOT_WHEEL_INTERNAL_WIDTH / 2, 0>,
		    FOOTBOT_WHEEL_INTERNAL_RADIUS
		    texture { footbot_white_texture }
		 	}
		 	
		     cylinder {
		    <0,  FOOTBOT_WHEEL_INTERNAL_WIDTH / 2 - 0.0025, 0>,
		    <0,  FOOTBOT_WHEEL_INTERNAL_WIDTH / 2 + 0.0025, 0>,
		    FOOTBOT_WHEEL_INTERNAL_RADIUS - 0.004
		 	}
	 	}
	 	
		// Nut
		union {
			intersection{
			  box {<-1, 0.0,-1>,< 1,1.0,1> rotate<0, 0,0>}
			  box {<-1,-0.1,-1>,< 1,1.1,1> rotate<0,45,0>}
			  scale <0.0035,0.0015,0.0035>
			  translate <0,  FOOTBOT_WHEEL_INTERNAL_WIDTH/2 - 0.0025, 0>
			}
			
		    cylinder {
			    <0, FOOTBOT_WHEEL_INTERNAL_WIDTH / 2 - 0.0025, 0>,
			    <0, FOOTBOT_WHEEL_INTERNAL_WIDTH / 2 - 0.0005, 0>,
			    0.0023
		 	}		

		  	texture{T_Stone37}
						  
		}	 	
 	
 	}  	

  #local footbot_internal_plastic_wheel_track_left =    union {

	// Spokes
	object {
		#declare Stren = 1.00;
		#declare R1 = 1.00;
		blob{
			 threshold 0.65

			 #local Nr = 0; 
			 #local EndNr = 4; 
			 #while (Nr< EndNr)
			  	cylinder{<0,0,0>,< 3.5,0,0>, R1, Stren
					rotate<-30,Nr * 360/EndNr,0>
					translate<0,2.5,0>
					scale 0.0042
				}
			 #local Nr = Nr + 1; 
			 #end
		} 



	}

	// The triangular object
	object {
		prism{ 0.00, 0.60, 4
		   <-0.60, 0.00>,
		   < 0.00, 0.00>,
		   < 0.00, 3.00>,
		   <-0.60, 0.00>
		   pigment{color White}
		   rotate<0,180,90>
		   translate<0.3,1.15,3.2>
		   scale <0.012,0.012,0.012>
		   }
	}


	// Nut
	union {
		intersection{
		  box {<-1, 0.0,-1>,< 1,1.0,1> rotate<0, 0,0>}
		  box {<-1,-0.1,-1>,< 1,1.1,1> rotate<0,45,0>}
		  scale <0.0035,0.0015,0.0035>
		  translate <0,  FOOTBOT_WHEEL_INTERNAL_WIDTH/2 - 0.0025, 0>
		}
		
	    cylinder {
		    <0, FOOTBOT_WHEEL_INTERNAL_WIDTH / 2 - 0.0025, 0>,
		    <0, FOOTBOT_WHEEL_INTERNAL_WIDTH / 2 - 0.0005, 0>,
		    0.0023
	 	}		

	  	texture{T_Stone37}
		translate<0,FOOTBOT_WHEEL_INTERNAL_RADIUS - 0.014,0>		
		scale 0.8		  
	}	




	difference {
		cylinder {
		<0, FOOTBOT_WHEEL_INTERNAL_WIDTH / 2, 0>,
		<0,  -FOOTBOT_WHEEL_INTERNAL_WIDTH / 2, 0>,
		FOOTBOT_WHEEL_INTERNAL_RADIUS
		} 	

		cylinder {
		<0, FOOTBOT_WHEEL_INTERNAL_WIDTH / 2 - 0.005, 0>,
		<0, FOOTBOT_WHEEL_INTERNAL_WIDTH / 2 +  0.005, 0>,
		FOOTBOT_WHEEL_INTERNAL_RADIUS - 0.005
		} 	

		texture { footbot_white_texture }		
	}
}
  #local footbot_internal_plastic_wheel_track_right =    union {


	// Spokes
	object {
		#declare Stren = 1.00;
		#declare R1 = 1.00;
		blob{
			 threshold 0.65

			 #local Nr = 0; 
			 #local EndNr = 4; 
			 #while (Nr< EndNr)
			  	cylinder{<0,0,0>,< 3.5,0,0>, R1, Stren
					rotate<-30,Nr * 360/EndNr,0>
					translate<0,-2.5,0>
					scale 0.0042
				}
			 #local Nr = Nr + 1; 
			 #end
		} 



	}

	// The triangular object
	object {
		prism{ 0.00, 0.60, 4
		   <-0.60, 0.00>,
		   < 0.00, 0.00>,
		   < 0.00, 3.00>,
		   <-0.60, 0.00>
		   pigment{color White}
		   rotate<0,180,-90>
		   translate<-0.3,-1.15,3.2>
		   scale <0.012,0.012,0.012>
		   }
	}


	// Nut
	union {
		intersection{
		  box {<-1, 0.0,-1>,< 1,1.0,1> rotate<0, 0,0>}
		  box {<-1,-0.1,-1>,< 1,1.1,1> rotate<0,45,0>}
		  scale <0.0035,0.0015,0.0035>
		  translate <0,  FOOTBOT_WHEEL_INTERNAL_WIDTH/2 - 0.0025, 0>
		}
		
	    cylinder {
		    <0, FOOTBOT_WHEEL_INTERNAL_WIDTH / 2 - 0.0025, 0>,
		    <0, FOOTBOT_WHEEL_INTERNAL_WIDTH / 2 - 0.0005, 0>,
		    0.0023
	 	}		

	  	texture{T_Stone37}
		translate<0,-FOOTBOT_WHEEL_INTERNAL_RADIUS - 0.008,0>		
		scale 0.8		  
	}	



	// The wheel
	difference {
		cylinder {
		<0, -FOOTBOT_WHEEL_INTERNAL_WIDTH / 2, 0>,
		<0,  FOOTBOT_WHEEL_INTERNAL_WIDTH / 2, 0>,
		FOOTBOT_WHEEL_INTERNAL_RADIUS
		} 	

		cylinder {
		<0, - FOOTBOT_WHEEL_INTERNAL_WIDTH / 2 - 0.005, 0>,
		<0, - FOOTBOT_WHEEL_INTERNAL_WIDTH / 2 +  0.005, 0>,
		FOOTBOT_WHEEL_INTERNAL_RADIUS - 0.005
		} 	

		texture { footbot_white_texture }	
	}	
}

  // EXTERNAL BLACK PNEUMATIC
  #local FOOTBOT_PNEUMATIC_THICKNESS = 0.0045;
  #local FOOTBOT_WHEEL_EXTERNAL_WIDTH = 0.027;
  #local FOOTBOT_WHEEL_EXTERNAL_RADIUS = FOOTBOT_WHEEL_INTERNAL_RADIUS + FOOTBOT_PNEUMATIC_THICKNESS;
  #local FOOTBOT_WHEEL_TEETH = 24;
  #local FOOTBOT_TOOTH_WIDTH = 0.004;
  #local FOOTBOT_TOOTH_HEIGHT = 0.005;
  #local footbot_external_pneumatic_wheel = union {
    
    // HOLLOW CYLINDER
    difference {
      cylinder {
        <0, -FOOTBOT_WHEEL_EXTERNAL_WIDTH / 2, 0>,
        <0,  FOOTBOT_WHEEL_EXTERNAL_WIDTH / 2, 0>,
        FOOTBOT_WHEEL_EXTERNAL_RADIUS
      }
      cylinder {
        <0, (-FOOTBOT_WHEEL_EXTERNAL_WIDTH - SMALL_SKEW) / 2, 0>,
        <0, ( FOOTBOT_WHEEL_EXTERNAL_WIDTH + SMALL_SKEW) / 2, 0>,
        FOOTBOT_WHEEL_INTERNAL_RADIUS - SMALL_SKEW
      }      
    }
    
    // TEETH
    #local COUNT = 0;
    #while( COUNT < FOOTBOT_WHEEL_TEETH )
      box {
        <-FOOTBOT_TOOTH_WIDTH / 2, -FOOTBOT_WHEEL_EXTERNAL_WIDTH / 2, FOOTBOT_WHEEL_EXTERNAL_RADIUS>,
        < FOOTBOT_TOOTH_WIDTH / 2,  FOOTBOT_WHEEL_EXTERNAL_WIDTH / 2, FOOTBOT_WHEEL_EXTERNAL_RADIUS + FOOTBOT_TOOTH_HEIGHT>
        rotate y * COUNT * 15
      }
      #local COUNT = COUNT + 1;
    #end
    
    texture { footbot_pneumatic_texture }
  }

  // FOOTBOT WHEEL
  #local footbot_wheel_right = union {
    // INTERNAL PLASTIC WHITE WHEEL
    object { footbot_internal_plastic_wheel_right }
    // EXTERNAL BLACK PNEUMATIC
    object { footbot_external_pneumatic_wheel }
    translate z * (FOOTBOT_WHEEL_EXTERNAL_RADIUS + FOOTBOT_TOOTH_HEIGHT)
  }
  
  #local footbot_wheel_left = union {
    // INTERNAL PLASTIC WHITE WHEEL
    object { footbot_internal_plastic_wheel_left }
    // EXTERNAL BLACK PNEUMATIC
    object { footbot_external_pneumatic_wheel }
    translate z * (FOOTBOT_WHEEL_EXTERNAL_RADIUS + FOOTBOT_TOOTH_HEIGHT)
  }
  

  // TRACK STRAIGHT PNEUMATIC PART
  #local FOOTBOT_BASE_RADIUS = 0.085;
  #local FOOTBOT_STRAIGHT_PNEUMATIC_TEETH = 9;
  #local footbot_straight_pneumatic_part = union {
    box {
      <-0.05/2 - FOOTBOT_WHEEL_INTERNAL_RADIUS, -FOOTBOT_WHEEL_EXTERNAL_WIDTH / 2, -FOOTBOT_PNEUMATIC_THICKNESS / 2>,
      < 0.05/2 +  FOOTBOT_WHEEL_INTERNAL_RADIUS,  FOOTBOT_WHEEL_EXTERNAL_WIDTH / 2,  FOOTBOT_PNEUMATIC_THICKNESS / 2>
    }
    // TEETH
    #local COUNT = 0;
    #while( COUNT < FOOTBOT_STRAIGHT_PNEUMATIC_TEETH )
      box {
        <-FOOTBOT_TOOTH_WIDTH / 2, -FOOTBOT_WHEEL_EXTERNAL_WIDTH / 2, FOOTBOT_PNEUMATIC_THICKNESS / 2>,
        < FOOTBOT_TOOTH_WIDTH / 2,  FOOTBOT_WHEEL_EXTERNAL_WIDTH / 2, FOOTBOT_PNEUMATIC_THICKNESS / 2 + FOOTBOT_TOOTH_HEIGHT>
        translate <( ( 4 * FOOTBOT_WHEEL_INTERNAL_RADIUS * COUNT / FOOTBOT_STRAIGHT_PNEUMATIC_TEETH ) - 2 * FOOTBOT_WHEEL_INTERNAL_RADIUS ),0,0>
      }
      #local COUNT = COUNT + 1;
    #end
    texture { footbot_pneumatic_texture }
  }

  // FOOTBOT TRACK RIGHT
  #local footbot_track_right = union {
    // INTERNAL PLASTIC WHITE BACK WHEEL
    object {
      footbot_internal_plastic_wheel_track_right
      translate <-0.05/2 - FOOTBOT_WHEEL_INTERNAL_RADIUS, 0, 0>
    }
    // FRONT PLASTIC WHITE BACK WHEEL
    object {
      footbot_internal_plastic_wheel_track_right
      translate <0.05/2 + FOOTBOT_WHEEL_INTERNAL_RADIUS, 0, 0>
    }
    // BACK PNEUMATIC PART
    difference {
      object { footbot_external_pneumatic_wheel }
      box {
        <0, FOOTBOT_WHEEL_EXTERNAL_WIDTH / 2 - SMALL_SKEW, FOOTBOT_WHEEL_EXTERNAL_RADIUS - FOOTBOT_TOOTH_HEIGHT - SMALL_SKEW>,
        <FOOTBOT_WHEEL_EXTERNAL_RADIUS + FOOTBOT_TOOTH_HEIGHT + SMALL_SKEW,  FOOTBOT_WHEEL_EXTERNAL_WIDTH / 2 + SMALL_SKEW,  FOOTBOT_WHEEL_EXTERNAL_RADIUS + FOOTBOT_TOOTH_HEIGHT + SMALL_SKEW>
      }
      translate <-0.05/2 - FOOTBOT_WHEEL_INTERNAL_RADIUS, 0, 0>
    }
    // FRONT PNEUMATIC PART
    difference {
      object { footbot_external_pneumatic_wheel }
      box {
        <0, -FOOTBOT_WHEEL_EXTERNAL_WIDTH / 2 + SMALL_SKEW, -FOOTBOT_WHEEL_EXTERNAL_RADIUS + FOOTBOT_TOOTH_HEIGHT - SMALL_SKEW>,
        <-FOOTBOT_WHEEL_EXTERNAL_RADIUS + FOOTBOT_TOOTH_HEIGHT + SMALL_SKEW,  FOOTBOT_WHEEL_EXTERNAL_WIDTH / 2 + SMALL_SKEW,  FOOTBOT_WHEEL_EXTERNAL_RADIUS + FOOTBOT_TOOTH_HEIGHT + SMALL_SKEW>
      }
      translate <0.05/2 + FOOTBOT_WHEEL_INTERNAL_RADIUS, 0, 0>
    }
    // TOP STRAIGHT PNEUMATIC
    object {
      footbot_straight_pneumatic_part
      translate z * (FOOTBOT_WHEEL_INTERNAL_RADIUS + FOOTBOT_PNEUMATIC_THICKNESS / 2)
    }
    // BOTTOM STRAIGHT PNEUMATIC
    object {
      footbot_straight_pneumatic_part
      rotate y * 180
      translate z * (-FOOTBOT_WHEEL_INTERNAL_RADIUS - FOOTBOT_PNEUMATIC_THICKNESS / 2)
    }

    translate <0,-0.004,FOOTBOT_WHEEL_EXTERNAL_RADIUS + FOOTBOT_TOOTH_HEIGHT>
  }
  
  
  
    // FOOTBOT TRACK LEFT
  #local footbot_track_left = union {
    // INTERNAL PLASTIC WHITE BACK WHEEL
    object {
      footbot_internal_plastic_wheel_track_left
      translate <-0.05/2 - FOOTBOT_WHEEL_INTERNAL_RADIUS, 0, 0>
    }
    // FRONT PLASTIC WHITE BACK WHEEL
    object {
      footbot_internal_plastic_wheel_track_left
      translate <0.05/2 + FOOTBOT_WHEEL_INTERNAL_RADIUS, 0, 0>
    }
    // BACK PNEUMATIC PART
    difference {
      object { footbot_external_pneumatic_wheel }
      box {
        <0, FOOTBOT_WHEEL_EXTERNAL_WIDTH / 2 - SMALL_SKEW, FOOTBOT_WHEEL_EXTERNAL_RADIUS - FOOTBOT_TOOTH_HEIGHT - SMALL_SKEW>,
        <FOOTBOT_WHEEL_EXTERNAL_RADIUS + FOOTBOT_TOOTH_HEIGHT + SMALL_SKEW,  FOOTBOT_WHEEL_EXTERNAL_WIDTH / 2 + SMALL_SKEW,  FOOTBOT_WHEEL_EXTERNAL_RADIUS + FOOTBOT_TOOTH_HEIGHT + SMALL_SKEW>
      }
      translate <-0.05/2 - FOOTBOT_WHEEL_INTERNAL_RADIUS, 0, 0>
    }
    // FRONT PNEUMATIC PART
    difference {
      object { footbot_external_pneumatic_wheel }
      box {
        <0, -FOOTBOT_WHEEL_EXTERNAL_WIDTH / 2 + SMALL_SKEW, -FOOTBOT_WHEEL_EXTERNAL_RADIUS + FOOTBOT_TOOTH_HEIGHT - SMALL_SKEW>,
        <-FOOTBOT_WHEEL_EXTERNAL_RADIUS + FOOTBOT_TOOTH_HEIGHT + SMALL_SKEW,  FOOTBOT_WHEEL_EXTERNAL_WIDTH / 2 + SMALL_SKEW,  FOOTBOT_WHEEL_EXTERNAL_RADIUS + FOOTBOT_TOOTH_HEIGHT + SMALL_SKEW>
      }
      translate <0.05/2 + FOOTBOT_WHEEL_INTERNAL_RADIUS, 0, 0>
    }
    // TOP STRAIGHT PNEUMATIC
    object {
      footbot_straight_pneumatic_part
      translate z * (FOOTBOT_WHEEL_INTERNAL_RADIUS + FOOTBOT_PNEUMATIC_THICKNESS / 2)
    }
    // BOTTOM STRAIGHT PNEUMATIC
    object {
      footbot_straight_pneumatic_part
      rotate y * 180
      translate z * (-FOOTBOT_WHEEL_INTERNAL_RADIUS - FOOTBOT_PNEUMATIC_THICKNESS / 2)
    }
    translate <0,0.004,FOOTBOT_WHEEL_EXTERNAL_RADIUS + FOOTBOT_TOOTH_HEIGHT>
  }
  
  
  

  // THE FOOTBOT BASE
  #local FOOTBOT_BASE_HEIGHT = 0.005;
  #local FOOTBOT_BASE_INTERNAL_RADIUS = 0.085;
  #local FOOTBOT_TRACK_RUBBER_BAND_WIDTH = 0.004;
  
  #local footbot_base = union {
    // right wheel
    object {
      footbot_wheel_right
      translate <0, -0.105/2 - FOOTBOT_TRACK_RUBBER_BAND_WIDTH , 0>
    }

    // left wheel
    object {
      footbot_wheel_left
      translate <0, 0.105/2 + FOOTBOT_TRACK_RUBBER_BAND_WIDTH , 0>
    }

	      
#if (FOOTBOT_BATTERY_INSERTED)

    union {
      	  //  Battery holder
	      difference {
	      	union {
		      	union {
		      			// White box separating the wheels 
					      box {
					        <-0.14/2, -0.03 / 2, -0.05 / 2>,
					        < 0.14/2,  0.03 / 2,  0.05 / 2>
					      }
					      // White box connecting the wheels
					      box {
					        <-0.05/2, -0.105/2 + FOOTBOT_WHEEL_INTERNAL_WIDTH/2, -FOOTBOT_WHEEL_INTERNAL_RADIUS / 2>,
					        < 0.05/2,  0.105/2 - FOOTBOT_WHEEL_INTERNAL_WIDTH/2,  FOOTBOT_WHEEL_INTERNAL_RADIUS / 2>
					      } 			      
				      }
				  union {
				      // Metalic circles in the front
				      cylinder {
				          <0, 0, -0.01>
				          <0.14/2 + 0.0001, 0,  -0.01>
				          0.003
				          texture { T_Chrome_2A}
				          finish {reflection 0}
				       }
				
				      cylinder {
				          <0, 0, 0.0205 / 2 + 0.01/2 >
				          <0.14/2  + 0.0001, 0,  0.0205 / 2 + 0.01/2 >
				          0.003
				          texture { T_Chrome_2A}
				          finish {reflection 0}
				       } 
			      }			      
		      }
		      box {
		        <-0.15/2, -0.022 / 2, -0.048 / 2>,
		        < 0.135/2,  0.022 / 2,  0.048 / 2>
		      }	    
	      }
	      // Battery
	      union {
		      box {
		        <-0.142/2, -0.0205 / 2, -0.046 / 2>,
		        < 0.134/2,  0.0205 / 2,  0.046 / 2>
		      }	   
		       // Battery pin in the back
		       cylinder {
		          <0, 0, 0 >
		          <-0.14 / 2 - 0.008 , 0,  0 >
		          0.004
		       }    
	      }

      texture { footbot_white_texture }
      translate z * (FOOTBOT_WHEEL_EXTERNAL_RADIUS + FOOTBOT_TOOTH_HEIGHT + 0.012)
    }


#else 

  //  Battery holder
      difference {
      	union {
	      	union {
	      			// White box separating the wheels 
				      box {
				        <-0.14/2, -0.03 / 2, -0.05 / 2>,
				        < 0.14/2,  0.03 / 2,  0.05 / 2>
				      }
				      // White box connecting the wheels
				      box {
				        <-0.05/2, -0.105/2 + FOOTBOT_WHEEL_INTERNAL_WIDTH/2, -FOOTBOT_WHEEL_INTERNAL_RADIUS / 2>,
				        < 0.05/2,  0.105/2 - FOOTBOT_WHEEL_INTERNAL_WIDTH/2,  FOOTBOT_WHEEL_INTERNAL_RADIUS / 2>
				      } 			      
			      }
			  union {
			      // Metalic circles in the front
			      cylinder {
			          <0, 0, -0.01>
			          <0.14/2 + 0.0001, 0,  -0.01>
			          0.003
			          texture { T_Chrome_2A}
			          finish {reflection 0}
			       }
			
			      cylinder {
			          <0, 0, 0.0205 / 2 + 0.01/2 >
			          <0.14/2  + 0.0001, 0,  0.0205 / 2 + 0.01/2 >
			          0.003
			          texture { T_Chrome_2A}
			          finish {reflection 0}
			       } 
		      }			      
	      }
	      box {
	        <-0.15/2, -0.022 / 2, -0.048 / 2>,
	        < 0.135/2,  0.022 / 2,  0.048 / 2>
	      }	 


      texture { footbot_white_texture }
      translate z * (FOOTBOT_WHEEL_EXTERNAL_RADIUS + FOOTBOT_TOOTH_HEIGHT + 0.012)
    }
#end    	      
      


    
    // right track
    object {
      footbot_track_right
      translate <0, -FOOTBOT_WHEEL_EXTERNAL_WIDTH, 0>
    }

    // left track
    object {
      footbot_track_left
      translate <0, FOOTBOT_WHEEL_EXTERNAL_WIDTH, 0>
    }
    
    // electronic board
    union {

      cylinder {
        <0, 0, 2 * (FOOTBOT_WHEEL_EXTERNAL_RADIUS + FOOTBOT_TOOTH_HEIGHT)>,
        <0, 0, 2 * (FOOTBOT_WHEEL_EXTERNAL_RADIUS + FOOTBOT_TOOTH_HEIGHT) + FOOTBOT_BASE_HEIGHT - 0.001>,
        FOOTBOT_BASE_INTERNAL_RADIUS
        pigment { footbot_white_texture }
      }
      // proximity sensors
      #local PROXIMITY_SENSORS = 24;
      #local PROXIMITY_SENSOR_ANGLE = 360 / PROXIMITY_SENSORS;
      #local PROXIMITY_SENSOR_PHASE = PROXIMITY_SENSOR_ANGLE / 2;
      #local PROXIMITY_SENSOR_HEIGHT = 0.003;
      #local PROXIMITY_SENSOR_WIDTH = 0.005;
      #local PROXIMITY_SENSOR_DEPTH = 0.001;
      #local COUNT = 0;
      #while( COUNT < PROXIMITY_SENSORS )
        box {
          <-PROXIMITY_SENSOR_DEPTH / 2, -PROXIMITY_SENSOR_WIDTH / 2, -PROXIMITY_SENSOR_HEIGHT>
          < PROXIMITY_SENSOR_DEPTH / 2,  PROXIMITY_SENSOR_WIDTH / 2,  0>
          translate <FOOTBOT_BASE_RADIUS, 0, 2 * (FOOTBOT_WHEEL_EXTERNAL_RADIUS + FOOTBOT_TOOTH_HEIGHT)>
          rotate z * (PROXIMITY_SENSOR_PHASE + COUNT * PROXIMITY_SENSOR_ANGLE )
          texture { pigment { color Black } }
        }
        #local COUNT = COUNT + 1;
      #end
    }

  }


  ////////////////////////////////////////////////////////////////////////////////////////////
  //																						//
  // 							FOOTBOT DOCKING MODULE										//
  //																						//
  ////////////////////////////////////////////////////////////////////////////////////////////  
  #local FOOTBOT_DOCKING_MAJOR_RADIUS = FOOTBOT_BASE_RADIUS - 0.01;
  #local FOOTBOT_DOCKING_MINOR_RADIUS = 0.02;
  #local FOOTBOT_DOCKING_CROSS_WIDTH = 0.025;
  #local FOOTBOT_DOCKING_CROSS_HEIGHT = 0.001;
  #local FOOTBOT_DOCKING_HOLE_EXTERNAL_RADIUS = 0.045;
  #local FOOTBOT_DOCKING_HOLE_INTERNAL_RADIUS = 0.03;
  #local FOOTBOT_DOCKING_MODULE_HEIGHT = 0.03;
  #local FOOTBOT_DOCKING_ELEVATION =  FOOTBOT_BASE_HEIGHT - 0.001 + 2*(FOOTBOT_WHEEL_EXTERNAL_RADIUS + FOOTBOT_TOOTH_HEIGHT) + FOOTBOT_BASE_HEIGHT + FOOTBOT_DOCKING_MINOR_RADIUS - 0.01;
  #local footbot_docking = union {

	// Gripper
	#local FOOTBOT_GRIPPING_UNIT_WIDTH = 0.02;
	#local FOOTBOT_GRIPPING_UNIT_LENGTH = 0.003;
	#local FOOTBOT_GRIPPING_UNIT_CUBOID_HEIGHT = 0.012 / 2;
	#local FOOTBOT_SINGLE_GRIPPER_WIDTH = 0.004;
	#local FOOTBOT_SINGLE_GRIPPER_LENGTH = 0.008;
	#local FOOTBOT_SINGLE_GRIPPER_HEIGHT = 0.004;
	#local FOOTBOT_GAP_BETWEEN_INDIVIDUAL_GRIPPERS = 0.0005;
	#local FOOTBOT_GRIPPER_ROUNDED_BOX_RADIUS = 0.0008;
	#local FOOTBOT_GRIPPER_APPERTURE_SAFE = FOOTBOT_GRIPPER_APPERTURE;
	#local FOOTBOT_GRIPPING_UNIT_SPHERE_RADIUS = 0.017;
	


	// Grippable area
	#local footbot_grippable_area = union {
		
		 difference {
		   difference {
			   cylinder {
			    <0, 0, -0.03/2>,
			    <0, 0, 0.03/2>,
			    FOOTBOT_BASE_INTERNAL_RADIUS
			  	}
			   cylinder {
			    <0, 0, -0.015/2>,
			    <0, 0, 0.015/2>,
			    FOOTBOT_BASE_INTERNAL_RADIUS + 0.02
			  	}
		
		   }
		   
		    // The second cylidner that is carved out to get the 3D effect (hollow part inside)
	   		cylinder {
		    <0, 0, -0.03/2>,
		    <0, 0, 0.03/2>,
		    FOOTBOT_BASE_INTERNAL_RADIUS - 0.003
		  	}
		  	
		  	// Now set the transperancy			
		    pigment { White transmit 0.4}
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
		   	// Filling (behind the grippable area )
		   cylinder {
		    <0, 0, -FOOTBOT_DOCKING_MODULE_HEIGHT/2>,
		    <0, 0, FOOTBOT_DOCKING_MODULE_HEIGHT/2 + 0.005>,
		    FOOTBOT_DOCKING_MAJOR_RADIUS + 0.002
		    pigment {footbot_white_texture}
		  }

   }


	// Gripping unit
	#local footbot_gripping_unit = union {

	// Make things safe: gripper apperture can only be from the interval [90,-90]				  	        
	  #if(FOOTBOT_GRIPPER_APPERTURE > 90.0)
		#local FOOTBOT_GRIPPER_APPERTURE_SAFE =  90;
	  #end       		
		
	  #if(FOOTBOT_GRIPPER_APPERTURE < -90.0)
		#local FOOTBOT_GRIPPER_APPERTURE_SAFE =  -90;
	  #end  		
			
	
		difference{
			merge{
	
			     // the round part
				cylinder {
				<-FOOTBOT_GRIPPING_UNIT_WIDTH/2, FOOTBOT_DOCKING_MAJOR_RADIUS + 0.0008,  0>,
				<FOOTBOT_GRIPPING_UNIT_WIDTH/2, FOOTBOT_DOCKING_MAJOR_RADIUS + 0.0008,  0>,
				FOOTBOT_GRIPPING_UNIT_SPHERE_RADIUS
				pigment { footbot_white_texture}
				}
	
				// the box
				box {                 
				   	<-FOOTBOT_GRIPPING_UNIT_WIDTH/2,FOOTBOT_DOCKING_MAJOR_RADIUS,-FOOTBOT_GRIPPING_UNIT_CUBOID_HEIGHT>,
				   	<FOOTBOT_GRIPPING_UNIT_WIDTH/2, FOOTBOT_DOCKING_MAJOR_RADIUS + FOOTBOT_GRIPPING_UNIT_SPHERE_RADIUS + FOOTBOT_GRIPPING_UNIT_LENGTH,FOOTBOT_GRIPPING_UNIT_CUBOID_HEIGHT>
					pigment { footbot_white_texture}
				}
		    }
	
	
			// the box that is carved out
			box {                 
			   	<-FOOTBOT_SINGLE_GRIPPER_WIDTH * 1.5,FOOTBOT_DOCKING_MAJOR_RADIUS + 0.0127,-FOOTBOT_GRIPPING_UNIT_CUBOID_HEIGHT * 2>,
			   	<FOOTBOT_SINGLE_GRIPPER_WIDTH * 1.5, FOOTBOT_DOCKING_MAJOR_RADIUS + FOOTBOT_GRIPPING_UNIT_LENGTH + 0.21 ,FOOTBOT_GRIPPING_UNIT_CUBOID_HEIGHT * 2>
				pigment { footbot_white_texture}
			}
	    }
	
	        
	    // the queer cylinder
		cylinder {
	    <-FOOTBOT_GRIPPING_UNIT_WIDTH/2 - FOOTBOT_GAP_BETWEEN_INDIVIDUAL_GRIPPERS + FOOTBOT_SINGLE_GRIPPER_WIDTH, FOOTBOT_DOCKING_MAJOR_RADIUS + FOOTBOT_GRIPPING_UNIT_LENGTH + FOOTBOT_GRIPPING_UNIT_SPHERE_RADIUS,  0>,
	    <FOOTBOT_GRIPPING_UNIT_WIDTH/2 - FOOTBOT_SINGLE_GRIPPER_WIDTH,  FOOTBOT_DOCKING_MAJOR_RADIUS + FOOTBOT_GRIPPING_UNIT_LENGTH  + FOOTBOT_GRIPPING_UNIT_SPHERE_RADIUS,  0>,
	    0.0017
	    texture { T_Chrome_2A}	
	    }
	    
	
	    // the right most (seen as if you were a foot-bot) gripper
		object {
		Round_Box(
	        <0,0,-FOOTBOT_SINGLE_GRIPPER_HEIGHT/2>,
	        <FOOTBOT_SINGLE_GRIPPER_WIDTH,FOOTBOT_SINGLE_GRIPPER_LENGTH,FOOTBOT_SINGLE_GRIPPER_HEIGHT/2>,
			FOOTBOT_GRIPPER_ROUNDED_BOX_RADIUS, no)
			texture { T_Chrome_2A}			
			finish {reflection 0}
			rotate x * (360 - FOOTBOT_GRIPPER_APPERTURE_SAFE)
			translate <-FOOTBOT_GRIPPING_UNIT_WIDTH/2 + FOOTBOT_SINGLE_GRIPPER_WIDTH - FOOTBOT_GAP_BETWEEN_INDIVIDUAL_GRIPPERS, FOOTBOT_DOCKING_MAJOR_RADIUS + FOOTBOT_GRIPPING_UNIT_LENGTH + FOOTBOT_GRIPPING_UNIT_SPHERE_RADIUS,0>
		} 
		
	
		// the left most grippper
		object {
		Round_Box(
	        <0,0,-FOOTBOT_SINGLE_GRIPPER_HEIGHT/2>,
	        <FOOTBOT_SINGLE_GRIPPER_WIDTH,FOOTBOT_SINGLE_GRIPPER_LENGTH,FOOTBOT_SINGLE_GRIPPER_HEIGHT/2>,
			FOOTBOT_GRIPPER_ROUNDED_BOX_RADIUS, no)
			texture { T_Chrome_2A}
			finish {reflection 0}
			rotate x * (360 - FOOTBOT_GRIPPER_APPERTURE_SAFE)
			translate <-FOOTBOT_GRIPPING_UNIT_WIDTH/2 + (3 * FOOTBOT_SINGLE_GRIPPER_WIDTH) - FOOTBOT_GAP_BETWEEN_INDIVIDUAL_GRIPPERS, FOOTBOT_DOCKING_MAJOR_RADIUS + FOOTBOT_GRIPPING_UNIT_LENGTH + FOOTBOT_GRIPPING_UNIT_SPHERE_RADIUS,0>
		} 
	
		// the cental grippper
		object {
		Round_Box(
	        <0,0,-FOOTBOT_SINGLE_GRIPPER_HEIGHT/2>,
	        <FOOTBOT_SINGLE_GRIPPER_WIDTH,FOOTBOT_SINGLE_GRIPPER_LENGTH,FOOTBOT_SINGLE_GRIPPER_HEIGHT/2>,
			FOOTBOT_GRIPPER_ROUNDED_BOX_RADIUS, no)
			texture { T_Chrome_2A}
			finish {reflection 0}
			#if(FOOTBOT_GRIPPER_APPERTURE < 0)
			rotate x * (360 + FOOTBOT_GRIPPER_APPERTURE_SAFE)
		  	#end
		  	#if(FOOTBOT_GRIPPER_APPERTURE > 0)
			rotate x * FOOTBOT_GRIPPER_APPERTURE_SAFE
		  	#end		  	
			translate <-FOOTBOT_GRIPPING_UNIT_WIDTH/2 + (2 * FOOTBOT_SINGLE_GRIPPER_WIDTH) - FOOTBOT_GAP_BETWEEN_INDIVIDUAL_GRIPPERS, FOOTBOT_DOCKING_MAJOR_RADIUS + FOOTBOT_GRIPPING_UNIT_LENGTH + FOOTBOT_GRIPPING_UNIT_SPHERE_RADIUS,0>
			
		} 

	}

    // LEDS 
    #local footbot_leds = union {
      #local FOOTBOT_LEDS = 12;
      #local FOOTBOT_LED_ANGLE = 360 / FOOTBOT_LEDS;
      #local FOOTBOT_LED_PHASE = FOOTBOT_LED_ANGLE / 2;
      #local FOOTBOT_LED_RADIUS = 0.01 / 4.0;

      #include "robots/led.inc"      
      #macro footbot_led(LED_COLOR, LED_ANGLE)
        object {
          led(FOOTBOT_LED_RADIUS, LED_COLOR, 0)
          translate x * (FOOTBOT_DOCKING_MAJOR_RADIUS + FOOTBOT_LED_RADIUS)
          rotate z * LED_ANGLE
        }
      #end

      object { footbot_led(FOOTBOT_LED1_COLOR,  360 -  FOOTBOT_GRIPPING_UNIT_WIDTH/2 -                 	         FOOTBOT_LED_PHASE) }
      object { footbot_led(FOOTBOT_LED2_COLOR,  360 -  FOOTBOT_GRIPPING_UNIT_WIDTH/2 -      FOOTBOT_LED_ANGLE  - FOOTBOT_LED_PHASE) }
      object { footbot_led(FOOTBOT_LED3_COLOR,  360 -  FOOTBOT_GRIPPING_UNIT_WIDTH/2 - (2 * FOOTBOT_LED_ANGLE) - FOOTBOT_LED_PHASE) }
      object { footbot_led(FOOTBOT_LED4_COLOR,  360 -  FOOTBOT_GRIPPING_UNIT_WIDTH/2 - (3 * FOOTBOT_LED_ANGLE) - FOOTBOT_LED_PHASE) }
      object { footbot_led(FOOTBOT_LED5_COLOR,  360 -  FOOTBOT_GRIPPING_UNIT_WIDTH/2 - (4 * FOOTBOT_LED_ANGLE) - FOOTBOT_LED_PHASE) }
      object { footbot_led(FOOTBOT_LED6_COLOR,  360 -  FOOTBOT_GRIPPING_UNIT_WIDTH/2 - (5 * FOOTBOT_LED_ANGLE) - FOOTBOT_LED_PHASE) }
      object { footbot_led(FOOTBOT_LED7_COLOR,  360 -  FOOTBOT_GRIPPING_UNIT_WIDTH/2 - (6 * FOOTBOT_LED_ANGLE) - FOOTBOT_LED_PHASE) }
      object { footbot_led(FOOTBOT_LED8_COLOR,  360 -  FOOTBOT_GRIPPING_UNIT_WIDTH/2 - (7 * FOOTBOT_LED_ANGLE) - FOOTBOT_LED_PHASE) }
      object { footbot_led(FOOTBOT_LED9_COLOR,  360 -  FOOTBOT_GRIPPING_UNIT_WIDTH/2 - (8 * FOOTBOT_LED_ANGLE) - FOOTBOT_LED_PHASE) }
      object { footbot_led(FOOTBOT_LED10_COLOR, 360 -  FOOTBOT_GRIPPING_UNIT_WIDTH/2 - (9 * FOOTBOT_LED_ANGLE) - FOOTBOT_LED_PHASE) }
      object { footbot_led(FOOTBOT_LED11_COLOR, 360 -  FOOTBOT_GRIPPING_UNIT_WIDTH/2 - (10 * FOOTBOT_LED_ANGLE) - FOOTBOT_LED_PHASE) }
      object { footbot_led(FOOTBOT_LED12_COLOR, 360 -  FOOTBOT_GRIPPING_UNIT_WIDTH/2 - (11 * FOOTBOT_LED_ANGLE) - FOOTBOT_LED_PHASE) }
    }
    
    
    
	// Put all three parts together
    object { 
    	footbot_grippable_area 
    }
    // The turret
    union {
	    object { 
	    	footbot_gripping_unit 
	    	rotate<0,0,-90>
	    }
	    object { 
		    footbot_leds 
	    }
	    //rotate<0,0,-90>
	}
 
  }    
  
  
  


  
  ////////////////////////////////////////////////////////////////////////////////////////////
  //																						//
  // 							RANGE AND BEARING  MODULE									//
  //																						//
  ////////////////////////////////////////////////////////////////////////////////////////////
  
  
  #local FOOTBOT_RANGE_AND_BEARING_WHITE_PART_HEIGHT = 0.013;
  #local FOOTBOT_RANGE_AND_BEARING_BLUE_PART_HEIGHT =  0.0015;
  #local FOOTBOT_RANGE_AND_BEARING_MODULE_ELEVATION = FOOTBOT_DOCKING_ELEVATION + 0.006;
  
    #local footbot_range_and_bearing_module = union {

    // 2D Sensors and Emitters
	  difference {
	    torus {
	      FOOTBOT_DOCKING_MAJOR_RADIUS - 0.0065, FOOTBOT_DOCKING_MINOR_RADIUS - 0.0055
	      rotate x * 90
	     translate z * 0.007	
	    }
	   union {
		cylinder {
		<0, 0, -0.01>,
		<0, 0, 0.01 + FOOTBOT_RANGE_AND_BEARING_WHITE_PART_HEIGHT/3>,
		FOOTBOT_DOCKING_MAJOR_RADIUS + 0.02

		}



		#local FOOTBOT_RAB_SENSOR_CARVED_OUT_BOXES = 8;
		#local FOOTBOT_RAB_SENSOR_CARVED_OUT_BOX_ANGLE = 360 / FOOTBOT_RAB_SENSOR_CARVED_OUT_BOXES;

		#macro footbot_rab_sensor_carved_out_box(RAB_SENSOR_CARVED_OUT_BOX_ANGLE)


			#local EYEBOT_RAB_SENSOR_CARVED_OUT_BOX_LENGTH_WIDTH = 0.01;
			// the box that is carved out
			box {                 
			<-EYEBOT_RAB_SENSOR_CARVED_OUT_BOX_LENGTH_WIDTH /2,-EYEBOT_RAB_SENSOR_CARVED_OUT_BOX_LENGTH_WIDTH /2,-EYEBOT_RAB_SENSOR_CARVED_OUT_BOX_LENGTH_WIDTH /2>,
			<EYEBOT_RAB_SENSOR_CARVED_OUT_BOX_LENGTH_WIDTH /2,EYEBOT_RAB_SENSOR_CARVED_OUT_BOX_LENGTH_WIDTH /2,EYEBOT_RAB_SENSOR_CARVED_OUT_BOX_LENGTH_WIDTH /2>
			pigment { color White}
			translate <-FOOTBOT_DOCKING_MAJOR_RADIUS,0,FOOTBOT_RANGE_AND_BEARING_WHITE_PART_HEIGHT + 0.008>
			}


			rotate z * RAB_SENSOR_CARVED_OUT_BOX_ANGLE
		#end


		object { footbot_rab_sensor_carved_out_box(360) }
		object { footbot_rab_sensor_carved_out_box(360 -     FOOTBOT_RAB_SENSOR_CARVED_OUT_BOX_ANGLE  ) }
		object { footbot_rab_sensor_carved_out_box(360 -(2 * FOOTBOT_RAB_SENSOR_CARVED_OUT_BOX_ANGLE) ) }
		object { footbot_rab_sensor_carved_out_box(360 -(3 * FOOTBOT_RAB_SENSOR_CARVED_OUT_BOX_ANGLE) ) }
		object { footbot_rab_sensor_carved_out_box(360 -(4 * FOOTBOT_RAB_SENSOR_CARVED_OUT_BOX_ANGLE) ) }
		object { footbot_rab_sensor_carved_out_box(360 -(5 * FOOTBOT_RAB_SENSOR_CARVED_OUT_BOX_ANGLE) ) }
		object { footbot_rab_sensor_carved_out_box(360 -(6 * FOOTBOT_RAB_SENSOR_CARVED_OUT_BOX_ANGLE) ) }
		object { footbot_rab_sensor_carved_out_box(360 - (7 * FOOTBOT_RAB_SENSOR_CARVED_OUT_BOX_ANGLE) ) }




	}
		pigment {footbot_white_texture}
	   }      














      #local FOOTBOT_RAB_SENSORS = 8;
      #local FOOTBOT_RAB_SENSOR_ANGLE = 360 / FOOTBOT_RAB_SENSORS;
      #local FOOTBOT_RAB_SENSOR_PHASE = 0;
      #local FOOTBOT_RAB_SENSOR_RADIUS = 0.0020;


	// Sensors
      #macro footbot_rab_sensor(RAB_SENSOR_ANGLE)


	union {


		#local EYEBOT_RAB_SENSOR_BOX_LENGTH_WIDTH = 0.005;
		box {                 
		   	<-EYEBOT_RAB_SENSOR_BOX_LENGTH_WIDTH/2,-EYEBOT_RAB_SENSOR_BOX_LENGTH_WIDTH/2,-EYEBOT_RAB_SENSOR_BOX_LENGTH_WIDTH / 1.5>,
		   	<EYEBOT_RAB_SENSOR_BOX_LENGTH_WIDTH/2,EYEBOT_RAB_SENSOR_BOX_LENGTH_WIDTH/2,EYEBOT_RAB_SENSOR_BOX_LENGTH_WIDTH/ 1.5>
			pigment { color Black}
		}


		object{
		Round_Cylinder
		(<-0.01, 0, 0>, <0.004, 0, 0>, FOOTBOT_RAB_SENSOR_RADIUS + 0.000001, FOOTBOT_RAB_SENSOR_RADIUS,1)
		pigment {color Black transmit 0.4}

		  finish
		  { phong 0.9 phong_size 40  // A highlight
		    reflection 0.0  // Glass reflects a bit
		  }
		  interior
		  { ior 1.5 // Glass refraction
		  }
		} 

		translate <FOOTBOT_DOCKING_MAJOR_RADIUS - 0.003,0,FOOTBOT_RANGE_AND_BEARING_WHITE_PART_HEIGHT + 0.006>
		rotate z * RAB_SENSOR_ANGLE

	}
      #end

      object { footbot_rab_sensor(360 -                	         FOOTBOT_RAB_SENSOR_PHASE) }
      object { footbot_rab_sensor(360 -     FOOTBOT_RAB_SENSOR_ANGLE  - FOOTBOT_RAB_SENSOR_PHASE) }
      object { footbot_rab_sensor(360 -(2 * FOOTBOT_RAB_SENSOR_ANGLE) - FOOTBOT_RAB_SENSOR_PHASE) }
      object { footbot_rab_sensor(360 -(3 * FOOTBOT_RAB_SENSOR_ANGLE) - FOOTBOT_RAB_SENSOR_PHASE) }
      object { footbot_rab_sensor(360 -(4 * FOOTBOT_RAB_SENSOR_ANGLE) - FOOTBOT_RAB_SENSOR_PHASE) }
      object { footbot_rab_sensor(360 -(5 * FOOTBOT_RAB_SENSOR_ANGLE) - FOOTBOT_RAB_SENSOR_PHASE) }
      object { footbot_rab_sensor(360 -(6 * FOOTBOT_RAB_SENSOR_ANGLE) - FOOTBOT_RAB_SENSOR_PHASE) }
      object { footbot_rab_sensor(360 - (7 * FOOTBOT_RAB_SENSOR_ANGLE) - FOOTBOT_RAB_SENSOR_PHASE) }





       // Emitters 
     #local FOOTBOT_RAB_EMITTERS = 16;
     #local FOOTBOT_RAB_EMITTER_RADIUS = FOOTBOT_RAB_SENSOR_RADIUS / 1.7;
     #local FOOTBOT_RAB_EMITTER_ANGLE = 360 / FOOTBOT_RAB_EMITTERS;
     #local FOOTBOT_RAB_EMITTER_PHASE = FOOTBOT_RAB_EMITTER_ANGLE / 2;

      #macro footbot_rab_emitter(RAB_EMITTER_ANGLE)

	object{
	  Round_Cylinder
		(<-0.01, 0, 0>, <0.003, 0, 0>, FOOTBOT_RAB_EMITTER_RADIUS + 0.000001, FOOTBOT_RAB_EMITTER_RADIUS,1)
		pigment {color Black transmit 0.8}

		  finish
		  { phong 0.9 phong_size 40  // A highlight
		    reflection 0.0  // Glass reflects a bit
		  }
		  interior
		  { ior 1.5 // Glass refraction
		  }

		translate <FOOTBOT_DOCKING_MAJOR_RADIUS,0,FOOTBOT_RANGE_AND_BEARING_WHITE_PART_HEIGHT + 0.008>
		rotate z * RAB_EMITTER_ANGLE
	} 
      #end

      object { footbot_rab_emitter(360 -                	         FOOTBOT_RAB_EMITTER_PHASE) }
      object { footbot_rab_emitter(360 -     FOOTBOT_RAB_EMITTER_ANGLE  - FOOTBOT_RAB_EMITTER_PHASE) }
      object { footbot_rab_emitter(360 -(2 * FOOTBOT_RAB_EMITTER_ANGLE) - FOOTBOT_RAB_EMITTER_PHASE) }
      object { footbot_rab_emitter(360 -(3 * FOOTBOT_RAB_EMITTER_ANGLE) - FOOTBOT_RAB_EMITTER_PHASE) }
      object { footbot_rab_emitter(360 -(4 * FOOTBOT_RAB_EMITTER_ANGLE) - FOOTBOT_RAB_EMITTER_PHASE) }
      object { footbot_rab_emitter(360 -(5 * FOOTBOT_RAB_EMITTER_ANGLE) - FOOTBOT_RAB_EMITTER_PHASE) }
      object { footbot_rab_emitter(360 -(6 * FOOTBOT_RAB_EMITTER_ANGLE) - FOOTBOT_RAB_EMITTER_PHASE) }
      object { footbot_rab_emitter(360 - (7 * FOOTBOT_RAB_EMITTER_ANGLE) - FOOTBOT_RAB_EMITTER_PHASE) }
      object { footbot_rab_emitter(360 -(8 * FOOTBOT_RAB_EMITTER_ANGLE) - FOOTBOT_RAB_EMITTER_PHASE) }
      object { footbot_rab_emitter(360 -(9 * FOOTBOT_RAB_EMITTER_ANGLE) - FOOTBOT_RAB_EMITTER_PHASE) }
      object { footbot_rab_emitter(360 -(10 * FOOTBOT_RAB_EMITTER_ANGLE) - FOOTBOT_RAB_EMITTER_PHASE) }
      object { footbot_rab_emitter(360 -(11 * FOOTBOT_RAB_EMITTER_ANGLE) - FOOTBOT_RAB_EMITTER_PHASE) }
      object { footbot_rab_emitter(360 -(12 * FOOTBOT_RAB_EMITTER_ANGLE) - FOOTBOT_RAB_EMITTER_PHASE) }
      object { footbot_rab_emitter(360 - (13 * FOOTBOT_RAB_EMITTER_ANGLE) - FOOTBOT_RAB_EMITTER_PHASE) }
      object { footbot_rab_emitter(360 -(14 * FOOTBOT_RAB_EMITTER_ANGLE) - FOOTBOT_RAB_EMITTER_PHASE) }
      object { footbot_rab_emitter(360 - (15 * FOOTBOT_RAB_EMITTER_ANGLE) - FOOTBOT_RAB_EMITTER_PHASE) }






 	// 3D Sensors and Emitters
      cylinder {
        <0, 0, 0.022>,
        <0, 0, 0.022 + FOOTBOT_RANGE_AND_BEARING_BLUE_PART_HEIGHT>,
        FOOTBOT_DOCKING_MAJOR_RADIUS
        pigment {
          image_map {
            png "textures/robots/swarmanoid/footbot/rab_circuit.png"
            once
            interpolate 2
            
          }
          scale <.15, .15, .15>
          translate <-0.075,-0.075,0>
         }
      }
    
   }

  ////////////////////////////////////////////////////////////////////////////////////////////
  //																						//
  // 							DISTANCE SCANNER MODULE										//
  //																						//
  ////////////////////////////////////////////////////////////////////////////////////////////
  #local FOOTBOT_DISTANCE_SCANNER_PLASTIC_PIECE_BASE_HEIGHT = 0.001;
  #local FOOTBOT_DISTANCE_SCANNER_ELEVATION = FOOTBOT_RANGE_AND_BEARING_MODULE_ELEVATION + FOOTBOT_DOCKING_MINOR_RADIUS + FOOTBOT_RANGE_AND_BEARING_WHITE_PART_HEIGHT/4;
  #local footbot_distance_scanner_module = union {

      #local FOOTBOT_DISTANCE_SCANNER_LONGRANGE_WIDTH = 0.039;
      #local FOOTBOT_DISTANCE_SCANNER_HEIGHT = 0.02;
      #local FOOTBOT_DISTANCE_SCANNER_LENGTH = 0.1;
      #local FOOTBOT_DISTANCE_SCANNER_MARGIN = 0.03;

      // Gap
	  cylinder {
	    <0, 0, 0>,     					
	    <0, 0, FOOTBOT_DISTANCE_SCANNER_PLASTIC_PIECE_BASE_HEIGHT>, 
	    0.03            					
	    pigment { color Black}
	  }

      // yellow plastic piece base 1
	  cylinder {
	    <0, 0, FOOTBOT_DISTANCE_SCANNER_PLASTIC_PIECE_BASE_HEIGHT>,     					
	    <0, 0, 2 * FOOTBOT_DISTANCE_SCANNER_PLASTIC_PIECE_BASE_HEIGHT>, 
	    0.045            					
	    pigment { color Goldenrod}
	  }

      // yellow plastic piece 2
	  cylinder {
	    <0, 0, FOOTBOT_DISTANCE_SCANNER_PLASTIC_PIECE_BASE_HEIGHT>,     					
	    <0, 0, FOOTBOT_DISTANCE_SCANNER_PLASTIC_PIECE_BASE_HEIGHT + FOOTBOT_DISTANCE_SCANNER_HEIGHT >, 
	    0.04            					
	    pigment { color Goldenrod}
	  }
	  
	  // box 1 (smaller)
	  box {
	    <-FOOTBOT_DISTANCE_SCANNER_LONGRANGE_WIDTH/2, -FOOTBOT_DISTANCE_SCANNER_LENGTH/2 + 0.005, 2 * FOOTBOT_DISTANCE_SCANNER_PLASTIC_PIECE_BASE_HEIGHT>,     // Near lower left corner
	    <FOOTBOT_DISTANCE_SCANNER_LONGRANGE_WIDTH/2, FOOTBOT_DISTANCE_SCANNER_LENGTH/2 - 0.005,  FOOTBOT_DISTANCE_SCANNER_HEIGHT + 2 * FOOTBOT_DISTANCE_SCANNER_PLASTIC_PIECE_BASE_HEIGHT>   // Far upper right corner
	    pigment { color Black}

	  }

  	  // box 2
	  box {
	    <-FOOTBOT_DISTANCE_SCANNER_LONGRANGE_WIDTH/2, -FOOTBOT_DISTANCE_SCANNER_LENGTH/2, 2 * FOOTBOT_DISTANCE_SCANNER_PLASTIC_PIECE_BASE_HEIGHT>,     // Near lower left corner
	    <FOOTBOT_DISTANCE_SCANNER_LONGRANGE_WIDTH/2, FOOTBOT_DISTANCE_SCANNER_LENGTH/2,  FOOTBOT_DISTANCE_SCANNER_HEIGHT + 2 * FOOTBOT_DISTANCE_SCANNER_PLASTIC_PIECE_BASE_HEIGHT>   // Far upper right corner
	    pigment { color Black}

	    rotate <0,0,90>
	  }


  }
    

  ////////////////////////////////////////////////////////////////////////////////////////////
  //																						//
  // 									TOP MODULE											//
  //																						//
  ////////////////////////////////////////////////////////////////////////////////////////////
  #local FOOTBOT_TOP_MODULE_ELEVATION = FOOTBOT_DISTANCE_SCANNER_ELEVATION + FOOTBOT_DISTANCE_SCANNER_PLASTIC_PIECE_BASE_HEIGHT + FOOTBOT_DISTANCE_SCANNER_HEIGHT + 2 * FOOTBOT_DISTANCE_SCANNER_PLASTIC_PIECE_BASE_HEIGHT;
  #local FOOTBOT_TOP_MODULE_RADIUS = 0.065;
  #local FOOTBOT_TOP_MODULE_WHITE_PLASTIC_PIECE_HEIGHT = 0.012;
  #local footbot_top_module = union {
 

    union {
		// the white plastic piece on top of the distance scanner 1 
		cylinder {
		  <0, 0, -FOOTBOT_TOP_MODULE_WHITE_PLASTIC_PIECE_HEIGHT/2 *  0.33>,
		  <0, 0, FOOTBOT_TOP_MODULE_WHITE_PLASTIC_PIECE_HEIGHT/2 *  0.33 - FOOTBOT_DISTANCE_SCANNER_PLASTIC_PIECE_BASE_HEIGHT>,
		  FOOTBOT_TOP_MODULE_RADIUS * 1.015
		  pigment { footbot_white_texture }
		}	
		
		
		// the white plastic piece on top of the distance scanner 2 
		cylinder {
		  <0, 0, -FOOTBOT_TOP_MODULE_WHITE_PLASTIC_PIECE_HEIGHT/2 *  0.66 + FOOTBOT_TOP_MODULE_WHITE_PLASTIC_PIECE_HEIGHT/2 *  0.33>,
		  <0, 0, FOOTBOT_TOP_MODULE_WHITE_PLASTIC_PIECE_HEIGHT/2  *  0.66 + FOOTBOT_TOP_MODULE_WHITE_PLASTIC_PIECE_HEIGHT/2 *  0.33 -FOOTBOT_DISTANCE_SCANNER_PLASTIC_PIECE_BASE_HEIGHT>,
		  FOOTBOT_TOP_MODULE_RADIUS
		  pigment { footbot_white_texture }
		}	
    
      // CIRCUIT BOARD
      cylinder {
        <0, 0, 0.005>,
        <0, 0, 0.006>,
        FOOTBOT_TOP_MODULE_RADIUS
        pigment {
          image_map {
            png "textures/robots/swarmanoid/footbot/top_circuit.png"
            interpolate 2
          }
          scale <.13, .13, .13>
          translate <-0.065,0.065,0>
        }

      }
    }
    

      
    // Elevations on the top (right hand side)
    union {
    
    	 // The Wifi card
	     box {
		    <0.023,-0.035, 0.008>, 
		    <0.043,0.022 , 0.009> 
		pigment {color DarkGreen}
	  	} 
	  	
	  	// The Wifi USB plug
	     box {
			<0.028,0.022, 0.001>,
			<0.037,0.033 , 0.009> 
		texture {T_Chrome_2A}
		finish {reflection 0} 
	  	} 

	// The Wifi USB socket
	     box {
		    <0.027,0.033, 0.0>, 
		    <0.038,0.045 , 0.01> 
		texture {T_Chrome_2A}
		finish {reflection 0} 

	  	} 
	  	
    	 // The USB plug
	     box {
		    <0.047,0.0072, 0.0>, 
		    <0.06,-0.0046 , 0.01> 
		texture {T_Chrome_2A}
		finish {reflection 0} 
	  	} 	  	
    
	    //base 1
	     box {
		    <-0.02125,-0.02127/2, 0.0>,
		    <-0.0285,0.02127/2, 0.009>
		    pigment { color Black}
		    finish { specular 0.7 roughness 0.03 } // For reflection of the beacon led
		  }
		        
	    //base 2
	     box {
		    <-0.05625,-0.015/2 + 0.01, 0.0>,
		    <-0.058,0.015/2 + 0.01, 0.009>
		    pigment { color Black}
		    finish { specular 0.7 roughness 0.03 } // For reflection of the beacon led
		  }
		          
	      //base 3
	     box {
		    <-0.05625,-0.015/2 - 0.01, 0.0>,
		    <-0.058,0.015/2 - 0.01, 0.009> 
		    pigment { color Black}
		    finish { specular 0.7 roughness 0.03 } // For reflection of the beacon led
		  }	          
	      
	      //top cover
	     box {
		    <-0.02,-0.05/2, 0.009>, 
		    <-0.06,0.05/2 , 0.01> 
	        pigment {
	          image_map {
	            png "textures/robots/swarmanoid/footbot/top_circuit_dark.png"
	            interpolate 2
	          }
	          scale <.13, .13, .13>
	          translate <-0.065,0.065,0>
	        }

		  }
	  }       
      
 
	//CEILING CAMERA
    union {
      #local FOOTBOT_CEILING_CAMERA_HEIGHT = 0.01;
      #local FOOTBOT_CEILING_CAMERA_RADIUS = 0.0055;
      
      #local FOOTBOT_CEILING_CAMERA_BASE_WIDTH_LENGTH = 0.02;
      #local FOOTBOT_CEILING_CAMERA_BASE_HEIGHT = 0.005;

    //base
     box {
	    <-0.028/2,0.04, 0.0>, 
	    <0.028/2,0.045, 0.009> 
	    pigment { footbot_white_texture}
	    finish { specular 0.7 roughness 0.03 } // For reflection of the beacon led
	  }

      	//top cover
	     box {
		    <-0.028/2,0.03, 0.009>, 
		    <0.028/2,0.06 , 0.01> 
	        pigment {
	          image_map {
	            png "textures/robots/swarmanoid/footbot/top_circuit_dark.png"
	            interpolate 2
	            
	          }
	          scale <.13, .13, .13>
	          translate <-0.065,0.065,0>
	        }
		  }
		  
	  // camera base 
	  box {
	    <-FOOTBOT_CEILING_CAMERA_BASE_WIDTH_LENGTH/2, 0.035, FOOTBOT_CEILING_CAMERA_BASE_HEIGHT + 0.009>,     // Near lower left corner
	    <FOOTBOT_CEILING_CAMERA_BASE_WIDTH_LENGTH/2, 0.055,  FOOTBOT_CEILING_CAMERA_BASE_HEIGHT + FOOTBOT_CEILING_CAMERA_BASE_HEIGHT>   // Far upper right corner
	    pigment { color Black}
	    finish { specular 0.7 roughness 0.03 } // For reflection of the beacon led
	  }
	  
	  // camera
      cylinder {
        <0.0,0.0,2 * FOOTBOT_CEILING_CAMERA_BASE_HEIGHT>,
        <0.0,0.0,2 * FOOTBOT_CEILING_CAMERA_BASE_HEIGHT + FOOTBOT_CEILING_CAMERA_BASE_HEIGHT + FOOTBOT_CEILING_CAMERA_HEIGHT>,
        FOOTBOT_CEILING_CAMERA_RADIUS
        pigment { color Black}
        finish { specular 0.7 roughness 0.03 } // For reflection of the beacon led
        translate y * 0.045
      }
	  

    }   
    
    //PILLARS FOR THE BEACON AND THE TUBE
    union {
      #local FOOTBOT_TUBE_PILLAR_HEIGHT = 0.0177;
      #local FOOTBOT_TUBE_PILLAR_RADIUS = 0.0022;
      #local FOOTBOT_TUBE_PILLAR_MARGIN = 0.011;
      #local FOOTBOT_TUBE_RADIUS = 0.025;
      

      
      // bottom left
      cylinder {
        <-FOOTBOT_TUBE_RADIUS+FOOTBOT_TUBE_PILLAR_MARGIN,-FOOTBOT_TUBE_RADIUS/2, FOOTBOT_TOP_MODULE_WHITE_PLASTIC_PIECE_HEIGHT/2>,
        <-FOOTBOT_TUBE_RADIUS+FOOTBOT_TUBE_PILLAR_MARGIN,-FOOTBOT_TUBE_RADIUS/2,FOOTBOT_TOP_MODULE_WHITE_PLASTIC_PIECE_HEIGHT/2 + FOOTBOT_TUBE_PILLAR_HEIGHT>,
        FOOTBOT_TUBE_PILLAR_RADIUS
        pigment { color Grey }
        finish { specular 0.7 roughness 0.03 }
      }
      
      // bottom right
      cylinder {
        <FOOTBOT_TUBE_RADIUS-FOOTBOT_TUBE_PILLAR_MARGIN,-FOOTBOT_TUBE_RADIUS/2,FOOTBOT_TOP_MODULE_WHITE_PLASTIC_PIECE_HEIGHT/2>,
        <FOOTBOT_TUBE_RADIUS-FOOTBOT_TUBE_PILLAR_MARGIN,-FOOTBOT_TUBE_RADIUS/2,FOOTBOT_TOP_MODULE_WHITE_PLASTIC_PIECE_HEIGHT/2 + FOOTBOT_TUBE_PILLAR_HEIGHT>,
        FOOTBOT_TUBE_PILLAR_RADIUS
        pigment { color Grey }
        finish { specular 0.7 roughness 0.03 }
      } 
      
       // top left
      cylinder {
        <-FOOTBOT_TUBE_RADIUS+FOOTBOT_TUBE_PILLAR_MARGIN,+FOOTBOT_TUBE_RADIUS/2,FOOTBOT_TOP_MODULE_WHITE_PLASTIC_PIECE_HEIGHT/2>,
        <-FOOTBOT_TUBE_RADIUS+FOOTBOT_TUBE_PILLAR_MARGIN,+FOOTBOT_TUBE_RADIUS/2,FOOTBOT_TOP_MODULE_WHITE_PLASTIC_PIECE_HEIGHT/2 + FOOTBOT_TUBE_PILLAR_HEIGHT>,
        FOOTBOT_TUBE_PILLAR_RADIUS
        pigment { color Grey }
        finish { specular 0.7 roughness 0.03 }
      } 
      
      // top right
      cylinder {
        <FOOTBOT_TUBE_RADIUS-FOOTBOT_TUBE_PILLAR_MARGIN,+FOOTBOT_TUBE_RADIUS/2,FOOTBOT_TOP_MODULE_WHITE_PLASTIC_PIECE_HEIGHT/2>,
        <FOOTBOT_TUBE_RADIUS-FOOTBOT_TUBE_PILLAR_MARGIN,+FOOTBOT_TUBE_RADIUS/2,FOOTBOT_TOP_MODULE_WHITE_PLASTIC_PIECE_HEIGHT/2 + FOOTBOT_TUBE_PILLAR_HEIGHT>,
        FOOTBOT_TUBE_PILLAR_RADIUS
        pigment { color Grey }
        finish { specular 0.7 roughness 0.03 }
      } 
    }
    


	//BEACON
    union {
      #local FOOTBOT_BEACON_HEIGHT = 0.017;
      #local FOOTBOT_BEACON_RADIUS = 0.021;
      #local FOOTBOT_BEACON_COVER_HEIGHT = 0.0016;
      #local FOOTBOT_BEACON_COVER_TOP_RADIUS = 0.0215;
      #local FOOTBOT_BEACON_COVER_BOTTOM_RADIUS = 0.025;

     // cover bottom
      cylinder {
        <0,0,0>,
        <0,0,FOOTBOT_BEACON_COVER_HEIGHT>,
        FOOTBOT_BEACON_COVER_BOTTOM_RADIUS
        pigment {
          image_map {
            png "textures/robots/swarmanoid/footbot/top_circuit.png"
            interpolate 2
            
          }
	      scale <.124, .124, .124>
	      translate <-0.0625,0.064,0>
        }
      }       
      
     // beacon
     #declare beacon = cylinder {
        <0,0,0>,
        <0,0,FOOTBOT_BEACON_HEIGHT>,
        FOOTBOT_BEACON_RADIUS
        pigment{ color FOOTBOT_BEACON_COLOR}
        //translate <0,0,FOOTBOT_BEACON_COVER_HEIGHT>
        finish {ambient 1 diffuse .6}
      }   


	// The beacon is actually off, draw a transparent glas
	 #if ((FOOTBOT_BEACON_COLOR.x = 0) & (FOOTBOT_BEACON_COLOR.y = 0) & (FOOTBOT_BEACON_COLOR.z = 0))
	
		cylinder {
	        <0,0,0>,
	        <0,0,FOOTBOT_BEACON_HEIGHT>,
	        FOOTBOT_BEACON_RADIUS
		pigment {color White transmit 0.1}

		  finish
		  { phong 0.9 phong_size 40 
		    reflection 0
		  }
		  interior
		  { ior 1.5 // Glass refraction
		  }
	        translate z * FOOTBOT_BEACON_COVER_HEIGHT
	      }  	

	
	  // if switched on
	  #else
	  
		// combine light source with a regular object so that the beacon casts a shadow
		difference {
		   object { 	  
			  light_source {
				  	<0,0,FOOTBOT_BEACON_COVER_HEIGHT>
				  	color FOOTBOT_BEACON_COLOR
				  	fade_distance 0.02
		    	  		fade_power 2
					shadowless
				  	looks_like { beacon }
			  }
			}
		   object { 
				cylinder {
				        <0,0,FOOTBOT_BEACON_COVER_HEIGHT>,
				        <0,0,FOOTBOT_BEACON_HEIGHT>,
				        FOOTBOT_BEACON_RADIUS - 0.00001
				        pigment{ footbot_white_texture transmit 0.2}
				        translate z * FOOTBOT_BEACON_COVER_HEIGHT
				 }   
			}
		}	  

	#end


	  // cover top
	  cylinder {
	    <0,0,0>,
	    <0,0,FOOTBOT_BEACON_COVER_HEIGHT>,
	    FOOTBOT_BEACON_COVER_TOP_RADIUS
	    pigment {
	      image_map {
	        png "textures/robots/swarmanoid/footbot/top_circuit.png"
	        interpolate 2
	        
	      }
	      scale <.124, .124, .124>
	      translate <-0.0625,0.064,0>
	    }
	    translate z * (FOOTBOT_BEACON_COVER_HEIGHT + FOOTBOT_BEACON_HEIGHT)
  }
  
  translate z * (FOOTBOT_TUBE_PILLAR_HEIGHT + FOOTBOT_TOP_MODULE_WHITE_PLASTIC_PIECE_HEIGHT/2)
}
    
    


    
    // OMNIDIRECTIONAL CAMERA
    
  #local FOOTBOT_CAMERA_HEIGHT = 0.012;
  #local FOOTBOT_CAMERA_RADIUS = 0.007;
  #local FOOTBOT_GLASS_TUBE_HEIGHT = 0.103;
  #local FOOTBOT_GLASS_TUBE_RADIUS = 0.0202;
  #local FOOTBOT_MIRROR_RADIUS = FOOTBOT_GLASS_TUBE_RADIUS;
  #local FOOTBOT_MIRROR_HEIGHT = 0.012;
  #local FOOTBOT_MIRROR_STICK_HEIGHT = 0.053;
  #local FOOTBOT_GLASS_TUBE_PILLAR_HEIGHT = 0.02;
  
  #local FOOTBOT_CAMERA_BASE_HEIGHT = 0.005;
  
  difference {

	union {
      // pillar behind the camera
      cylinder {
        <0,-0.018,2 * FOOTBOT_BEACON_COVER_HEIGHT>,
        <0,-0.018,2 * FOOTBOT_BEACON_COVER_HEIGHT + FOOTBOT_GLASS_TUBE_PILLAR_HEIGHT>,
        FOOTBOT_CAMERA_RADIUS/4.5
        pigment { color Grey }
        finish { specular 0.7 roughness 0.03 }
      }
      
      // pillar on the right of the camera
      cylinder {
        <-0.015, 0.01,2 * FOOTBOT_BEACON_COVER_HEIGHT>,
        <-0.015, 0.01,2 * FOOTBOT_BEACON_COVER_HEIGHT + FOOTBOT_GLASS_TUBE_PILLAR_HEIGHT>,
        FOOTBOT_CAMERA_RADIUS/4.5
        pigment { color Grey }
        finish { specular 0.7 roughness 0.03 }
      }
      
       // pillar on the left of the camera
      cylinder {
        <0.015, 0.01,2 * FOOTBOT_BEACON_COVER_HEIGHT>,
        <0.015, 0.01,2 * FOOTBOT_BEACON_COVER_HEIGHT + FOOTBOT_GLASS_TUBE_PILLAR_HEIGHT>,
        FOOTBOT_CAMERA_RADIUS/4.5
        pigment { color Grey }
        finish { specular 0.7 roughness 0.03 }
      }
      
      // camera base 
	  box {
	    <0.01, -0.01, 2 * FOOTBOT_BEACON_COVER_HEIGHT>, 
	    <-0.01,0.01,  2 * FOOTBOT_BEACON_COVER_HEIGHT + FOOTBOT_CAMERA_BASE_HEIGHT> 
	    pigment { color Black}
	    finish { specular 0.7 roughness 0.03 } // For reflection of the beacon led
	  }
          
      // camera
      cylinder {
        <0,0,2 * FOOTBOT_BEACON_COVER_HEIGHT +  FOOTBOT_CAMERA_BASE_HEIGHT>,
        <0,0,2 * FOOTBOT_BEACON_COVER_HEIGHT +  FOOTBOT_CAMERA_BASE_HEIGHT + FOOTBOT_CAMERA_HEIGHT>,
        FOOTBOT_CAMERA_RADIUS
        pigment { color Black }
        finish { specular 0.7 roughness 0.03 }
      }
      // external glass tube
      cylinder {
        <0,0,0.0>,
        <0,0,FOOTBOT_GLASS_TUBE_HEIGHT>,
        FOOTBOT_GLASS_TUBE_RADIUS
        texture { pigment { footbot_white_texture transmit 0.8 } }
      }
      // mirror
      cone {
        <0,0,FOOTBOT_GLASS_TUBE_HEIGHT>, FOOTBOT_MIRROR_RADIUS
        <0,0,FOOTBOT_GLASS_TUBE_HEIGHT-FOOTBOT_MIRROR_HEIGHT>, 0.0
        pigment { footbot_white_texture }
        finish { reflection 0.9 }
      }
     
      
      // black stick inside the tube
      cylinder {
        <0,0,FOOTBOT_GLASS_TUBE_HEIGHT - FOOTBOT_MIRROR_HEIGHT>,
        <0,0,FOOTBOT_GLASS_TUBE_HEIGHT - FOOTBOT_MIRROR_HEIGHT - FOOTBOT_MIRROR_STICK_HEIGHT>,
        0.0005
        texture { pigment { color Black} }
      } 
      
     }
     
     
     // carve this part out on the top
      cone {
        <0,0,FOOTBOT_GLASS_TUBE_HEIGHT + 0.0001 >, FOOTBOT_MIRROR_RADIUS - 0.003
        <0,0,FOOTBOT_GLASS_TUBE_HEIGHT -FOOTBOT_MIRROR_HEIGHT>, 0.0
        pigment { footbot_white_texture}
      }
    
      translate z * (FOOTBOT_TUBE_PILLAR_HEIGHT + FOOTBOT_BEACON_HEIGHT + FOOTBOT_TOP_MODULE_WHITE_PLASTIC_PIECE_HEIGHT/2)

     }
     rotate <0,0,-90>
  }
  
  union {
    object { footbot_base }
    object {
      footbot_docking
      translate z * FOOTBOT_DOCKING_ELEVATION    
      rotate < FOOTBOT_TURRET_ROTATION.x, FOOTBOT_TURRET_ROTATION.y, 360 - FOOTBOT_TURRET_ROTATION.z >
    }
    object {
      footbot_range_and_bearing_module
      translate z * FOOTBOT_RANGE_AND_BEARING_MODULE_ELEVATION
    }
    object {
      footbot_distance_scanner_module
      translate z * FOOTBOT_DISTANCE_SCANNER_ELEVATION
      rotate FOOTBOT_DISTANCE_SCANNER_ROTATION
    }
    object {
      footbot_top_module
      translate z * FOOTBOT_TOP_MODULE_ELEVATION
    }
    rotate FOOTBOT_ROTATION
    translate FOOTBOT_POSITION
    
    pigment { footbot_white_texture }
    
  }

#end
