FIND_PATH( LIBSIGC++_INCLUDE_DIR sigc++/sigc++.h /usr/include/sigc++-2.0/ /usr/local/include/sigc++-2.0 )
FIND_PATH( LIBSIGC++_LIB_INCLUDE_DIR sigc++config.h /usr/lib/sigc++-2.0/include /usr/local/lib/sigc++-2.0/include )
FIND_LIBRARY( LIBSIGC++_LIBRARY NAMES sigc-2.0 PATHS /usr/lib /usr/local/lib )
SET( LIBSIGC++_INCLUDE_DIRS ${LIBSIGC++_INCLUDE_DIR} ${LIBSIGC++_LIB_INCLUDE_DIR} )

IF( LIBSIGC++_INCLUDE_DIRS AND LIBSIGC++_LIBRARY )
   SET( LIBSIGC++_FOUND TRUE )
ENDIF( LIBSIGC++_INCLUDE_DIRS AND LIBSIGC++_LIBRARY )


IF( LIBSIGC++_FOUND )
   IF( NOT libsigc++_FIND_QUIETLY )
      MESSAGE( STATUS "Found libsigc++: ${LIBSIGC++_LIBRARY}" )
   ENDIF( NOT libsigc++_FIND_QUIETLY )
ELSE( LIBSIGC++_FOUND )
   IF( libsigc++_FIND_REQUIRED )
      MESSAGE( FATAL_ERROR "Could not find libsigc++" )
   ENDIF( libsigc++_FIND_REQUIRED )
ENDIF( LIBSIGC++_FOUND )
