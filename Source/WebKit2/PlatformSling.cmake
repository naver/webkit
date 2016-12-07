set(WebKit2_LIBRARIES
    WTF
    JavaScriptCore
    WebCore
    WebCoreDerivedSources

    ${MEDIA_LIBRARY}
    ${OPENGL_LIBRARY}
    ${OS_LIBRARY}
    ${UTIL_LIBRARY}
    ${VIEW_LIBRARY}
    ${ONIG_LIBRARY}

    ${ANGLE_LIBRARIES}
    ${CAIRO_LIBRARIES}
    ${CURL_LIBRARIES}
    ${ICU_LIBRARIES}
    ${IMAGE_LIBRARIES}
    ${LIBXML_LIBRARIES}
    ${PLATFORM_LIBRARIES}
    ${PTHREAD_LIBRARIES}
    ${SAFEINT_LIBRARIES}
    ${SQLITE_LIBRARIES}
    ${ZLIB_LIBRARIES}

    ${WEBKIT_SYSTEM_LIBRARIES}
)

set(WebKit2_USE_PREFIX_HEADER ON)

list(APPEND WebKit2_SOURCES
    DatabaseProcess/sling/DatabaseProcessMainSling.cpp

    NetworkProcess/sling/NetworkProcessMainSling.cpp

    Platform/IPC/unix/AttachmentUnix.cpp
    Platform/IPC/unix/ConnectionUnix.cpp

    Platform/sling/LoggingSling.cpp
    Platform/sling/ModuleSling.cpp
    Platform/sling/SharedMemorySling.cpp

    Shared/API/c/cairo/WKImageCairo.cpp

    Shared/API/sling/SWKContextMenuItemNatives.cpp
    Shared/API/sling/SWKDataNatives.cpp
    Shared/API/sling/SWKErrorNatives.cpp
    Shared/API/sling/SWKSecurityOriginNatives.cpp
    Shared/API/sling/SWKURLNatives.cpp
    Shared/API/sling/SWKURLRequestNatives.cpp
    Shared/API/sling/SWKURLResponseNatives.cpp

    Shared/CoordinatedGraphics/CoordinatedBackingStore.cpp
    Shared/CoordinatedGraphics/CoordinatedGraphicsArgumentCoders.cpp
    Shared/CoordinatedGraphics/CoordinatedGraphicsScene.cpp
    Shared/CoordinatedGraphics/WebCoordinatedSurface.cpp

    Shared/cairo/ShareableBitmapCairo.cpp

    Shared/sling/CompletionHandlerNatives.cpp
    Shared/sling/NativeObjectCast.cpp
    Shared/sling/NativeWebEvent.cpp
    Shared/sling/PasteboardTypes.cpp
    Shared/sling/ProcessExecutablePathSling.cpp
    Shared/sling/ValueCallbackNatives.cpp
    Shared/sling/WebBitmapNatives.cpp
    Shared/sling/WebContextMenuNatives.cpp
    Shared/sling/WebEventEnumerationsNatives.cpp
    Shared/sling/WebMenuItemNatives.cpp
    Shared/sling/WebMenuNatives.cpp
    Shared/sling/WebPrintInfoNatives.cpp

    Shared/unix/ChildProcessMain.cpp

    UIProcess/BackingStore.cpp
    UIProcess/DefaultUndoController.cpp
    UIProcess/LegacySessionStateCodingNone.cpp
    UIProcess/WebResourceLoadStatisticsStore.cpp

    UIProcess/API/APIPageConfiguration.cpp

    UIProcess/API/C/sling/WKView.cpp

    UIProcess/API/sling/APIWebsiteDataStoreSling.cpp
    UIProcess/API/sling/SWKActivatedElementInfoNatives.cpp
    UIProcess/API/sling/SWKApplicationCacheManagerNatives.cpp
    UIProcess/API/sling/SWKAuthenticationChallengeNatives.cpp
    UIProcess/API/sling/SWKAuthenticationDecisionListenerNatives.cpp
    UIProcess/API/sling/SWKBackForwardListItemNatives.cpp
    UIProcess/API/sling/SWKBackForwardListNatives.cpp
    UIProcess/API/sling/SWKContextMenuDelegateNatives.cpp
    UIProcess/API/sling/SWKCookieManagerNatives.cpp
    UIProcess/API/sling/SWKCredentialNatives.cpp
    UIProcess/API/sling/SWKDownloadDelegateNatives.cpp
    UIProcess/API/sling/SWKDownloadNatives.cpp
    UIProcess/API/sling/SWKFindDelegateNatives.cpp
    UIProcess/API/sling/SWKFormDelegateNatives.cpp
    UIProcess/API/sling/SWKFormInputSessionNatives.cpp
    UIProcess/API/sling/SWKFrameHandleNatives.cpp
    UIProcess/API/sling/SWKFrameInfoNatives.cpp
    UIProcess/API/sling/SWKFramePolicyListenerNatives.cpp
    UIProcess/API/sling/SWKGeolocationManagerNatives.cpp
    UIProcess/API/sling/SWKGeolocationPermissionRequestNatives.cpp
    UIProcess/API/sling/SWKGeolocationPositionNatives.cpp
    UIProcess/API/sling/SWKGeolocationProviderNatives.cpp
    UIProcess/API/sling/SWKIconDatabaseDelegateNatives.cpp
    UIProcess/API/sling/SWKIconDatabaseNatives.cpp
    UIProcess/API/sling/SWKKeyValueStorageManagerNatives.cpp
    UIProcess/API/sling/SWKLoaderDelegateNatives.cpp
    UIProcess/API/sling/SWKNavigationActionNatives.cpp
    UIProcess/API/sling/SWKNavigationDataNatives.cpp
    UIProcess/API/sling/SWKNavigationNatives.cpp
    UIProcess/API/sling/SWKNavigationResponseNatives.cpp
    UIProcess/API/sling/SWKNotificationNatives.cpp
    UIProcess/API/sling/SWKNotificationPermissionRequestNatives.cpp
    UIProcess/API/sling/SWKNotificationProviderNatives.cpp
    UIProcess/API/sling/SWKOpenPanelResultListenerNatives.cpp
    UIProcess/API/sling/SWKPolicyDelegateNatives.cpp
    UIProcess/API/sling/SWKPreferencesNatives.cpp
    UIProcess/API/sling/SWKProcessPoolConfigurationNatives.cpp
    UIProcess/API/sling/SWKProcessPoolNatives.cpp
    UIProcess/API/sling/SWKProtectionSpaceNatives.cpp
    UIProcess/API/sling/SWKResourceCacheManagerNatives.cpp
    UIProcess/API/sling/SWKScriptMessageHandlerNatives.cpp
    UIProcess/API/sling/SWKScriptMessageNatives.cpp
    UIProcess/API/sling/SWKSessionStateNatives.cpp
    UIProcess/API/sling/SWKUIDelegateNatives.cpp
    UIProcess/API/sling/SWKUserContentControllerNatives.cpp
    UIProcess/API/sling/SWKUserScriptNatives.cpp
    UIProcess/API/sling/SWKUserStyleSheetNatives.cpp
    UIProcess/API/sling/SWKVibrationProviderNatives.cpp
    UIProcess/API/sling/SWKViewNatives.cpp
    UIProcess/API/sling/SWKVisitedLinkStoreNatives.cpp
    UIProcess/API/sling/SWKWebContentConfigurationNatives.cpp
    UIProcess/API/sling/SWKWebContentNatives.cpp
    UIProcess/API/sling/SWKWebHitTestResultNatives.cpp
    UIProcess/API/sling/SWKWindowFeaturesNatives.cpp

    UIProcess/CoordinatedGraphics/CoordinatedDrawingAreaProxy.cpp
    UIProcess/CoordinatedGraphics/CoordinatedLayerTreeHostProxy.cpp
    UIProcess/CoordinatedGraphics/PageViewportController.cpp
    UIProcess/CoordinatedGraphics/WebPageProxyCoordinatedGraphics.cpp

    UIProcess/Databases/sling/DatabaseProcessProxySling.cpp

    UIProcess/InspectorServer/sling/WebInspectorServerSling.cpp

    UIProcess/Launcher/sling/ChildProcessLauncherNatives.cpp
    UIProcess/Launcher/sling/ProcessLauncherSling.cpp
    UIProcess/Launcher/sling/ProcessLauncherStrategy.cpp
    UIProcess/Launcher/sling/WebKitServiceRunnerNatives.cpp

    UIProcess/Storage/StorageManager.cpp

    UIProcess/WebsiteData/sling/WebsiteDataStoreSling.cpp

    UIProcess/cairo/BackingStoreCairo.cpp

    UIProcess/sling/CompositionUnderlineNatives.cpp
    UIProcess/sling/ContextMenuClient.cpp
    UIProcess/sling/DownloadClient.cpp
    UIProcess/sling/FindClient.cpp
    UIProcess/sling/FormClient.cpp
    UIProcess/sling/GeolocationManager.cpp
    UIProcess/sling/LoaderClient.cpp
    UIProcess/sling/NotificationManager.cpp
    UIProcess/sling/PageClientSling.cpp
    UIProcess/sling/PageViewportControllerClientSling.cpp
    UIProcess/sling/PolicyClient.cpp
    UIProcess/sling/TextCheckerSling.cpp
    UIProcess/sling/UIClient.cpp
    UIProcess/sling/VibrationProvider.cpp
    UIProcess/sling/ViewController.cpp
    UIProcess/sling/WebContextMenuProxySling.cpp
    UIProcess/sling/WebCookieManagerProxySling.cpp
    UIProcess/sling/WebEditableNatives.cpp
    UIProcess/sling/WebInspectorProxySling.cpp
    UIProcess/sling/WebKitTestRunnerSupportNatives.cpp
    UIProcess/sling/WebPageProxySling.cpp
    UIProcess/sling/WebPasteboardProxySling.cpp
    UIProcess/sling/WebPopupMenuProxySling.cpp
    UIProcess/sling/WebPreferencesSling.cpp
    UIProcess/sling/WebProcessPoolSling.cpp
    UIProcess/sling/WebProcessProxySling.cpp
    UIProcess/sling/WebRendererNatives.cpp
    UIProcess/sling/WebView.cpp

    WebProcess/InjectedBundle/posix/InjectedBundlePOSIX.cpp

    WebProcess/MediaCache/WebMediaKeyStorageManager.cpp

    WebProcess/WebCoreSupport/WebPasteboardOverrides.cpp

    WebProcess/WebCoreSupport/sling/WebContextMenuClientSling.cpp
    WebProcess/WebCoreSupport/sling/WebChromeClientSling.cpp
    WebProcess/WebCoreSupport/sling/WebEditorClientSling.cpp
    WebProcess/WebCoreSupport/sling/WebErrorsSling.cpp
    WebProcess/WebCoreSupport/sling/WebFrameNetworkingContext.cpp
    WebProcess/WebCoreSupport/sling/WebInspectorClientSling.cpp
    WebProcess/WebCoreSupport/sling/WebPopupMenuSling.cpp

    WebProcess/WebPage/AcceleratedDrawingArea.cpp
    WebProcess/WebPage/DrawingAreaImpl.cpp

    WebProcess/WebPage/CoordinatedGraphics/AreaAllocator.cpp
    WebProcess/WebPage/CoordinatedGraphics/CompositingCoordinator.cpp
    WebProcess/WebPage/CoordinatedGraphics/CoordinatedLayerTreeHost.cpp
    WebProcess/WebPage/CoordinatedGraphics/UpdateAtlas.cpp
    WebProcess/WebPage/CoordinatedGraphics/WebPageCoordinatedGraphics.cpp

    WebProcess/WebPage/sling/WebInspectorSling.cpp
    WebProcess/WebPage/sling/WebInspectorUISling.cpp
    WebProcess/WebPage/sling/WebPageSling.cpp

    WebProcess/sling/WebProcessMainSling.cpp
    WebProcess/sling/WebProcessSling.cpp
)

