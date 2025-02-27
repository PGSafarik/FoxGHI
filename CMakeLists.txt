CMAKE_MINIMUM_REQUIRED( VERSION 3.10 )
PROJECT( FXGHI DESCRIPTION "A small library that extends Foxtoolkit with Gnome 3-style Top-level windows" )

# Project Version
SET( FXGHI_VER_DATE  22 )
SET( FXGHI_VER_MONTH 02 )
SET( FXGHI_VER_YEAR  25)

SET( FXGHI_VER_MAJOR    0 )
SET( FXGHI_VER_MINOR    5 )
SET( FXGHI_VER_REVISION 2 )
SET( FXGHI_VER_BUILD    0 )

SET( FXGHI_VER_FLAG   "Alpha")
SET( FXGHI_VER_SHFLAG "a" )

SET( PROJECT_VERSION_UBUNTU 24.${FXGHI_VER_MONTH} )
SET( PROJECT_VERSION ${FXGHI_VER_MAJOR}.${FXGHI_VER_MINOR}.${FXGHI_VER_REVISION} )
SET( PROJECT_VERSION_FULL "${PROJECT_VERSION_UBUNTU} ${PROJECT_VERSION}.${FXGHI_VER_BUILD} ${FXGHI_VER_FLAG}" )

# The project settings
SET( CMAKE_INSTALL_PREFIX "/opt/foxghi/${FXGHI_VER_MAJOR}.${FXGHI_VER_MINOR}/${FXGHI_VER_REVISION}" )  # Install target directory
SET( LIB_FOX   "/opt/foxlib/1.7/84" )            # Fox toolkit path
SET( CMAKE_CXX_STANDARD 11 )                     # C++ Standard
SET( CMAKE_CXX_STANDARD_REQUIRED True )          # C++ Standard
#add_compile_options(-Wall -Wextra -pedantic -Werror)
#add_compile_options(-Wall -pedantic)

# Configure project
FILE( GLOB SOURCES src/*.cpp  src/Widgets/*.cpp src/Windows/*.cpp )  # List of implementation files
FILE( GLOB HEADERS include/*.h )
FILE( GLOB CORE_HEADERS include/Core/*.h )
FILE( GLOB WIDGETS_HEADERS include/Widgets/*.h )
FILE( GLOB WINDOWS_HEADERS include/Windows/*.h )
INCLUDE_DIRECTORIES( "${PROJECT_SOURCE_DIR}/include" )               # Insert include directory for building

SET( LDCFG_FILE_NAME "foxghi${PROJECT_VERSION}.conf" )  # set filename for ldconfig

configure_file( version.h.in "${PROJECT_SOURCE_DIR}/include/Core/version.h" )        # generate version.h file
configure_file( foxghi.conf.in "${PROJECT_SOURCE_DIR}/src/${LDCFG_FILE_NAME}" ) # generate file for ldconfig

# Add directories for project dependency
INCLUDE_DIRECTORIES( "${LIB_FOX}/include/" )    # foxlib API
LINK_DIRECTORIES(    "${LIB_FOX}/lib/" )        # foxlib shared 

# Add to the shared library
ADD_LIBRARY( ${PROJECT_NAME} SHARED ${SOURCES}
        include/Windows.h)  # Make project shared lib (.so)
TARGET_LINK_LIBRARIES( ${PROJECT_NAME} FOX-1.7 )  # Linked project with dependecies libs

# Build utils 
ADD_SUBDIRECTORY( "${PROJECT_SOURCE_DIR}/utils/FoxGHICP" )

# Build test  
ADD_SUBDIRECTORY( "${PROJECT_SOURCE_DIR}/tests/SimpleWindow" )

# Install build project
INSTALL( TARGETS ${PROJECT_NAME} DESTINATION lib/ ) # libray file(s)
INSTALL( FILES ${HEADERS} DESTINATION include/ )    # API (C++ header files)
INSTALL( FILES ${CORE_HEADERS} DESTINATION include/Core/ )
INSTALL( FILES ${WIDGETS_HEADERS} DESTINATION include/Widgets/ )
INSTALL( FILES ${WINDOWS_HEADERS} DESTINATION include/Windows/ )

INSTALL( FILES "${PROJECT_SOURCE_DIR}/src/${LDCFG_FILE_NAME}" DESTINATION /etc/ld.so.conf.d/ )
INSTALL( CODE "EXECUTE_PROCESS( COMMAND /usr/sbin/ldconfig )" )

### END ###
