// PoVRay 3.6 Include File "shapes_lo.pov"
// created by Friedrich A. Lohmueller, 05-Oct-2002,  version date 23-July-2006 
// last revised: 23-July-2006 
//   error in segment_macros fixed
// last revised: 26-June-2005 
//   added:  macro Segment_of_Object 
//   added:  macro Segment_of_CylinderRing 
//   added:  macro Segment_of_Torus 
//   all new macros with left handed angles !!! 
// 
// email:  Friedrich.Lohmueller_AT_t-online.de
// website: http://www.f-lohmueller.de 
//--------------------------------------------------------------------------
// content:
//
//  This file contains the following shapes declared by macro or as objects:
//
// #macro  Segment_of_Object ( SEgment_OBject, Segment_Angle)
// #macro  Segment_of_CylinderRing ( R_out, R_in, Height, Segment_Angle)
// for compatibility to older versions, defined with right handed angle: 
//   #macro Cylinder_Ring_Segment ( R_out, R_in, Height, Segment_Angle)  
// #macro Segment_of_Torus ( R_major, R_minor, Segment_Angle)
// for compatibility to older versions, defined with right handed angle: 
//   #macro Torus_Segment( R_major, R_minor, Segment_Angle)   
// #macro Round_Tube_Ring_N (N, Tube_R, Base_Width, Edge_R)
// #macro Column_N (N, Radius, Height ) 
// #macro Pyramid_N (N, Radius1, Radius2, Height )
//
// #macro Egg_Shape (Lower_Scale, Upper_Scale) 
// #declare Egg  (uses #macro Egg_Shape) 
// #macro Facetted_Sphere (Quarter_Segments, Radial_Segments) 
// #macro Facetted_Egg_Shape (Quarter_Segments, Radial_Segments, Lower_Scale, Upper_Scale)
// #macro Facetted_Egg(N_Quarter_Segments, N_Radial_Segments) 
// #macro Ring_Sphere (Rmaj_H, Rmaj_V, Rmin_H, Rmin_V, Number_of_Rings_horizontal, Number_of_Rings_vertical)
//
//
//
#include "debug.inc"

//------------------------------------------------------------------------
#ifndef( Shapes_Lo_Inc_Temp )
#declare Shapes_Lo_Inc_Temp = version;
#version 3.5;


//--------------------------------------------------- Segment_of_Object macro
#macro  Segment_of_Object ( SEgment_OBject, Segment_Angle_)
#local D = 0.0001; // just a little bit
#local Segment_Angle = Segment_Angle_;

#if (Segment_Angle = 0) #local Segment_Angle = D; #end

#if (abs(Segment_Angle) >= 360) #local Segment_Angle = mod (Segment_Angle, 360); #end

#local O_min = min_extent ( SEgment_OBject );
#local O_max = max_extent ( SEgment_OBject );

#local O_max_x = max (O_min.x, O_max.x); 
#local O_max_z = max (O_min.z, O_max.z); 

#local R_max = 1.5*max(O_max_x,O_max_z);
  
#if (Segment_Angle > 0) 
   #local Box_z = R_max+D;  
#else 
   #local Box_z = -R_max+D; 
#end

 
 intersection{ 
  object{ SEgment_OBject }

  #if (abs(Segment_Angle) >= 180) 
  union{
  #end // then use union!

   box { <-R_max+D,O_min.y-D,0>,< R_max+D, O_max.y+D,-Box_z> 
         rotate<0,0,0> 
       }// end of box
 
   box { <-R_max+D,O_min.y-D, Box_z>,< R_max+D, O_max.y+D,0> 
         rotate<0, Segment_Angle,0> 
        }// end of box

  #if (abs(Segment_Angle) >= 180) 
   } // end of union
  #end // end of union, if union is used!
  
} // end of intersection  

#end // end of macro ------------------------- end of macro Segment_of_Object -----

