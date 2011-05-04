
// sky ---------------------------------------------------------------
plane{<0,0,1>,1 hollow  // 
      
        texture{ pigment {color rgb<0.1,0.35,0.8>*0.8}
                          finish {ambient 1  diffuse 0}
               } // end texture 1

        texture{ pigment{ bozo turbulence 0.75
                          octaves 6  omega 0.7 lambda 2 
                          color_map {
                          [0.0  color rgb <0.95, 0.95, 0.95> ]
                          [0.05  color rgb <1, 1, 1>*1.25 ]
                          [0.15 color rgb <0.85, 0.85, 0.85> ]
                          [0.55 color rgbt <1, 1, 1, 1>*1 ]
                          [1.0 color rgbt <1, 1, 1, 1>*1 ]
                          } // end color_map 
                         translate< 3, 0,-1>
                         scale <0.3, 0.4, 0.2>*3
                        } // end pigment
                 finish {ambient 1 diffuse 0}
               } // end texture 2

      scale 10000}  
// fog at the horizon     
fog{distance 300000 color White}
