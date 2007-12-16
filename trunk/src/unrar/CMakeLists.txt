ADD_DEFINITIONS( -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -fexceptions )
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR} )
SET( SRC filestr.cpp
        scantree.cpp
        dll.cpp
        rar.cpp
        strlist.cpp
        strfn.cpp
        pathfn.cpp
        int64.cpp
        savepos.cpp
        global.cpp
        file.cpp
        filefn.cpp
        filcreat.cpp
        archive.cpp
        arcread.cpp
        unicode.cpp
        system.cpp
        isnt.cpp
        crypt.cpp
        crc.cpp
        rawread.cpp
        encname.cpp
        resource.cpp
        match.cpp
        timefn.cpp
        rdwrfn.cpp
        consio.cpp
        options.cpp
        ulinks.cpp
        errhnd.cpp
        rarvm.cpp
        rijndael.cpp
        getbits.cpp
        sha1.cpp
        extinfo.cpp
        extract.cpp
        volume.cpp
        list.cpp
        find.cpp
        unpack.cpp
        cmddata.cpp )
ADD_LIBRARY( unrar SHARED ${SRC} )