list(REMOVE_ITEM WebKit2_SOURCES
    UIProcess/WebsiteData/unix/WebsiteDataStoreUnix.cpp
)

if (USE_CURL)
    list(APPEND WebKit2_SOURCES
        NetworkProcess/curl/NetworkProcessCurl.cpp
        NetworkProcess/curl/RemoteNetworkingContextCurl.cpp

        Shared/Authentication/curl/AuthenticationManagerCurl.cpp

        Shared/Downloads/curl/DownloadCurl.cpp

        Shared/Network/CustomProtocols/curl/CustomProtocolManagerCurl.cpp
        Shared/Network/CustomProtocols/curl/CustomProtocolManagerImpl.cpp

        Shared/curl/WebCoreArgumentCodersCurl.cpp

        UIProcess/InspectorServer/curl/WebSocketServerCurl.cpp

        UIProcess/Network/CustomProtocols/curl/CustomProtocolManagerProxyCurl.cpp

        UIProcess/Network/curl/NetworkProcessProxyCurl.cpp

        WebProcess/Cookies/curl/WebCookieManagerCurl.cpp
    )
endif ()

if (ANDROID)
    list(APPEND WebKit2_SOURCES
        sling/android/RegisterClass.cpp
        sling/android/WebKitJNIMain.cpp
    )
