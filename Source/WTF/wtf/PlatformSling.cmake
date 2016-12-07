list(APPEND WTF_SOURCES
    UniStdExtras.cpp

    sling/DispatchQueue.cpp
    sling/RunLoopSling.cpp
    sling/ThreadLoop.cpp
    sling/ThreadLoopBackend.cpp
    sling/WTFMainThread.cpp
    sling/WorkQueueSling.cpp

    text/sling/TextBreakIteratorInternalICU.cpp
)

if (WIN32)
    list(APPEND WTF_SOURCES
        PlatformUserPreferredLanguagesWin.cpp
    )
else ()
    list(APPEND WTF_SOURCES
        PlatformUserPreferredLanguagesUnix.cpp
    )
endif ()

set(WTF_LIBRARIES
    PUBLIC ${WTF_LIBRARIES}
)

list(APPEND WTF_LIBRARIES
    PRIVATE ${ONIG_LIBRARY}
    PRIVATE ${OS_LIBRARY}
    PRIVATE ${PLATFORM_LIBRARIES}
    PUBLIC  ${PTHREAD_LIBRARIES}
    PRIVATE ${SAFEINT_LIBRARIES}
    PRIVATE ${ZLIB_LIBRARIES}

    PRIVATE ${WTF_SYSTEM_LIBRARIES}
)

list(APPEND WTF_INCLUDE_DIRECTORIES
    "${WTF_DIR}/wtf/sling"
    "${DERIVED_SOURCES_DIR}/WTF"
    "${DERIVED_SOURCES_DIR}/NativeInterfaces/WTF"
)

list(APPEND WTF_HEADERS
    sling/DispatchQueue.h
    sling/DispatchQueueWorkItem.h
    sling/ThreadLoop.h
)

set(WTF_FRAMEWORK_SOURCES
    sling/WTFMainThread.java
    sling/ThreadLoopBackend.java
)

GENERATE_WEBKIT_NATIVE_INTERFACE_SOURCES(WTF_SOURCES "${WTF_FRAMEWORK_SOURCES}" INTERNAL)

if (MSVC)
    set(WTF_PRE_BUILD_COMMAND "${CMAKE_BINARY_DIR}/DerivedSources/WTF/preBuild.cmd")
    file(WRITE "${WTF_PRE_BUILD_COMMAND}" "@xcopy /y /s /d /f \"${CMAKE_SOURCE_DIR}/WebKitLibraries/win/tools/*.*\" \"${WEBKIT_LIBRARIES_DIR}/tools/\" >nul 2>nul\n")
    file(MAKE_DIRECTORY ${WEBKIT_LIBRARIES_DIR}/tools)
endif ()