// sample of how to use it:
/*
// ------------------------------------------------------------------
#declare My_Test_Object =
difference{
 union{ // positiv
 sphere { <0,0,0>, 2.75 
          texture { pigment{ color rgb< 0.5, 1.0, 0.0>}
                    finish { ambient 0.1 diffuse 0.85  phong 1}
                  } // end of texture 
           scale<1,1,1>  rotate<0,0,0>  translate<0,0,0>  
        }  // end of sphere ----------------------------------- 
 torus { 1.5,0.3 
        texture { pigment{color rgb<0.5,1.0,0>}
                  finish {ambient 0.15 diffuse 0.85 phong 1}
                } // end of texture
        scale <1,1,1> rotate<0,0,0> translate<0,2.5,0>
      } // end of torus  -------------------------------              
 }// end of union

 sphere { <0,0,0>, 2.15 
          texture { pigment{ color rgb<1,0.6,0> } 
                    finish { ambient 0.1 diffuse 0.85  phong 1}
                  } // end of texture  
           scale<1,1,1>  rotate<0,0,0>  translate<0,0,0>  
        }  // end of sphere ----------------------------------- 
 cylinder { <0,-1.5,0>,<0,3.5,0>, 1.50 
           texture { pigment { color rgb<1,1,1>}
                     finish  { ambient 0.15 diffuse 0.85 phong 0.5}
                   } // end of texture
           scale <1,1,1> rotate<0,0,0> translate<0,0,0>
         } // end of cylinder  ------------------------------ ------
  scale<1,0.6,1>  rotate<0,0,0>  translate<0,0,0>  
} // end of diff


#include "shapes_lo.inc"
object{  Segment_of_Object (My_Test_Object, -225)   

         texture { pigment{ color rgb<1,1,1>*1.2} 
                   // normal { bumps 0.5 scale 0.05}
                   finish { ambient 0.1 diffuse 0.85  phong 1}
                 } // end of texture 

        scale <1,1,1> rotate<0,0,0> translate<0,0,0>
      }
// ------------------------------------------------------------------
*/


// ------------------------------------------------------------------
//--------------------------------------------------- Segment_of_CylinderRing macro
#macro  Segment_of_CylinderRing ( R_out, R_in, Height, Segment_Angle_)
#local Segment_Angle = Segment_Angle_;
#local D = 0.0001; // just a little bit

 #if (Height = 0 ) #local  Height = D; #end
 #if (Height < 0 ) #local  D = -D; #end

 #if (R_out < R_in) #local X=R_out; #local R_out=R_in; #local R_in=X; #end
 
 #if (Segment_Angle < 0) 
      #local Negativ_Flag = 1; 
      #local Segment_Angle = -Segment_Angle; 
 #else 
      #local Negativ_Flag = 0;
 #end
 

 #if (Segment_Angle >= 360) #local Segment_Angle = mod (Segment_Angle, 360); #end

 intersection{ 
   cylinder { <0,0,0>,<0,Height,0>, R_out 
            } // end of outer cylinder  ----------
   cylinder { <0,-D,0>,<0,Height+D,0>, R_in 
              inverse
            } // end of inner cylinder  ----------


  #if (Segment_Angle > 0) // ------------------------------------------------------
  #if (Segment_Angle >= 180)
  union{
  #end // then use union!

   box { <-R_out+D,-D,0>,< R_out+D, Height+D, R_out+D> 
         rotate<0,0,0> 
       }// end of box
 
   box { <-R_out+D,-D,-R_out+D>,< R_out+D, Height+D,0> 
         rotate<0,  Segment_Angle,0>  
       }// end of box

  #if (Segment_Angle >= 180)
   } // end of union
  #end // end of union, if union is used!
  
 #if (Negativ_Flag = 1)  rotate<0,-Segment_Angle,0>   #end   
 scale<-1,1,-1> 
 #end // of "#if (Segment_Angle > 0)" --------------------------------------------

} // end of intersection  
 