endif ()

list(APPEND WebKit2_MESSAGES_IN_FILES
    UIProcess/CoordinatedGraphics/CoordinatedLayerTreeHostProxy.messages.in

    WebProcess/WebPage/CoordinatedGraphics/CoordinatedLayerTreeHost.messages.in
)

list(APPEND WebKit2_INCLUDE_DIRECTORIES
    "${WEBCORE_DIR}/page/scrolling/coordinatedgraphics"
    "${WEBCORE_DIR}/platform/sling"
    "${WEBCORE_DIR}/platform/graphics/sling"
    "${WEBCORE_DIR}/platform/graphics/cairo"
    "${WEBCORE_DIR}/platform/graphics/egl"
    "${WEBCORE_DIR}/platform/graphics/opentype"
    "${WEBCORE_DIR}/platform/network/sling"
    "${DERIVED_SOURCES_DIR}/NativeInterfaces/WebKit2"
    "${DERIVED_SOURCES_DIR}/NativeInterfaces/WebCore"
    "${DERIVED_SOURCES_DIR}/NativeInterfaces/WTF"
    "${WEBKIT2_DIR}/Platform/sling"
    "${WEBKIT2_DIR}/Platform/unix"
    "${WEBKIT2_DIR}/Shared/API/c/sling"
    "${WEBKIT2_DIR}/Shared/API/sling"
    "${WEBKIT2_DIR}/Shared/CoordinatedGraphics"
    "${WEBKIT2_DIR}/Shared/sling"
    "${WEBKIT2_DIR}/Shared/unix"
    "${WEBKIT2_DIR}/Shared/Network/CustomProtocols/sling"
    "${WEBKIT2_DIR}/DatabaseProcess/unix"
    "${WEBKIT2_DIR}/UIProcess/sling"
    "${WEBKIT2_DIR}/UIProcess/CoordinatedGraphics"
    "${WEBKIT2_DIR}/UIProcess/API/C/cairo"
    "${WEBKIT2_DIR}/UIProcess/API/C/sling"
    "${WEBKIT2_DIR}/UIProcess/API/sling"
    "${WEBKIT2_DIR}/UIProcess/Launcher/sling"
    "${WEBKIT2_DIR}/UIProcess/Network/CustomProtocols/sling"
    "${WEBKIT2_DIR}/WebProcess/WebCoreSupport/sling"
    "${WEBKIT2_DIR}/WebProcess/WebPage/CoordinatedGraphics"
    "${WEBKIT2_DIR}/WebProcess/sling"
    "${WEBKIT2_DIR}/WebProcess/unix"
    "${WEBKIT2_DIR}/NetworkProcess/unix"
    "${WEBKIT2_DIR}/PluginProcess/unix"
    "${WTF_DIR}/wtf/sling"
    "${WTF_DIR}"
    "${WEBKIT2_DIR}"
    "${CAIRO_INCLUDE_DIR}"
)

