#include "textures.inc"
#include "common.inc"
#include "textures.inc"
#include "stdinc.inc" 
#include "metals.inc"
#include "shapesq.inc" 
#include "shapes.inc"
#include "shapes_lo.inc"


#macro book( BOOK_POSITION, BOOK_ROTATION )



	#local SWARMANOID_BOOK_WIDTH = 0.02;
	#local SWARMANOID_BOOK_LENGTH = 0.1;
	#local SWARMANOID_BOOK_HEIGHT = 0.18;

	#local SWARMANOID_BOOK_COVER_THICKNESS = 0.01;

	#local swarmanoid_book_cover = union {
		difference {
			box{
				<SWARMANOID_BOOK_WIDTH/2,SWARMANOID_BOOK_LENGTH/2,SWARMANOID_BOOK_HEIGHT/2>,
				<-SWARMANOID_BOOK_WIDTH/2,-SWARMANOID_BOOK_LENGTH/2,-SWARMANOID_BOOK_HEIGHT/2>
				pigment {color Red}
			}

			box{
				<SWARMANOID_BOOK_WIDTH/2-SWARMANOID_BOOK_COVER_THICKNESS/2,SWARMANOID_BOOK_LENGTH/2-SWARMANOID_BOOK_COVER_THICKNESS,SWARMANOID_BOOK_HEIGHT/2+SWARMANOID_BOOK_COVER_THICKNESS>,
				<-SWARMANOID_BOOK_WIDTH/2+SWARMANOID_BOOK_COVER_THICKNESS/2,-SWARMANOID_BOOK_LENGTH/2-SWARMANOID_BOOK_COVER_THICKNESS,-SWARMANOID_BOOK_HEIGHT/2-SWARMANOID_BOOK_COVER_THICKNESS>
				pigment {color White}
			}
		}

			box{
				<SWARMANOID_BOOK_WIDTH/2-SWARMANOID_BOOK_COVER_THICKNESS/2,SWARMANOID_BOOK_LENGTH/2-SWARMANOID_BOOK_COVER_THICKNESS,SWARMANOID_BOOK_HEIGHT/2-SWARMANOID_BOOK_COVER_THICKNESS/2>,
				<-SWARMANOID_BOOK_WIDTH/2+SWARMANOID_BOOK_COVER_THICKNESS/2,-SWARMANOID_BOOK_LENGTH/2,-SWARMANOID_BOOK_HEIGHT/2+SWARMANOID_BOOK_COVER_THICKNESS/2>
				pigment {color White}
			}

	}


	union {
    		object { swarmanoid_book_cover 
			rotate BOOK_ROTATION
			translate BOOK_POSITION
		}

	}


#end
