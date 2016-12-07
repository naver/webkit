add_custom_target(GenerateForwardingHeadersForWebKitTestRunnerWin
    COMMAND ${PERL_EXECUTABLE} ${WEBKIT2_DIR}/Scripts/generate-forwarding-headers.pl --include-path ${WEBKIT_TESTRUNNER_DIR} --output ${DERIVED_SOURCES_WEBKIT2_DIR}/include --platform win --platform curl
)
set(ForwardingHeadersForWebKitTestRunner_NAME GenerateForwardingHeadersForWebKitTestRunnerWin)

list(APPEND WebKitTestRunner_SOURCES
    ${WEBKIT_TESTRUNNER_DIR}/win/EventSenderProxyWin.cpp
    ${WEBKIT_TESTRUNNER_DIR}/win/PlatformWebViewWin.cpp
    ${WEBKIT_TESTRUNNER_DIR}/win/TestControllerWin.cpp
    ${WEBKIT_TESTRUNNER_DIR}/win/main.cpp
)

if (USE_CAIRO)
    list(APPEND WebKitTestRunner_SOURCES
        ${WEBKIT_TESTRUNNER_DIR}/cairo/TestInvocationCairo.cpp
    )
endif ()

if (USE_CG)
    list(APPEND WebKitTestRunner_SOURCES
        ${WEBKIT_TESTRUNNER_DIR}/cg/TestInvocationCG.cpp
    )
endif ()

list(APPEND WebKitTestRunner_INCLUDE_DIRECTORIES
    "${DERIVED_SOURCES_WEBKIT2_DIR}/include"
    "${DERIVED_SOURCES_WEBKIT_DIR}/Interfaces"
    "${WEBKIT2_DIR}/UIProcess/API/C"
)

set(WebKitTestRunner_LIBRARIES
    DbgHelp
    WTF
    JavaScriptCore
    WebCoreTestSupport
    WebKit2
    WebKitGUID
    comctl32
    comsupp
    comsuppw
    shlwapi
)

list(APPEND WebKitTestRunnerInjectedBundle_SOURCES
    ${WEBKIT_TESTRUNNER_INJECTEDBUNDLE_DIR}/win/ActivateFontsWin.cpp
    ${WEBKIT_TESTRUNNER_INJECTEDBUNDLE_DIR}/win/InjectedBundleWin.cpp
    ${WEBKIT_TESTRUNNER_INJECTEDBUNDLE_DIR}/win/TestRunnerWin.cpp
)