# This is needed because of a naming conflict with DiagnosticLoggingClient.h.
# FIXME: Rename one of the DiagnosticLoggingClient headers.
list(REMOVE_ITEM WebKit2_INCLUDE_DIRECTORIES
    "${WEBCORE_DIR}/page"
)
list(APPEND WebKit2_INCLUDE_DIRECTORIES
    "${WEBCORE_DIR}/page"
)

list(REMOVE_ITEM WebKit2_INCLUDE_DIRECTORIES
    "${THIRDPARTY_DIR}/ANGLE"
    "${THIRDPARTY_DIR}/ANGLE/include/KHR"
)
list(APPEND WebKit2_INCLUDE_DIRECTORIES
    "${ANGLE_INCLUDE_DIR}"
    "${ANGLE_INCLUDE_DIR}/include/KHR"
)

if (USE_CURL)
    list(APPEND WebKit2_INCLUDE_DIRECTORIES
        "${WEBCORE_DIR}/platform/network/curl"
        "${WEBKIT2_DIR}/Shared/Network/CustomProtocols/curl"
    )
endif ()

if (USE_FREETYPE)
    list(APPEND WebKit2_INCLUDE_DIRECTORIES
        "${WEBCORE_DIR}/platform/graphics/freetype"
        "${WEBCORE_DIR}/platform/graphics/harfbuzz"
    )
