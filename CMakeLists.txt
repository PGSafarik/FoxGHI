CMAKE_MINIMUM_REQUIRED( VERSION 3.10 )
PROJECT( FXGHI VERSION 0.1 DESCRIPTION "A small library that extends Foxtoolkit with Gnome 3-style Top-level windows" )

# The project settings
SET( CMAKE_INSTALL_PREFIX "/opt/foxghi/0.1/1" )  # Install target directory
SET( LIB_FOX   "/opt/foxlib/1.7/64" )            # Fox toolkit path
SET( CMAKE_CXX_STANDARD 98 )                     # C++ Standard
SET( CMAKE_CXX_STANDARD_REQUIRED True )          # C++ Standard
#add_compile_options(-Wall -Wextra -pedantic -Werror)
#add_compile_options(-Wall -pedantic)

# Configure project
FILE( GLOB SOURCES src/*.cpp )                          # List of implementation files
FILE( GLOB HEADERS include/*.h )                        # List of C++ header files (for install - API)
INCLUDE_DIRECTORIES( "${PROJECT_SOURCE_DIR}/include" )  # Insert include directory for building

# Add directories for project dependency
INCLUDE_DIRECTORIES( "${LIB_FOX}/include/" )    # foxlib API
LINK_DIRECTORIES(    "${LIB_FOX}/lib/" )        # foxlib shared 

# Add to the shared library
ADD_LIBRARY( ${PROJECT_NAME} SHARED ${SOURCES} )  # Make project shared lib (.so)
TARGET_LINK_LIBRARIES( ${PROJECT_NAME} FOX-1.7 )  # Linked project with dependecies libs

# Install build project
INSTALL( TARGETS ${PROJECT_NAME} DESTINATION lib/ ) # libray file(s)
INSTALL( FILES ${HEADERS} DESTINATION include/ )    # API (C++ header files)

### END ###