#end // end of macro ------------------------- end of Segment_of_CylinderRing macro ------
                                               

// --------------- for compatibility to older versions, defined with right handed angle: 
#macro Cylinder_Ring_Segment   ( R_out_old, R_in_old, Height_old, Segment_Angle_old)
 object{ Segment_of_CylinderRing ( R_out_old, R_in_old, Height_old, Segment_Angle_old)
         scale<1,1,-1>}
#end //---------------------------------------------------------------------------------



// sample of how to use it:
/*
#include "shapes_lo.inc"
// ------------------------------------------------------------------
object{  Segment_of_CylinderRing ( 2.75, 2.25 , 0.2, 90)   

         texture {  pigment{ color rgb<0.5,1,0>} 
                    finish { ambient 0.1 diffuse 0.85  phong 1}
                 } // end of texture 

        scale <1,1,1> rotate<0,0,0> translate<0,0,0>
      }
// ------------------------------------------------------------------
*/

 
//--------------------------------------------------------Segment_of_Torus macro
#macro Segment_of_Torus ( R_major, R_minor, Segment_Angle_)
//---------------------------------------------------------------------------
 #local D =  0.00001;
 #local Segment_Angle = Segment_Angle_;

 #if (Segment_Angle < 0) 
      #local Negativ_Flag = 1; 
      #local Segment_Angle = -Segment_Angle; 
 #else 
      #local Negativ_Flag = 0;
 #end

#if (Segment_Angle > 360) #local Segment_Angle = mod(Segment_Angle,360); #end
intersection{
 torus { R_major, R_minor }

#if (Segment_Angle > 180)
 union{
#end // use union!

 box   { <-1,-1,0>,<1,1,1>
         scale < R_major+R_minor+D, R_minor+D, R_major+R_minor+D>
       }// end of box
 box   { <-1,-1,-1>,<1,1,0>
         scale < R_major+R_minor+D, R_minor+D, R_major+R_minor+D>
         rotate < 0,-Segment_Angle,0 >
       }// end of box

#if (Segment_Angle > 180)
 }
#end // end of union, if union is used!

 #if (Negativ_Flag = 0)  rotate<0,Segment_Angle,0>   #end 

 } // end of intersection
#end  // end of macro Torus_Segment( ... ) ---------------- end of macro Segment_of_Torus


// for compatibility to older versions, defined with right handed angle: 
#macro Torus_Segment ( R_major_old, R_minor_old, Segment_Angle_old)
 object{ Segment_of_Torus( R_major_old, R_minor_old, Segment_Angle_old)
         scale<1,1,-1>}
#end //------------------------------------------------------------------

// sample of how to use it:


/*   
#include "shapes_lo.inc"
//#macro Segment_of_Torus( R_major, R_minor, Segment_Angle) ----
object{ Segment_of_Torus ( 1.00, 0.15,-270)
        texture { pigment{color rgb<0.5,1,0>}       // YellowGreen
                  finish {ambient 0.15 diffuse 0.85 phong 1}
                } // end of texture
        scale <1,1,1> rotate<0,0,0> translate<0,0,0>
      } // end of Torus_Segment(...) ------------------------              
*/


//----------------------------------------------------- Round_Tube_Ring_N (...) macro
#macro Round_Tube_Ring_N (N, Tube_R, Base_Width, Edge_R)
#local D = 0.0001; // just a little bit

#if (Edge_R > Base_Width)  #declare Edge_R=Base_Width; #end
#if (N < 3 ) #declare N = 3; #end
#declare Edge_Angle = 360/N ;
#declare Linear_Half_Len = (Base_Width-Edge_R)*tan(radians(Edge_Angle/2));

#declare Edge_Part =
object{ Torus_Segment( Edge_R, Tube_R, Edge_Angle)
        rotate<-90,0,0> translate<Base_Width-Edge_R,Linear_Half_Len,0>
      } // end of Torus_Segment(...) ------------------------------------              
  #if (Edge_R != Base_Width)
