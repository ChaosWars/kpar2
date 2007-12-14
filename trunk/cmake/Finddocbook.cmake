FIND_PROGRAM( KDE3_MEINPROC_EXECUTABLE NAME meinproc PATHS ${KDE3PRFIX}/bin )

IF( KDE3_MEINPROC_EXECUTABLE )
    SET( DOCBOOK_FOUND TRUE )
ELSE( KDE3_MEINPROC_EXECUTABLE )
    MESSAGE( STATUS "Failed to find meinproc" )
ENDIF( KDE3_MEINPROC_EXECUTABLE )

IF( DOCBOOK_FOUND )
   IF( NOT docbook_FIND_QUIETLY )
      MESSAGE( STATUS "Found meinproc: ${KDE3_MEINPROC_EXECUTABLE}" )
   ENDIF( NOT docbook_FIND_QUIETLY )
ELSE( DOCBOOK_FOUND )
   IF( docbook_FIND_REQUIRED )
      MESSAGE( FATAL_ERROR "Could not find meinproc" )
   ENDIF( docbook_FIND_REQUIRED )
ENDIF( DOCBOOK_FOUND )

MACRO( KDE3_GENERATE_DOCBOOK outfiles )
	FOREACH( it ${ARGN} )
		GET_FILENAME_COMPONENT( in ${it} ABSOLUTE )
		SET( outfile  )
		ADD_CUSTOM_COMMAND( OUTPUT ${outfile}
                            COMMAND ${KDE3_MEINPROC_EXECUTABLE}
                            ARGS ${in}
                            DEPENDS ${infile} )
		SET( ${outfiles} "${${outfiles}}" ${outfile} )
	ENDFOREACH( it )
ENDMACRO( KDE3_GENERATE_DOCBOOK )