endif ()

if (USE_CAIRO_WINFONT)
    list(APPEND WebKit2_INCLUDE_DIRECTORIES
        "${WEBCORE_DIR}/platform/graphics/win"
    )
endif ()

if (WIN32)
    list(APPEND WebKit2_INCLUDE_DIRECTORIES
        "${WEBCORE_DIR}/platform/win"
        "${ANGLE_INCLUDE_DIR}/include"
        "${ANGLE_INCLUDE_DIR}/include/EGL"
    )
elseif (ANDROID)
    list(APPEND WebCore_INCLUDE_DIRECTORIES
        "${ANDROID_SYS_ROOT}/usr/include/EGL"
    )
endif ()

if (USE_CURL)
    set(WEBCORE_PLATFORM_NETWORK curl)
endif ()

add_definitions(-DWEBKIT_EXPORT=WTF_EXPORT)

add_dependencies(WebCoreDerivedSources JavaScriptCore)

add_custom_target(GenerateForwardingHeadersForWebKit2
    COMMAND ${PERL_EXECUTABLE} ${WEBKIT2_DIR}/Scripts/generate-forwarding-headers.pl --include-path ${WEBKIT2_DIR} --output ${DERIVED_SOURCES_DIR}/ForwardingHeaders --platform sling --platform ${WEBCORE_PLATFORM_NETWORK}
)

set(WEBKIT2_EXTRA_DEPENDENCIES
    GenerateForwardingHeadersForWebKit2
)

set_target_properties(GenerateForwardingHeadersForWebKit2 PROPERTIES FOLDER "WebKit")
add_dependencies(GenerateForwardingHeadersForWebKit2 WebCore)

set(WebKit2_FRAMEWORK_SOURCES
    Shared/API/sling/SWKData.java
    Shared/API/sling/SWKError.java
    Shared/API/sling/SWKSecurityOrigin.java
    Shared/API/sling/SWKURL.java
    Shared/API/sling/SWKURLResponse.java

    Shared/sling/CompletionHandler.java
    Shared/sling/ValueCallback.java
    Shared/sling/WebEventEnumerations.java

    UIProcess/API/sling/SWKAuthenticationChallenge.java
    UIProcess/API/sling/SWKBackForwardList.java
    UIProcess/API/sling/SWKBackForwardListItem.java
    UIProcess/API/sling/SWKFrameInfo.java
    UIProcess/API/sling/SWKFramePolicyListener.java
    UIProcess/API/sling/SWKLoaderDelegate.java
    UIProcess/API/sling/SWKNavigation.java
    UIProcess/API/sling/SWKNavigationAction.java
    UIProcess/API/sling/SWKNavigationResponse.java
    UIProcess/API/sling/SWKPolicyDelegate.java
    UIProcess/API/sling/SWKPreferences.java
    UIProcess/API/sling/SWKProcessPool.java
    UIProcess/API/sling/SWKScriptMessage.java
    UIProcess/API/sling/SWKScriptMessageHandler.java
    UIProcess/API/sling/SWKUIDelegate.java
    UIProcess/API/sling/SWKUserContentController.java
    UIProcess/API/sling/SWKUserScript.java
    UIProcess/API/sling/SWKView.java
    UIProcess/API/sling/SWKWebContent.java
    UIProcess/API/sling/SWKWebContentConfiguration.java
    UIProcess/API/sling/SWKWindowFeatures.java
)