#declare Linear_Part =
cylinder { <0,-Linear_Half_Len-D,0>,<0,Linear_Half_Len+D,0>,Tube_R
           scale <1,1,1> rotate<0,0,0> translate<Base_Width,0,0>
         } // end of cylinder
  #end  

#if (Edge_R != Base_Width)
#declare One_Segment =
union{
        object {Linear_Part}
        object {Edge_Part}
       translate<0,0,0>                             
     }
#else 
#declare One_Segment =
        object {Edge_Part}
#end

union{
 #local Nr = 0;     // start
 #local EndNr = N; // end
 #while (Nr< EndNr) 
   object{One_Segment rotate<0,0,Nr * 360/EndNr>} 

 #local Nr = Nr + 1;    // next Nr
 #end // ---------------  end of loop 
}
#end // -----------  end of #macro Round_Tube_Ring_N (N, Tube_R, Base_Width, Edge_R) 

// sample of how to use it:
/*  
#include "shapes_lo.inc"
//#macro Round_Tube_Ring_N (N, Tube_R, Base_Width, Edge_R)  ---------------
object{ Round_Tube_Ring_N (3, 0.075, 0.90, 0.35) 
        texture { Polished_Chrome 
                  pigment{color rgb<1,0.7,0.2>}
                  finish {ambient 0.15 diffuse 0.85 phong 1 reflection 0.3}
                } // end of texture
        rotate<0,0,0>
        translate<0.2,1.4,0>} 
     // end of object -----------------------------------------------------
*/



 
//------------------------------------------------------------------ Pyramid_N macro
#macro Pyramid_N (N, Radius1, Radius2, Height ) 
//----------------------------------------------------------------------------------
#local D= 0.000001; // a little bit to avoid coincident surfaces in intersection

intersection{
 #local Nr = 0;    // start
 #local EndNr = N; // end
 #while (Nr< EndNr) 
   
  // linear prism in z-direction: from ,to ,number of points (first = last)
  prism { -2.00 ,2.00 , 5
         <-2.00, 0.00-Nr*D>,< 1.00,0.00-Nr*D>,< 0.00+Radius2/Radius1,1.00+Nr*D>,<-2.00,1.00+Nr*D>,<-2.00,0.00-Nr*D>
         rotate<-90,0,0> scale<1,1,-1> //turns prism in z direction! 
         scale<Radius1+Nr*D,Height+Nr*D,Radius1+Nr*D>
         rotate<0,Nr * 360/EndNr,0>
     } // end of prism -------------------------------------------------------------

 #local Nr = Nr + 1;    // next Nr
 #end // ----------------  end of loop 
} // end of intersection

#end // ----------------------------------- end of macro Pyramid_N (N, Radius1, Radius2, Height ) 

// sample of how to use it:
/*  
#include "shapes_lo.inc"
//#macro Pyramid_N (N, Radius1, Radius2, Height )

object{ Pyramid_N (11, 2.00, 0.80, 2.30 )
        texture { pigment{color rgb<1 ,1,1>*1.2} 
                  finish {ambient 0.05 diffuse 0.75 phong 1}
                }
        scale <1,1,1> rotate< 0,0, 0>  translate< 0, 0, 0>
      } // end of object ------------------------------------

*/
//------------------------------------------------------------------ Column_N macro
#macro Column_N  (N, Radius, Height ) 
//------------------------------------------------------------------
object{ Pyramid_N (N, Radius, Radius, Height )
      }
#end // ----------------------------------------- end of  macro N_Column (N, Radius, Height )

// sample of how to use it:
/*  
#include "shapes_lo.inc"
//#macro Column_N (N, Radius, Height )
object{  Column_N (14, 1.8, 2.30 )
         texture { pigment{color rgb<1 ,1,1>*1.2} 
                   finish {ambient 0.05 diffuse 0.95 phong 1}
                 }
         scale <1,1,1> rotate< 0,0, 0>  translate< 0, 0, 0>
      } // end of object ------------------------------------
*/


