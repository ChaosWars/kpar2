PROJECT( kpar2 )
CMAKE_MINIMUM_REQUIRED( VERSION 2.4.0 )

IF( COMMAND CMAKE_POLICY )
    CMAKE_POLICY(SET CMP0003 NEW)
ENDIF( COMMAND CMAKE_POLICY )

#if you don't want the full compiler output, remove the following line
SET( CMAKE_VERBOSE_MAKEFILE OFF )
#So that cmake can find local cmake files
SET( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" )
FIND_PACKAGE( KDE3 REQUIRED )
#list all source files here
ADD_SUBDIRECTORY( src )
ADD_SUBDIRECTORY( doc )