set(WebKit2_FRAMEWORK_PRIVATE_SOURCES
    Shared/API/sling/SWKContextMenuItem.java
    Shared/API/sling/SWKURLRequest.java

    Shared/sling/WebBitmap.java
    Shared/sling/WebContextMenu.java
    Shared/sling/WebMenu.java
    Shared/sling/WebMenuItem.java
    Shared/sling/WebPrintInfo.java

    UIProcess/API/sling/SWKActivatedElementInfo.java
    UIProcess/API/sling/SWKApplicationCacheManager.java
    UIProcess/API/sling/SWKAuthenticationDecisionListener.java
    UIProcess/API/sling/SWKContextMenuDelegate.java
    UIProcess/API/sling/SWKCookieManager.java
    UIProcess/API/sling/SWKCredential.java
    UIProcess/API/sling/SWKDownload.java
    UIProcess/API/sling/SWKDownloadDelegate.java
    UIProcess/API/sling/SWKFindDelegate.java
    UIProcess/API/sling/SWKFormDelegate.java
    UIProcess/API/sling/SWKFormInputSession.java
    UIProcess/API/sling/SWKFrameHandle.java
    UIProcess/API/sling/SWKGeolocationManager.java
    UIProcess/API/sling/SWKGeolocationPermissionRequest.java
    UIProcess/API/sling/SWKGeolocationPosition.java
    UIProcess/API/sling/SWKGeolocationProvider.java
    UIProcess/API/sling/SWKIconDatabase.java
    UIProcess/API/sling/SWKIconDatabaseDelegate.java
    UIProcess/API/sling/SWKKeyValueStorageManager.java
    UIProcess/API/sling/SWKNavigationData.java
    UIProcess/API/sling/SWKNotification.java
    UIProcess/API/sling/SWKNotificationPermissionRequest.java
    UIProcess/API/sling/SWKNotificationProvider.java
    UIProcess/API/sling/SWKOpenPanelResultListener.java
    UIProcess/API/sling/SWKProcessPoolConfiguration.java
    UIProcess/API/sling/SWKProtectionSpace.java
    UIProcess/API/sling/SWKResourceCacheManager.java
    UIProcess/API/sling/SWKSecureCoding.java
    UIProcess/API/sling/SWKSessionState.java
    UIProcess/API/sling/SWKUserStyleSheet.java
    UIProcess/API/sling/SWKVibrationProvider.java
    UIProcess/API/sling/SWKVisitedLinkStore.java
    UIProcess/API/sling/SWKWebHitTestResult.java
    UIProcess/API/sling/SWKWebsiteDataStore.java

    UIProcess/Launcher/sling/ChildProcessLauncher.java
    UIProcess/Launcher/sling/WebKitServiceRunner.java

    UIProcess/sling/CompositionUnderline.java
    UIProcess/sling/WebEditable.java
    UIProcess/sling/WebEditableContext.java
    UIProcess/sling/WebKitTestRunnerSupport.java
    UIProcess/sling/WebRenderer.java
    UIProcess/sling/WebRenderContext.java
    UIProcess/sling/WebViewContext.java

    sling/android/ChildThread.java
    sling/android/IWebKitService.aidl
    sling/android/WebKitResourcesManager.java
    sling/android/WebKitService.java
    sling/android/WebKitServiceNetworkProcess.java
    sling/android/WebKitServiceWebProcess.java
)

GENERATE_WEBKIT_NATIVE_INTERFACE_SOURCES(WebKit2_SOURCES "${WebKit2_FRAMEWORK_SOURCES}" PUBLIC)
GENERATE_WEBKIT_NATIVE_INTERFACE_SOURCES(WebKit2_SOURCES "${WebKit2_FRAMEWORK_PRIVATE_SOURCES}" PRIVATE)

add_subdirectory(sling)