// ------------------------------------------------------------ shape of an egg by #macro 
#macro Egg_Shape (Lower_Scale, Upper_Scale)                  // 
// ------------------------------------------------------------
#local Egg_Lower_Part =
         difference {
                      sphere{<0,0,0>,1 scale<1,Lower_Scale,1>}
                      box{<-1,0,-1>,<1,Lower_Scale,1>}
                    } //---------------------------------------
#local Egg_Upper_Part =
         difference {
                      sphere {<0,0,0>,1 scale<1,Upper_Scale,1>}
                      box {<-1,-Upper_Scale,-1>,<1,0,1>}
                     }//---------------------------------------
//-------------------------------------------------------------
  union { 
          object {Egg_Upper_Part}
          object {Egg_Lower_Part}
          translate<0,Lower_Scale,0>
          scale 2/(Lower_Scale+Upper_Scale) 
           
        } // end of union ------------------------------------
#end //------------------------------------------------------- end of the egg macro
// sample of how to use it:
/*  
#include "shapes_lo.inc"
object { Egg_Shape (1.75, 0.65) 
         texture{ pigment{color rgb<1,1,1>*1}
                  normal {bumps 0.5 scale 0.0125}
                  finish {ambient 0.05 diffuse 0.75 phong 1 reflection 0.15}
                } // end of texture
         rotate <0,0,0>
         translate< 0, 0, 0>
       } // end of object
*/ 

// ----------------------------------------------------------- shape of simple egg
#declare Egg = object { Egg_Shape (1.15,1.55)} 
// ----------------------------------------------------------- end of the egg object


// -----------------------------------------------------------------macro Facetted_Sphere
#macro Facetted_Sphere (Quarter_Meridian_Segments, Equatorial_Segments)
     //Facettierte_Kugel (Viertelskreis_Teilung, Equatorial_Teilung)

#local Facets_Silhouette =
 prism { 
   -2 ,2 , 
   2*Quarter_Meridian_Segments+4
   < -2,-1.00>, 

   #local Nr    = -Quarter_Meridian_Segments; 
   #local EndNr =  Quarter_Meridian_Segments;
   #while (Nr< EndNr+1)
     #local Angle_degrees = Nr* 90/EndNr;
     #local Angle_radians = radians(Angle_degrees);
   < cos(Angle_radians) , sin(Angle_radians)>,
     
   #local Nr = Nr + 1 ;     
   #end       
   < -2, 1>,
   < -2,-1> 
      
 rotate<-90,0,0> scale<1,1,-1> //turns prism in z direction! Don't change this line! 
 } // end of prism object --------------------------------------------------------

intersection{
 #local Nr = 0;                  // start
 #local EndNr = Equatorial_Segments; // end
 #while (Nr< EndNr) 
 
 object{ Facets_Silhouette rotate<0,Nr * 360/EndNr,0>} 

 #local Nr = Nr + 1;    // next Nr
 #end // ---------------  end of loop 

} // end of intersection

#end // ---------------------------------------------- end of  macro Facetted_Sphere

// sample of how to use it:

/*  
#include "shapes_lo.inc"
object{ Facetted_Sphere (6, 16 )
        texture {pigment{color White*1.0} 
                 finish {ambient 0.08 diffuse 0.82 phong 0.1}
                }
        translate< 0, 1, 0>
      }
*/
//--------------------------------------------------------------------------------------  


// ------------------------------------------------------------------------------- macro Facetted_Egg_Shape
#macro Facetted_Egg_Shape (Quarter_Segments, Radial_Segments, Lower_Scale, Upper_Scale)
     //Facettierte_Kugel (Viertelskreis_Teilung, Radial_Teilung)
