###################################################################################################
#####                                                                                         #####
#####         Disparity - app that uses stereo matching to compute disparity maps.            #####
#####                                                                                         #####
###################################################################################################

PROJECT(Disparity VERSION ${APP_VERSION} LANGUAGES CXX)

# Install packages.
MESSAGE(STATUS "Installing package dependencies...")
VCPKG_INSTALL(OpenCV)

# Resolve package dependencies.
FIND_PACKAGE(OpenCV CONFIG REQUIRED core)

ADD_EXECUTABLE(Disparity
    "demo.hxx"
    "demo.cpp"
)

# Setup project properties.
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
    FOLDER "Apps"
    VERSION ${APP_VERSION}
    SOVERSION ${APP_YEAR}
)

# Setup project dependencies.
TARGET_LINK_LIBRARIES(${PROJECT_NAME}
    PUBLIC ${OpenCV_LIBS}
)

# Set target link options to enable debugging.
TARGET_LINK_OPTIONS(${PROJECT_NAME} 
    PUBLIC $<$<OR:$<CONFIG:>,$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:/DEBUG /ASSEMBLYDEBUG>
)

# Setup installer.
INSTALL(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_BINARY_DIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_BINARY_DIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINARY_DIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDE_DIR}
)

# Export config.
INSTALL(EXPORT ${PROJECT_NAME}Config DESTINATION ${CMAKE_INSTALL_EXPORT_DIR})
EXPORT(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}Config.cmake)
