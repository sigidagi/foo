# - Find ZeroMQ library
#
# This module checks for the required version number and defines
# ZMQ_LIBRARIES, the libraries to link against to use ZMQ.
# ZMQ_LIB_DIR, the location of the libraries
# ZMQ_FOUND, If false, do not try to use ZMQ
#
FIND_LIBRARY (ZMQ_LIBRARIES NAMES zmq
    PATHS
    ${CMAKE_SOURCE_DIR}/build/lib
    /usr/lib
    /usr/local/lib
    /usr/lib/i386-linux-gnu
    PATH_SUFFIXES zmq 
    NO_DEFAULT_PATH
)

FIND_PATH (ZMQ_INCLUDE_DIRS zmq.h
    PATHS
    ${CMAKE_SOURCE_DIR}/build/include
    /usr/include
    /usr/local/include
    PATH_SUFFIXES zmq 
    NO_DEFAULT_PATH
)

IF(ZMQ_INCLUDE_DIRS)
    MESSAGE(STATUS "Found ZeroMQ includes: " ${ZMQ_INCLUDE_DIRS}/zmq.h)
ENDIF(ZMQ_INCLUDE_DIRS)

IF(ZMQ_LIBRARIES)
    MESSAGE(STATUS "Found ZeroMQ library: ${ZMQ_LIBRARIES}")
ENDIF(ZMQ_LIBRARIES)

IF(ZMQ_INCLUDE_DIRS AND ZMQ_LIBRARIES)
    SET(ZMQ_FOUND TRUE)
ENDIF(ZMQ_INCLUDE_DIRS AND ZMQ_LIBRARIES)

# Check found version against required one
IF (DEFINED ZMQ_CFG_FILE)
    FILE(READ "${ZMQ_CFG_FILE}" _ZMQ_VERSION_H_CONTENTS)
    STRING(REGEX MATCH "#define ZMQ_VERSION_MAJOR ([0-9])" _MATCH "${_ZMQ_VERSION_H_CONTENTS}")
    SET(ZMQ_VERSION_MAJOR ${CMAKE_MATCH_1})
    STRING(REGEX MATCH "#define ZMQ_VERSION_MINOR ([0-9])" _MATCH "${_ZMQ_VERSION_H_CONTENTS}")
    SET(ZMQ_VERSION_MINOR ${CMAKE_MATCH_1})
    STRING(REGEX MATCH "#define ZMQ_VERSION_PATCH ([0-9])" _MATCH "${_ZMQ_VERSION_H_CONTENTS}")
    SET(ZMQ_VERSION_PATCH ${CMAKE_MATCH_1})
    set (ZMQ_VERSION "${ZMQ_VERSION_MAJOR}.${ZMQ_VERSION_MINOR}.${ZMQ_VERSION_PATCH}")
    MESSAGE(STATUS "Detected ZeroMQ version number: ${ZMQ_VERSION}")
    IF (DEFINED ZMQ_VERSION AND ZMQ_VERSION VERSION_LESS ZMQ_FIND_VERSION)
        SET(ZMQ_FOUND FALSE)
        MESSAGE(STATUS "Installed version ${ZMQ_VERSION} of ZeroMQ does not meet the minimum required version of ${ZMQ_FIND_VERSION}")
        #ENDIF ()
    ELSE ()
        MESSAGE(STATUS "Unable to find zmq.h header file")
        SET(ZMQ_FOUND FALSE)
    ENDIF ()
ENDIF ()

# Report the results.
IF (NOT ZMQ_FOUND AND ZMQ_FIND_REQUIRED)
    SET(ZMQ_DIR_MESSAGE "Required version of ZeroMQ was not found.")
    MESSAGE(FATAL_ERROR "${ZMQ_DIR_MESSAGE}")
ENDIF (NOT ZMQ_FOUND AND ZMQ_FIND_REQUIRED)

MARK_AS_ADVANCED(
    ZMQ_LIBRARIES
    ZMQ_INCLUDE_DIRS
)
