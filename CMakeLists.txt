###################################################################################################
#####                                                                                         #####
#####                   Stereo Matching and Depth Estimation using OpenCV.                    #####
#####                                                                                         #####
###################################################################################################

CMAKE_MINIMUM_REQUIRED(VERSION 3.18)

# Install vcpkg dependencies automatically (experimental - might be changed or removed later; see: https://github.com/microsoft/vcpkg/issues/1653). 
SET(X_VCPKG_APPLOCAL_DEPS_INSTALL ON)
SET(VCPKG_MODULE_DIRECTORY "${CMAKE_SOURCE_DIR}/src/modules/vcpkg" CACHE STRING "VCPKG module directory." FORCE)
SET(CMAKE_TOOLCHAIN_FILE "${VCPKG_MODULE_DIRECTORY}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "VCPKG toolchain file." FORCE)

PROJECT(CVDepthFromStereo LANGUAGES CXX)

# Check if the build dir does not match the source dir (disallow in-source builds).
IF("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
   MESSAGE(SEND_ERROR "In-source builds are not allowed.")
ENDIF("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")

# Include configuration files.
INCLUDE("${CMAKE_SOURCE_DIR}/src/cmake/modules.cmake")
INCLUDE("${CMAKE_SOURCE_DIR}/src/cmake/version.cmake")
INCLUDE("${CMAKE_SOURCE_DIR}/src/cmake/config.cmake") 

# Include sub-projects.
ADD_SUBDIRECTORY(src/Disparity)
