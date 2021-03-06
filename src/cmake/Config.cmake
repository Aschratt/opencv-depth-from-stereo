###################################################################################################
#####                                                                                         #####
#####                         Contains project build configuration.                           #####
#####                                                                                         #####
###################################################################################################

# C++ standard version.
SET(CMAKE_CXX_STANDARD 17)

# Define C++ compile flags.
IF(MSVC)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")       # Use multi core compiling to speed up compile times.
ENDIF(MSVC)

# For debug builds, append the "d" suffix.
SET(CMAKE_DEBUG_POSTFIX "d")

# If not provided to be any different, initialize the install directory.
IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    SET(CMAKE_INSTALL_PREFIX "/install/${CMAKE_GENERATOR_PLATFORM}" CACHE PATH "Installation directory." FORCE)
ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

# Setup build artifact directory.
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/binaries/")

# Setup installation directories.
SET (CMAKE_INSTALL_BINARY_DIR  "bin/")
SET (CMAKE_INSTALL_EXPORT_DIR  "cmake/")
SET (CMAKE_INSTALL_INCLUDE_DIR "include/")

# Export all symbols automatically on Windows.
IF (WIN32)
    SET (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
ENDIF()