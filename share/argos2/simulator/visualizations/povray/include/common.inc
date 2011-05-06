#include "rad_def.inc"
#include "colors.inc"
#include "math.inc"

//////////////////
// GLOBAL SETTINGS
//////////////////

#if ( RADIOSITY )
  global_settings {
    noise_generator 1
    radiosity {
      pretrace_start 64/image_width
      pretrace_end   8/image_width // 8/image_width
      count 35 // 50 higher value -> more quality but slower
      nearest_count 5 // 10 
      error_bound 0.25 // 0.25 // the lower, the higher 'count' must be
      recursion_limit 3 // higher values are not necessarily better
      gray_threshold 1.0 // indirect light has no color
      brightness 2.0 //2.5
      //minimum_reuse 0.005
    }
  }
  #default {finish{ambient 0}}
#else
  global_settings {
    ambient_light 1
  }
#end

///////////////////
// GLOBAL VARIABLES
///////////////////

#declare SMALL_SKEW = 1e-4;
#declare DRAW_REFERENCE= 0;

/////////
// CAMERA
/////////

#declare default_camera = camera {
  up z
  right -4/3 * x
  sky z
  direction y
  location 0.5
  look_at 0
}

////////////
// REFERENCE
////////////

#if ( DRAW_REFERENCE )

#local REFERENCE_RADIUS = 0.01;
  sphere {
  <0,0,0>, REFERENCE_RADIUS
    pigment {
      color Red
    }
  }
  sphere {
    <1,0,0>, REFERENCE_RADIUS
    pigment {
      color Green
    }
  }
  sphere {
    <0,1,0>, REFERENCE_RADIUS
    pigment {
      color Blue
    }
  }
  sphere {
    <0,0,1>, REFERENCE_RADIUS
    pigment {
      color Yellow
    }
  }
#end
