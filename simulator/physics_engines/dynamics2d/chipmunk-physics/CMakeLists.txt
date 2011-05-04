set(chipmunk_HEADERS
  include/chipmunk.h
  include/chipmunk_ffi.h
  include/chipmunk_types.h
  include/chipmunk_unsafe.h
  include/constraints/cpConstraint.h
  include/constraints/cpDampedRotarySpring.h
  include/constraints/cpDampedSpring.h
  include/constraints/cpGearJoint.h
  include/constraints/cpGrooveJoint.h
  include/constraints/cpPinJoint.h
  include/constraints/cpPivotJoint.h
  include/constraints/cpRatchetJoint.h
  include/constraints/cpRotaryLimitJoint.h
  include/constraints/cpSimpleMotor.h
  include/constraints/cpSlideJoint.h
  include/constraints/util.h
  include/cpArbiter.h
  include/cpArray.h
  include/cpBB.h
  include/cpBody.h
  include/cpCollision.h
  include/cpHashSet.h
  include/cpPolyShape.h
  include/cpShape.h
  include/cpSpace.h
  include/cpSpaceHash.h
  include/cpVect.h
  )

set(chipmunk_IMPLEMENTATIONS
  src/chipmunk.c
  src/constraints/cpConstraint.c
  src/constraints/cpDampedRotarySpring.c
  src/constraints/cpDampedSpring.c
  src/constraints/cpGearJoint.c
  src/constraints/cpGrooveJoint.c
  src/constraints/cpPinJoint.c
  src/constraints/cpPivotJoint.c
  src/constraints/cpRatchetJoint.c
  src/constraints/cpRotaryLimitJoint.c
  src/constraints/cpSimpleMotor.c
  src/constraints/cpSlideJoint.c
  src/cpArbiter.c
  src/cpArray.c
  src/cpBB.c
  src/cpBody.c
  src/cpCollision.c
  src/cpHashSet.c
  src/cpPolyShape.c
  src/cpShape.c
  src/cpSpace.c
  src/cpSpaceHash.c
  src/cpVect.c
  )

include_directories(${CMAKE_SOURCE_DIR}/physics_engines/dynamics2d/chipmunk-physics/include)
add_library(chipmunk SHARED ${chipmunk_IMPLEMENTATIONS})
set_target_properties(chipmunk PROPERTIES VERSION 5.3.1)

install(TARGETS chipmunk
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos2
  ARCHIVE DESTINATION lib/argos2)
