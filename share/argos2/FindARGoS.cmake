# Find ARGoS
#
# This module defines these variables:
#
#  ARGOS_FOUND       - True if the ARGoS libraries was found
#  ARGOS_INCLUDE_DIR - The include directory of the ARGoS libraries
#  ARGOS_LINK_DIR    - The link directory of the ARGoS libraries
#
# AUTHOR: Carlo Pinciroli <cpinciro@ulb.ac.be>

#
# Define a default exception scheme to link against
# and validate user choice.
#

#
# Find the header file
#
FIND_PATH(ARGOS_INCLUDE_DIR
  NAMES
  argos2/simulator/simulator.h
  PATHS
  /usr/include
  /usr/local/include
  DOC "ARGoS header location"
)

#
# Find the library directory
#
FIND_PATH(ARGOS_LINK_DIR
  NAMES
  libargos2_simulator.so
  PATHS
  /usr/lib/argos2
  /usr/local/lib/argos2
  DOC "ARGoS library location"
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(ARGoS DEFAULT_MSG ARGOS_LINK_DIR ARGOS_INCLUDE_DIR)

IF(ARGOS_INCLUDE_DIR AND ARGOS_LINK_DIR)
  SET(ARGOS_INCLUDE_DIRS )
  SET(ARGOS_LINK_DIRS    )
ENDIF(ARGOS_INCLUDE_DIR AND ARGOS_LINK_DIR)

MARK_AS_ADVANCED(ARGOS_INCLUDE_DIR)
MARK_AS_ADVANCED(ARGOS_LINK_DIR)

# Needed to use TinyXML++ bindings
ADD_DEFINITIONS(-DTIXML_USE_TICPP)