#local Facets_Silhouette =
union{
 prism { 
   -2 ,2 ,  Quarter_Segments +3
   < -2,-1.00>, 
 #local Nr    =  -Quarter_Segments; 
 #local EndNr =  0;
 #while (Nr< EndNr+1)
   #local Angle_degrees = Nr* 90/Quarter_Segments;
   #local Angle_radians = radians(Angle_degrees);
   < cos (Angle_radians) , sin (Angle_radians)> ,
 #local Nr = Nr + 1 ;     
 #end       
   < -2, 0> 
 rotate<-90,0,0> scale<1,1,-1> //turns prism in z direction! Don't change this line! 
 scale<1,Lower_Scale,1>
 } // end of prism object ----------------------------------------------------------

 prism { 
  -2 ,2 , Quarter_Segments+4
  < -2, 0>, 
  #local Nr    =  0; 
  #local EndNr =  Quarter_Segments;
  #while (Nr< EndNr+1)
   #local Angle_degrees = Nr* 90/Quarter_Segments;
   #local Angle_radians = radians(Angle_degrees);
  < cos (Angle_radians) , sin (Angle_radians)> ,
  #local Nr = Nr + 1 ;     
  #end       
  < -2, 1>,
  < -2, 0> 
 rotate<-90,0,0> scale<1,1,-1> //turns prism in z direction! 
 scale<1,Upper_Scale,1>
 } // end of prism object -------------------------------------------
}// end of union

intersection{
 #local Nr = 0;                  // start
 #local EndNr = Radial_Segments; // end
 #while (Nr< EndNr) 
 
 object{ Facets_Silhouette rotate<0,Nr * 360/EndNr,0>} 

 #local Nr = Nr + 1;    // next Nr
 #end // ---------------  end of loop 
} // end of intersection

#end // ------------------------------------------- end of macro Facetted_Egg
// sample of how to use it:

/*  
#include "shapes_lo.inc"
object{ Facetted_Egg_Shape (9, 16 ,1.15,1.55)
        texture {pigment{color White} 
                 finish {ambient 0.05 diffuse 0.75 phong 0.1}
                }
        translate <0,1.15,0>
        scale 2/(1.15+1.55)
        rotate<0,0,0> 
        translate<0,ß,0>
      } // end of object ------------------------------------
*/
//---------------------------------------------------------------------------
// ------------------------------------------------------------------------------- macro Facetted_Egg
#macro Facetted_Egg(N_Quarter_Segments, N_Radial_Segments) 
  object{ Facetted_Egg_Shape(N_Quarter_Segments, N_Radial_Segments, 1.15, 1.55)
          translate < 0, 1.15, 0>
          scale 2/(1.15 + 1.55)
         }
#end
//---------------------------------------------------------------------------
/*
#include "shapes_lo.inc"
object{ Facetted_Egg (9, 16)
        texture { pigment{color White} 
                  finish {ambient 0.0 diffuse 0.75 phong 0.1}
                }
        scale 1
        rotate<0,0,0> 
        translate<0,0,0>
      } //---------------------------------------------------
*/

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


//Sphere with latitudes by steps in degrees      ----- Globus 
//Kugel mit BreitenGrade in Gradschritten        ----- Globus 
#macro Ring_Sphere (Rmaj_H, Rmaj_V, Rmin_H, Rmin_V, 
                    Number_of_Rings_horizontal, Number_of_Rings_vertical)
#if (Rmin_H > 0)
#declare RingsH1 = 
union{
#declare AngleD = 180/ Number_of_Rings_horizontal;
#declare Nr = -90+AngleD; #declare EndNr = 90; // --- start and end
// Nr = value of the angle - Winkelwert!!!! 

#while (Nr< EndNr)
 #declare RingR = Rmaj_H*cos(radians(Nr)); //sqrt( pow(R0,2) - pow((Nr*HDiff),2) );
 #declare RingH = Rmaj_H*sin(radians(Nr));
 torus{RingR,Rmin_H scale <1,1,1>
       rotate<0,0,0>
       translate<0, RingH,0>} 
#declare Nr = Nr + AngleD;
#end // --------------- end of loop 
#declare LastR= RingR; 
}//-----------------
#end // of "#if (Rmin_H > 0)"

