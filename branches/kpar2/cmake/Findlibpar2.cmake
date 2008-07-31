FIND_PATH( LIBPAR2_INCLUDE_DIR libpar2/libpar2.h /usr/include/ /usr/local/include/ )
FIND_PATH( LIBPAR2_LIB_INCLUDE_DIR config.h /usr/lib/libpar2/include /usr/lib64/libpar2/include /usr/local/lib/libpar2/include /usr/lib64/libpar2/include )
FIND_LIBRARY( LIBPAR2_LIBRARY NAMES par2 PATHS /usr/lib /usr/lib64 /usr/local/lib /usr/local/lib64 )
SET( LIBPAR2_INCLUDE_DIRS ${LIBPAR2_INCLUDE_DIR} ${LIBPAR2_LIB_INCLUDE_DIR} )

IF( LIBPAR2_INCLUDE_DIRS AND LIBPAR2_LIBRARY )
   SET( LIBPAR2_FOUND TRUE )
ENDIF( LIBPAR2_INCLUDE_DIRS AND LIBPAR2_LIBRARY )


IF( LIBPAR2_FOUND )
   IF( NOT libpar2_FIND_QUIETLY )
      MESSAGE( STATUS "Found libpar2: ${LIBPAR2_LIBRARY}" )
   ENDIF( NOT libpar2_FIND_QUIETLY )
ELSE( LIBPAR2_FOUND )
   IF( libpar2_FIND_REQUIRED )
      MESSAGE( FATAL_ERROR "Could not find libpar2" )
   ENDIF( libpar2_FIND_REQUIRED )
ENDIF( LIBPAR2_FOUND )
