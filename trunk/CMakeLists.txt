PROJECT(kpar2)

#if you don't want the full compiler output, remove the following line
SET(CMAKE_VERBOSE_MAKEFILE OFF)

#So that cmake can find local cmake files
SET( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" )

#add definitions, compiler switches, etc.
ADD_DEFINITIONS( -DCMAKE_INSTALL_PREFIX=${KDEDIR} )

#list all source files here
ADD_SUBDIRECTORY( src )

