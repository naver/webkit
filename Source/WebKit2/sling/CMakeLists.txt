if (NOT ANDROID)
    set(WebKit_INCLUDE_DIRECTORIES
        "${DERIVED_SOURCES_DIR}/WebKit/LibraryHeaders"
        "${DERIVED_SOURCES_DIR}/WebKit/LibraryHeaders/webkit"
        "${DERIVED_SOURCES_DIR}/WebKit/LibraryHeaders/private"
        "${DERIVED_SOURCES_DIR}/WebKit/LibraryHeaders/private/webkit"
        "${WEBKIT2_DIR}/sling"
        "${WEBKIT_LIBRARIES_DIR}/include/os"
        "${ANGLE_INCLUDE_DIR}"
        "${ANGLE_INCLUDE_DIR}/include"
        "${ANGLE_INCLUDE_DIR}/include/EGL"
        "${ANGLE_INCLUDE_DIR}/include/KHR"
        "${CMAKE_BINARY_DIR}"
    )

    if (WIN32)
        list(APPEND WebKit_INCLUDE_DIRECTORIES
            "${WEBCORE_DIR}/platform/win"
        )
    endif ()

    set(WebKit_SOURCES
        WebKitPrefix.h
    )

    set(WebKit_PRIVATE_SOURCES
        WebKitMain.cpp
    )

    set(WebKit_LIBRARIES
        PRIVATE WebKit2
        PRIVATE ${WebKit2_LIBRARIES}
        PUBLIC  ${WTF_SYSTEM_LIBRARIES}
    )

    if (DEVELOPER_MODE AND WIN32)
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /DEF:${TOOLS_DIR}/WebKitTestRunner/win/WebKit2.def")
    endif ()

    PROCESS_FRAMEWORK_LIBRARY_SOURCES(WebKit_SOURCES PUBLIC)
    PROCESS_FRAMEWORK_LIBRARY_SOURCES(WebKit_PRIVATE_SOURCES PRIVATE)
    PROCESS_FRAMEWORK_LIBRARY_SOURCES(WebKit_PRIVATE_SOURCES INTERNAL)

    WEBKIT_WRAP_SOURCELIST(${WebKit_SOURCES} ${WebKit_PRIVATE_SOURCES})

    if (WIN32)
        include(WebKitGUID.cmake)
    endif ()

    add_definitions(-DWEBCORE_EXPORT=WEBKIT_EXPORT -DWTF_EXPORT_PRIVATE=COMPILER_IMPORT -DNATIVE_EXPORT=NO_EXPORT)

    include_directories(${WebKit_INCLUDE_DIRECTORIES})
    add_library(WebKit SHARED ${WebKit_SOURCES} ${WebKit_PRIVATE_SOURCES})

    add_dependencies(WebKit WebKit2)
    add_prefix_header(WebKit "WebKitPrefix.h")
    target_link_libraries(WebKit ${WebKit_LIBRARIES})
    set_target_properties(WebKit PROPERTIES FOLDER "WebKit")

    if (WebKit_OUTPUT_NAME)
        set_target_properties(WebKit PROPERTIES OUTPUT_NAME ${WebKit_OUTPUT_NAME})
    endif ()
else ()
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/android/libs/${ANDROID_NDK_ABI_NAME})

    PROCESS_FRAMEWORK_LIBRARY_SOURCES(WebKit_SOURCES PUBLIC)
    PROCESS_FRAMEWORK_LIBRARY_SOURCES(WebKit_PRIVATE_SOURCES PRIVATE)
    PROCESS_FRAMEWORK_LIBRARY_SOURCES(WebKit_PRIVATE_SOURCES INTERNAL)

    add_custom_command(
        OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/android/bin/classes.jar ${CMAKE_BINARY_DIR}/libs/WebKit.jar
        MAIN_DEPENDENCY android/AndroidManifest.xml
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/android/AndroidManifest.xml ${CMAKE_CURRENT_BINARY_DIR}/android
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/android/project.properties ${CMAKE_CURRENT_BINARY_DIR}/android
        COMMAND ${CMAKE_COMMAND} -E copy ${WEBKIT_LIBRARIES_DIR}/bin/onig.jar ${CMAKE_CURRENT_BINARY_DIR}/android/libs
        COMMAND ${CMAKE_COMMAND} -E copy ${WEBKIT_LIBRARIES_DIR}/bin/view.jar ${CMAKE_CURRENT_BINARY_DIR}/android/libs
        COMMAND android update lib-project --path .
        COMMAND ant release
        COMMAND mkdir -p ${WEBKIT_LIBRARIES_DIR}/bin
        COMMAND cp -u ${CMAKE_CURRENT_BINARY_DIR}/android/bin/classes.jar ${CMAKE_BINARY_DIR}/libs/WebKit.jar
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/android
        VERBATIM)

    add_custom_target(WebKit ALL SOURCES ${WebKit_SOURCES} ${WebKit_PRIVATE_SOURCES} android/AndroidManifest.xml)

    add_dependencies(WebKit WebKit2)
endif ()