#if (Rmin_V > 0)
#declare RingsV1 =          // longitudes - Längengrade
union{
#declare Nr = 0; #declare EndNr = Number_of_Rings_vertical; // --- start and end
#while (Nr< EndNr)
 torus{Rmaj_V-Rmin_V,Rmin_V scale <1,1,1>
       rotate<90,0,0>
       rotate<0, Nr*360/EndNr,0>} 
#declare Nr = Nr + 1;
#end // --------------- end of loop 
}//---------------------------------
#end // of "#if (Rmin_V > 0)"

union{ #if (Rmin_H > 0) object{ RingsH1} #end
       #if (Rmin_V > 0) object{ RingsV1} #end
       sphere{<0, Rmaj_H,0>,Rmin_H} 
       sphere{<0,-Rmaj_H,0>,Rmin_H} 
      }  
#end //----------------------------------------------------------------
                                              
// sample of how to use it:

/*  

#include "shapes_lo.inc"
object{Ring_Sphere  (1.00, 1.02, 0.025, 0.025, 12,16) 
        texture {  pigment{color White*1.1}
                  finish {ambient 0.1 diffuse 0.8 phong 1 reflection 0.25}
                } // end of texture
        scale <1,1,1>
        rotate<-20,0,-7> 
        translate<0,1.00,0>
      }
*/     
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------<<<< Round_Pyramid macro 
// Round_N_Pyramid (N, Wire_Radius, Pyramid_R1, Pyramid_R2, Pyramid_Height, Fill_On, Merge_On)  
#macro Round_N_Pyramid (N, Wire_Radius, Pyramid_R1, Pyramid_R2, Pyramid_Height, Fill_On, Merge_On)  
#local RR = Wire_Radius; 
#local RP_R  = Pyramid_R1; // base radius
#local RP_R2 = Pyramid_R2; // top radius
#local RP_H  = Pyramid_Height;

#local D = 0.00001;    
#if ( N < 3) #local N = 3; #end // 3 is minimum!!!
#if ( RR = 0 ) #local RR = D; #end  
#if ( RR < 0 ) #local RR = abs(RR) ; #end
#if ( RP_R < 0 ) #local RP_R = abs(RP_R) ; #end
#if ( RP_R2 < 0 ) #local RP_R2 = abs(RP_R2) ; #end

#if ( RR = RP_R/2 ) #local RP_R = RP_R/2+D; #end
//---------------------------------------------------------------------------------------------------
#if ( RP_R < RP_R2 )  #local Delta_Xchange = RP_R; #local RP_R = RP_R2; #local RP_R2 = Delta_Xchange; 
#Debug_Message ("Warning!
                 in Rounded_N_Pyramid:
                 Pyramid_R1 must be bigger than Pyramid_R2 - values exchanged !!
                 ") 
#end 
//---------------------------------------------------------------------------------------------------
#local RA = sqrt(pow(RR,2)+pow(RR*tan(radians(180/N)),2)  );// Verkürzung des Radiuses zur Ecke - Kugelmittelpunkt
#if (RP_R2= 0) #local RP_R2 = RA; #end
 
#local P_Middle = RP_R*cos(radians(180/N));
#local P_Middle_up = RP_R2*cos(radians(180/N));

#local P_Side   = P_Middle*tan(radians(180/N)); // half base side
#local P_Side2  = P_Middle_up*tan(radians(180/N)); // half top side

