# find ODE (Open Dynamics Engine) includes and library
#
# ODE_INCLUDE_DIR - where the directory containing the ODE headers can be
#                   found
# ODE_LIBRARY     - full path to the ODE library
# ODE_DEFINITIONS - the output of `ode-config --cflags'
# ODE_CONFIG      - the path to the ode-config command
# ODE_FOUND       - TRUE if ODE was found
#
# AUTHOR: Carlo Pinciroli <cpinciro@ulb.ac.be>

# Look for the header files
FIND_PATH(ODE_INCLUDE_DIR ode/ode.h
  /usr/include
  /usr/local/include
)
IF(ODE_INCLUDE_DIR)
  MESSAGE(STATUS "Found ODE include dir: ${ODE_INCLUDE_DIR}")
ELSE(ODE_INCLUDE_DIR)
  MESSAGE(STATUS "Could NOT find ODE headers.")
ENDIF(ODE_INCLUDE_DIR)

# Look for the library file
FIND_LIBRARY(ODE_LIBRARY
  NAMES ode
  PATHS
  /usr/lib
  /usr/local/lib
)
IF(ODE_LIBRARY)
  MESSAGE(STATUS "Found ODE library: ${ODE_LIBRARY}")
ELSE(ODE_LIBRARY)
  MESSAGE(STATUS "Could NOT find ODE library.")
ENDIF(ODE_LIBRARY)

# By default, ODE has not been found
SET(TMP_ODE_FOUND FALSE)

# If both were found, proceed with more checks, otherwise bomb out
IF(ODE_INCLUDE_DIR AND ODE_LIBRARY)
  # Proceed with more checks
  # Check for the existence of ode-config
  FIND_PROGRAM(ODE_CONFIG ode-config)
  IF(ODE_CONFIG)
    # ode-config found, get the cflags
    EXECUTE_PROCESS(COMMAND ${ODE_CONFIG} --cflags OUTPUT_VARIABLE ODE_DEFAULT_CFLAGS)
    STRING(REGEX MATCH "-DdSINGLE|-DdDOUBLE" TMP_ODE_DEFINITIONS "${ODE_DEFAULT_CFLAGS}")
    SET(ODE_DEFINITIONS "${TMP_ODE_DEFINITIONS}" CACHE STRING "ODE-specific compilation flags.")
    # Was a specific minimum version required?
    IF(ODE_FIND_VERSION)
      # Minimum version required, check for it
      # Get the version string of the installed library
      EXECUTE_PROCESS(COMMAND ${ODE_CONFIG} --version OUTPUT_VARIABLE ODE_VERSION)
      MESSAGE(STATUS "Found ODE version: ${ODE_VERSION}")
      # Check that the installed version is at least equal to the requested version
      IF("${ODE_VERSION}" VERSION_LESS "${ODE_FIND_VERSION}")
        # The installed version is less than the installed one, bomb out
        SET(ODE_ERROR_MESSAGE "Skipping ODE. The installed ODE is older than ${ODE_FIND_VERSION}.")
      ELSE("${ODE_VERSION}" VERSION_LESS "${ODE_FIND_VERSION}")
        # The installed version is OK
        SET(TMP_ODE_FOUND TRUE)
      ENDIF("${ODE_VERSION}" VERSION_LESS "${ODE_FIND_VERSION}")
    ELSE(ODE_FIND_VERSION)
      # No specific version was asked, it's ok like this
      MESSAGE(STATUS "No specific version was asked, it's ok like this")
      SET(TMP_ODE_FOUND TRUE)
    ENDIF(ODE_FIND_VERSION)
  ELSE(ODE_CONFIG)
    # ode-config was not found -> we can't get version info -> bomb out
    SET(ODE_ERROR_MESSAGE "Could not find command ode-config. Check your ODE installation.")
  ENDIF(ODE_CONFIG)
ENDIF(ODE_INCLUDE_DIR AND ODE_LIBRARY)

# Make ODE_FOUND a cache variable
SET(ODE_FOUND ${TMP_ODE_FOUND} CACHE BOOL "Whether ODE was found or not.")
MARK_AS_ADVANCED(ODE_FOUND ODE_CONFIG ODE_LIBRARY ODE_INCLUDE_DIR ODE_DEFINITIONS)
  
# Missing headers and/or library, bomb out
IF(NOT ODE_FOUND)
  IF(ODE_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "${ODE_ERROR_MESSAGE}")
  ELSE(ODE_FIND_REQUIRED)
    MESSAGE(STATUS "${ODE_ERROR_MESSAGE}")
  ENDIF(ODE_FIND_REQUIRED)
ELSE(NOT ODE_FOUND)
  MESSAGE(STATUS "ODE found.")
ENDIF(NOT ODE_FOUND)
