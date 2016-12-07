# Copied from WebKit/PlatformWin.cmake and then modified, in case we need WebKitGUID.lib on Windows
if (WIN32)
    # Build the COM interface:
    macro(GENERATE_INTERFACE _infile _defines _depends)
        get_filename_component(_filewe ${WEBKIT_DIR}/${_infile} NAME_WE)
        add_custom_command(
            OUTPUT  ${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces/${_filewe}.h
            MAIN_DEPENDENCY ${WEBKIT_DIR}/${_infile}
            DEPENDS ${_depends}
            COMMAND midl.exe /I "${WEBKIT_DIR}/win/Interfaces" /I "${WEBKIT_DIR}/win/Interfaces/Accessible2" /I "${DERIVED_SOURCES_WEBKIT_DIR}/include" /I "${WEBKIT_DIR}/win" /WX /char signed /env win32 /tlb "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${_filewe}.tlb" /out "${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces" /h "${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces/${_filewe}.h" /iid "${_filewe}_i.c" ${_defines} "${WEBKIT_DIR}/${_infile}"
            VERBATIM)
        set_source_files_properties(${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces/${_filewe}.h PROPERTIES GENERATED TRUE)
        set_source_files_properties(${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces/${_filewe}_i.c PROPERTIES GENERATED TRUE)
    endmacro()

    set(MIDL_DEFINES /D\ \"__PRODUCTION__=01\")

    set(WEBKIT_IDL_DEPENDENCIES
        win/Interfaces/AccessibleComparable.idl
        win/Interfaces/DOMCSS.idl
        win/Interfaces/DOMCore.idl
        win/Interfaces/DOMEvents.idl
        win/Interfaces/DOMExtensions.idl
        win/Interfaces/DOMHTML.idl
        win/Interfaces/DOMPrivate.idl
        win/Interfaces/DOMRange.idl
        win/Interfaces/DOMWindow.idl
        win/Interfaces/IGEN_DOMObject.idl
        win/Interfaces/ITestRunnerWebView.idl
        win/Interfaces/IWebArchive.idl
        win/Interfaces/IWebBackForwardList.idl
        win/Interfaces/IWebBackForwardListPrivate.idl
        win/Interfaces/IWebCache.idl
        win/Interfaces/IWebCoreStatistics.idl
        win/Interfaces/IWebDataSource.idl
        win/Interfaces/IWebDatabaseManager.idl
        win/Interfaces/IWebDesktopNotificationsDelegate.idl
        win/Interfaces/IWebDocument.idl
        win/Interfaces/IWebDownload.idl
        win/Interfaces/IWebEditingDelegate.idl
        win/Interfaces/IWebEmbeddedView.idl
        win/Interfaces/IWebError.idl
        win/Interfaces/IWebErrorPrivate.idl
        win/Interfaces/IWebFormDelegate.idl
        win/Interfaces/IWebFrame.idl
        win/Interfaces/IWebFrameLoadDelegate.idl
        win/Interfaces/IWebFrameLoadDelegatePrivate.idl
        win/Interfaces/IWebFrameLoadDelegatePrivate2.idl
        win/Interfaces/IWebFramePrivate.idl
        win/Interfaces/IWebFrameView.idl
        win/Interfaces/IWebGeolocationPolicyListener.idl
        win/Interfaces/IWebGeolocationPosition.idl
        win/Interfaces/IWebGeolocationProvider.idl
        win/Interfaces/IWebHTMLRepresentation.idl
        win/Interfaces/IWebHTTPURLResponse.idl
        win/Interfaces/IWebHistory.idl
        win/Interfaces/IWebHistoryDelegate.idl
        win/Interfaces/IWebHistoryItem.idl
        win/Interfaces/IWebHistoryItemPrivate.idl
        win/Interfaces/IWebHistoryPrivate.idl
        win/Interfaces/IWebIconDatabase.idl
        win/Interfaces/IWebInspector.idl
        win/Interfaces/IWebInspectorPrivate.idl
        win/Interfaces/IWebJavaScriptCollector.idl
        win/Interfaces/IWebKitStatistics.idl
        win/Interfaces/IWebMutableURLRequest.idl
        win/Interfaces/IWebMutableURLRequestPrivate.idl
        win/Interfaces/IWebNavigationData.idl
        win/Interfaces/IWebNotification.idl
        win/Interfaces/IWebNotificationCenter.idl
        win/Interfaces/IWebNotificationObserver.idl
        win/Interfaces/IWebPolicyDelegate.idl
        win/Interfaces/IWebPolicyDelegatePrivate.idl
        win/Interfaces/IWebPreferences.idl
        win/Interfaces/IWebPreferencesPrivate.idl
        win/Interfaces/IWebResource.idl
        win/Interfaces/IWebResourceLoadDelegate.idl
        win/Interfaces/IWebResourceLoadDelegatePrivate.idl
        win/Interfaces/IWebResourceLoadDelegatePrivate2.idl
        win/Interfaces/IWebScriptObject.idl
        win/Interfaces/IWebScriptWorld.idl
        win/Interfaces/IWebSecurityOrigin.idl
        win/Interfaces/IWebSerializedJSValue.idl
        win/Interfaces/IWebSerializedJSValuePrivate.idl
        win/Interfaces/IWebTextRenderer.idl
        win/Interfaces/IWebUIDelegate.idl
        win/Interfaces/IWebUIDelegate2.idl
        win/Interfaces/IWebUIDelegatePrivate.idl
        win/Interfaces/IWebURLAuthenticationChallenge.idl
        win/Interfaces/IWebURLRequest.idl
        win/Interfaces/IWebURLResponse.idl
        win/Interfaces/IWebURLResponsePrivate.idl
        win/Interfaces/IWebUndoManager.idl
        win/Interfaces/IWebUndoTarget.idl
        win/Interfaces/IWebUserContentURLPattern.idl
        win/Interfaces/IWebView.idl
        win/Interfaces/IWebViewPrivate.idl
        win/Interfaces/IWebWorkersPrivate.idl
        win/Interfaces/JavaScriptCoreAPITypes.idl
        win/Interfaces/WebKit.idl
        win/Interfaces/WebScrollbarTypes.idl

        win/Interfaces/Accessible2/Accessible2.idl
        win/Interfaces/Accessible2/Accessible2_2.idl
        win/Interfaces/Accessible2/AccessibleApplication.idl
        win/Interfaces/Accessible2/AccessibleEditableText.idl
        win/Interfaces/Accessible2/AccessibleRelation.idl
        win/Interfaces/Accessible2/AccessibleStates.idl
        win/Interfaces/Accessible2/AccessibleText.idl
        win/Interfaces/Accessible2/AccessibleText2.idl
        win/Interfaces/Accessible2/IA2CommonTypes.idl
        "${DERIVED_SOURCES_WEBKIT_DIR}/include/autoversion.h"
    )

    macro(PREPEND_WEBKIT_DIR _output_files _input_files)
        set(_tmp "")
        foreach (_file ${_input_files})
            get_filename_component(_absolute ${_file} ABSOLUTE)
            string(REGEX MATCH "^${CMAKE_CURRENT_SOURCE_DIR}/" _match "${_absolute}")
            if ("${_match}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}/")
                list(APPEND _tmp ${WEBKIT_DIR}/${_file})
            else ()
                list(APPEND _tmp ${_file})
            endif ()
        endforeach ()
        set(${_output_files} "${_tmp}")
        unset(_tmp)
    endmacro()

    PREPEND_WEBKIT_DIR(WEBKIT_IDL_DEPENDENCIES "${WEBKIT_IDL_DEPENDENCIES}")

    add_custom_command(
        OUTPUT ${DERIVED_SOURCES_WEBKIT_DIR}/include/autoversion.h
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMAND ${PERL_EXECUTABLE} ${WEBKIT_LIBRARIES_WIN_DIR}/tools/scripts/auto-version.pl ${DERIVED_SOURCES_WEBKIT_DIR}
        VERBATIM)

    GENERATE_INTERFACE(win/Interfaces/WebKit.idl ${MIDL_DEFINES} "${WEBKIT_IDL_DEPENDENCIES}")
    GENERATE_INTERFACE(win/Interfaces/Accessible2/AccessibleApplication.idl ${MIDL_DEFINES} "${WEBKIT_IDL_DEPENDENCIES}")
    GENERATE_INTERFACE(win/Interfaces/Accessible2/Accessible2.idl ${MIDL_DEFINES} "${WEBKIT_IDL_DEPENDENCIES}")
    GENERATE_INTERFACE(win/Interfaces/Accessible2/Accessible2_2.idl ${MIDL_DEFINES} "${WEBKIT_IDL_DEPENDENCIES}")
    GENERATE_INTERFACE(win/Interfaces/Accessible2/AccessibleRelation.idl ${MIDL_DEFINES} "${WEBKIT_IDL_DEPENDENCIES}")
    GENERATE_INTERFACE(win/Interfaces/Accessible2/AccessibleStates.idl ${MIDL_DEFINES} "${WEBKIT_IDL_DEPENDENCIES}")
    GENERATE_INTERFACE(win/Interfaces/Accessible2/IA2CommonTypes.idl ${MIDL_DEFINES} "${WEBKIT_IDL_DEPENDENCIES}")
    GENERATE_INTERFACE(win/Interfaces/Accessible2/AccessibleEditableText.idl ${MIDL_DEFINES} "${WEBKIT_IDL_DEPENDENCIES}")
    GENERATE_INTERFACE(win/Interfaces/Accessible2/AccessibleText.idl ${MIDL_DEFINES} "${WEBKIT_IDL_DEPENDENCIES}")
    GENERATE_INTERFACE(win/Interfaces/Accessible2/AccessibleText2.idl ${MIDL_DEFINES} "${WEBKIT_IDL_DEPENDENCIES}")

    add_library(WebKitGUID STATIC
        "${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces/WebKit.h"
        "${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces/AccessibleApplication.h"
        "${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces/Accessible2.h"
        "${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces/Accessible2_2.h"
        "${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces/AccessibleRelation.h"
        "${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces/AccessibleStates.h"
        "${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces/IA2CommonTypes.h"
        "${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces/AccessibleEditableText.h"
        "${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces/AccessibleText.h"
        "${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces/AccessibleText2.h"
        "${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces/WebKit_i.c"
        "${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces/AccessibleApplication_i.c"
        "${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces/Accessible2_i.c"
        "${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces/Accessible2_2_i.c"
        "${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces/AccessibleRelation_i.c"
        "${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces/AccessibleEditableText_i.c"
        "${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces/AccessibleText_i.c"
        "${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces/AccessibleText2_i.c"
    )
    set_target_properties(WebKitGUID PROPERTIES OUTPUT_NAME WebKitGUID${DEBUG_SUFFIX})
    set_target_properties(WebKitGUID PROPERTIES FOLDER "WebKit")

    # Make sure incremental linking is turned off, as it creates unacceptably long link times.
    string(REPLACE "INCREMENTAL:YES" "INCREMENTAL:NO" replace_CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS})
    set(CMAKE_SHARED_LINKER_FLAGS "${replace_CMAKE_SHARED_LINKER_FLAGS} /INCREMENTAL:NO")
    string(REPLACE "INCREMENTAL:YES" "INCREMENTAL:NO" replace_CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS})
    set(CMAKE_EXE_LINKER_FLAGS "${replace_CMAKE_EXE_LINKER_FLAGS} /INCREMENTAL:NO")

    string(REPLACE "INCREMENTAL:YES" "INCREMENTAL:NO" replace_CMAKE_SHARED_LINKER_FLAGS_DEBUG ${CMAKE_SHARED_LINKER_FLAGS_DEBUG})
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${replace_CMAKE_SHARED_LINKER_FLAGS_DEBUG} /INCREMENTAL:NO")
    string(REPLACE "INCREMENTAL:YES" "INCREMENTAL:NO" replace_CMAKE_EXE_LINKER_FLAGS_DEBUG ${CMAKE_EXE_LINKER_FLAGS_DEBUG})
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${replace_CMAKE_EXE_LINKER_FLAGS_DEBUG} /INCREMENTAL:NO")

    string(REPLACE "INCREMENTAL:YES" "INCREMENTAL:NO" replace_CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO ${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO})
    set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "${replace_CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO} /INCREMENTAL:NO")
    string(REPLACE "INCREMENTAL:YES" "INCREMENTAL:NO" replace_CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO ${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO})
    set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${replace_CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} /INCREMENTAL:NO")

    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

    list(APPEND WebKit_LIBRARIES WebKitGUID${DEBUG_SUFFIX})

    # If this directory isn't created before midl runs and attempts to output WebKit.tlb,
    # It fails with an unusual error - midl failed - failed to save all changes
    file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    file(MAKE_DIRECTORY ${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces)

    set(WebKitGUID_PRE_BUILD_COMMAND "${CMAKE_BINARY_DIR}/DerivedSources/WebKit/preBuild.cmd")
    file(WRITE "${WebKitGUID_PRE_BUILD_COMMAND}" "@xcopy /y /d /f \"${CMAKE_CURRENT_SOURCE_DIR}/win/WebKitCOMAPI.h\" \"${DERIVED_SOURCES_DIR}/ForwardingHeaders/WebKit\" >nul 2>nul\n")
    file(MAKE_DIRECTORY ${DERIVED_SOURCES_DIR}/ForwardingHeaders/WebKit)
    add_custom_command(TARGET WebKitGUID PRE_BUILD COMMAND ${WebKitGUID_PRE_BUILD_COMMAND} VERBATIM)

    set(WebKitGUID_POST_BUILD_COMMAND "${CMAKE_BINARY_DIR}/DerivedSources/WebKit/postBuild.cmd")
    file(WRITE "${WebKitGUID_POST_BUILD_COMMAND}" "@xcopy /y /d /f \"${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces/*.h\" \"${DERIVED_SOURCES_DIR}/ForwardingHeaders/WebKit\" >nul 2>nul")
    add_custom_command(TARGET WebKitGUID POST_BUILD COMMAND ${WebKitGUID_POST_BUILD_COMMAND} VERBATIM)

    # End of copied contents

    file(MAKE_DIRECTORY ${DERIVED_SOURCES_DIR}/ForwardingHeaders/WebCore)
    file(APPEND "${WebKitGUID_POST_BUILD_COMMAND}" "\n@xcopy /y /d /f \"${WEBCORE_DIR}/platform/win/COMPtr.h\" \"${DERIVED_SOURCES_DIR}/ForwardingHeaders/WebCore\" >nul 2>nul")

    add_definitions(-DWEBKIT_EXPORTS)

    list(APPEND WebKit_INCLUDE_DIRECTORIES
        "${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces"
        "${WEBCORE_DIR}/platform"
        "${WTF_DIR}"
    )

    list(APPEND WebKit_LIBRARIES
        PRIVATE Rpcrt4
    )

    set(WebKit_win_SOURCES
        win/RuntimeLink.cpp
        win/WebCache.cpp
        win/WebCoreStatistics.cpp
        win/WebDataSource.cpp
        win/WebFrame.cpp
        win/WebHistory.cpp
        win/WebKitCOMAPI.cpp
        win/WebKitClassFactory.cpp
        win/WebKitDLLMain.cpp
        win/WebKitMessageLoop.cpp
        win/WebMutableURLRequest.cpp
        win/WebPreferences.cpp
        win/WebView.cpp
    )

    list(APPEND WebKit_SOURCES ${WebKit_win_SOURCES})

    source_group(win FILES ${WebKit_win_SOURCES})
endif ()
