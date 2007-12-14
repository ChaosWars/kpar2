PROJECT(kpar2)

#if you don't want the full compiler output, remove the following line
SET(CMAKE_VERBOSE_MAKEFILE OFF)

#So that cmake can find local cmake files
SET( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" )

#Find KDE
FIND_PACKAGE( KDE3 REQUIRED )
SET( QT_MT_REQUIRED TRUE )

#Include directories
INCLUDE_DIRECTORIES( ${KDE3_INCLUDE_DIRS}
                     ${CMAKE_CURRENT_BINARY_DIR}
                     ${CMAKE_CURRENT_SOURCE_DIR}

#list all source files here
ADD_SUBDIRECTORY( src )
ADD_SUBDIRECTORY( docs )
