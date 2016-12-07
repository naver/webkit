if (WIN32)
    include(PlatformWin.cmake)

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB")

    list(APPEND WebKitTestRunner_LIBRARIES WebKit ${CAIRO_LIBRARIES})
    list(REMOVE_ITEM WebKitTestRunner_LIBRARIES WebKit2)
endif ()
