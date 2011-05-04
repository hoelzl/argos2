// sky ---------------------------------------------------------------
sphere{ <0,0,0>,1 hollow    //keep attention: keep sun lower than sky
        texture{ pigment{ gradient <0,0,1>
                          color_map{[0.0 color White *0.8 ]
                                    [0.8 color rgb<0.1,0.25,0.75> ]
                                    [1.0 color rgb<0.1,0.25,0.75> ]}
                        }
                 finish {ambient 1 diffuse 0}
               }
scale 10000
}