#local P_Angle  = degrees(atan2( RP_H, (P_Middle-P_Middle_up))); // pending sides angle 
#local RR_sin = RR*sin(radians(P_Angle)); 
#local RR_cos = RR*cos(radians(P_Angle));
//----------------------------------------------------------------------
#if (Merge_On = 1)
merge{
#else
union{
#end // of #if (Merge_On = 1) .............    

 #if (RP_R2 = RA )
  sphere{< 0, RP_H, 0>,RR }  
 #end 
 #local Nr = 0; 
 #while (Nr< N) 
  union{ sphere{< RP_R -RA,    0, 0>,RR}                        // lower
          cylinder {< RP_R-RA, 0, 0>,< RP_R2-RA, RP_H, 0>,RR }    // sides low to up
         cylinder {< RP_R-RA, 0, 0>, vaxis_rotate(< RP_R-RA,  0, 0>,<0,1,0>,360/N),RR } // lower sides ring
         rotate<0,Nr*360/N,0>}

  #if (RP_R2 != RA )
  union{ sphere{< RP_R2-RA, RP_H, 0>,RR}                        // upper
         cylinder {< RP_R2-RA, 0, 0>,vaxis_rotate(< RP_R2-RA, 0, 0>,<0,1,0>,360/N),RR translate<0,RP_H,0>} // upper sides ring
         rotate<0,Nr*360/N,0>}                       
  #end 
  
 #local Nr = Nr + 1;
 #end  //-------------------------- end of wire frame
#if (Fill_On = 1)  // ------------------------ filling
union{ 
 #local Nr = 0; 
 #while (Nr< N) 
 intersection{    
  prism { -RR ,RP_H+RR , 4 // prism y
          < RR_sin, 0>,< P_Middle+RR_sin, P_Side>,< P_Middle+RR_sin,-P_Side>,< RR_sin, 0>
          rotate<0,360/N/2,0>                                } // end of prism -------------------------------------
  prism{ -RP_R-D , RP_R+D, 7 // prism z 
          < 0,-RR>,< P_Middle-RR,-RR>,
                   < P_Middle   -RR+RR_sin, RR_cos>,
                   < P_Middle_up-RR+RR_sin, RR_cos+RP_H>,
                   < RR_sin               , RP_H+RR_cos>,
                   < 0, RP_H>,< 0,-RR>
          rotate<-90,0,0> scale<1,1,-1> rotate<0,360/N/2,0>  } // end of prism -------------------------------------
  rotate<0,Nr*360/N,0>}// end of intersection
 #local Nr = Nr + 1;
 #end  

 
 intersection{  // lower cover  
  #local Nr = 0; 
  #while (Nr< N) 
      box{<-1.5*RP_R,-RR-D/100*Nr,-RP_R>,<P_Middle-RR,0, RP_R> 
        rotate<0,(Nr+0.5)*360/N,0>}
 
 #local Nr = Nr + 1;
 #end  
 }// end of intersection

 intersection{   // upper cover 
  #local Nr = 0; 
  #while (Nr< N) 
      box{<-1.5*RP_R,RP_H-RR,-RP_R>,<P_Middle_up-RR,RP_H+RR-D/100*Nr, RP_R> 
        rotate<0,(Nr+0.5)*360/N,0>}
 
 #local Nr = Nr + 1;
 #end  
 }// end of intersection
 
 }// end of union II


#end // of (Fill_On = 1) ---------- end of filling

} #end//------------------------- end of union and macro   Round_Pyramid (...)  ---------<<<


/*
// ------------------------- drawing --------------------------------------------

//#macro Round_N_Pyramid (N, Wire_Radius, Pyramid_R1, Pyramid_R2, Pyramid_Height, Fill_On, Merge_On)  
object{ Round_N_Pyramid (7, 0.10 , 1.00, 0.70, 0.45 , 1, 0)        
        texture{ pigment{color rgb<1,1,1>*1.0}
                 normal {bumps 0.15 scale 0.0005}
                 finish {ambient 0.1 diffuse 0.85 phong 1}}
rotate<  0,0,0> 
scale<1,1,1>
translate<0.1,0.2, 0.2>}
*/
//----------------------------------------------------------------------- end of file

#version Shapes_Lo_Inc_Temp;
#end
//--------------------------------------------------------------------- end of include file ---------------
