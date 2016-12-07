include(platform/ImageDecoders.cmake)
include(platform/TextureMapper.cmake)

list(APPEND WebCore_SOURCES
    editing/sling/EditorSling.cpp

    page/PageDebuggable.cpp

    page/sling/EventHandlerSling.cpp
    page/sling/SettingsSling.cpp

    platform/Cursor.cpp
    platform/KillRingNone.cpp
    platform/LocalizedStrings.cpp

    platform/audio/sling/AudioBusSling.cpp
    platform/audio/sling/AudioDestinationSling.cpp
    platform/audio/sling/AudioFileReaderSling.cpp
    platform/audio/sling/WebAudioDestinationNatives.cpp
    platform/audio/sling/WebAudioFileReaderNatives.cpp

    platform/graphics/GLContext.cpp
    platform/graphics/ImageSource.cpp
    platform/graphics/OpenGLShims.cpp
    platform/graphics/PlatformDisplay.cpp
    platform/graphics/WOFFFileFormat.cpp

    platform/graphics/cairo/BackingStoreBackendCairoImpl.cpp
    platform/graphics/cairo/BitmapImageCairo.cpp
    platform/graphics/cairo/CairoUtilities.cpp
    platform/graphics/cairo/FloatRectCairo.cpp
    platform/graphics/cairo/FontCairo.cpp
    platform/graphics/cairo/GradientCairo.cpp
    platform/graphics/cairo/GraphicsContextCairo.cpp
    platform/graphics/cairo/ImageBufferCairo.cpp
    platform/graphics/cairo/ImageCairo.cpp
    platform/graphics/cairo/IntRectCairo.cpp
    platform/graphics/cairo/PathCairo.cpp
    platform/graphics/cairo/PatternCairo.cpp
    platform/graphics/cairo/PlatformContextCairo.cpp
    platform/graphics/cairo/PlatformPathCairo.cpp
    platform/graphics/cairo/RefPtrCairo.cpp
    platform/graphics/cairo/TransformationMatrixCairo.cpp

    platform/graphics/cpu/arm/filters/FELightingNEON.cpp

    platform/graphics/egl/GLContextEGL.cpp
    platform/graphics/egl/GLContextFromCurrentEGL.cpp

    platform/graphics/gpu/Texture.cpp
    platform/graphics/gpu/TilingData.cpp

    platform/graphics/opengl/Extensions3DOpenGL.cpp
    platform/graphics/opengl/Extensions3DOpenGLCommon.cpp
    platform/graphics/opengl/Extensions3DOpenGLES.cpp
    platform/graphics/opengl/GLPlatformContext.cpp
    platform/graphics/opengl/GLPlatformSurface.cpp
    platform/graphics/opengl/GraphicsContext3DOpenGLCommon.cpp
    platform/graphics/opengl/GraphicsContext3DOpenGLES.cpp
    platform/graphics/opengl/TemporaryOpenGLSetting.cpp

    platform/graphics/sling/GraphicsContext3DPrivate.cpp
    platform/graphics/sling/GraphicsContext3DSling.cpp
    platform/graphics/sling/ImageSling.cpp
    platform/graphics/sling/MediaPlayerPrivateSling.cpp

    platform/graphics/surfaces/GLTransportSurface.cpp
    platform/graphics/surfaces/GraphicsSurface.cpp

    platform/graphics/surfaces/egl/EGLConfigSelector.cpp
    platform/graphics/surfaces/egl/EGLContext.cpp
    platform/graphics/surfaces/egl/EGLHelper.cpp
    platform/graphics/surfaces/egl/EGLPbufferSurface.cpp
    platform/graphics/surfaces/egl/EGLSurface.cpp

    platform/graphics/surfaces/sling/GraphicsSurfacePbufferNatives.cpp
    platform/graphics/surfaces/sling/GraphicsSurfacePbufferPrivate.cpp
    platform/graphics/surfaces/sling/GraphicsSurfaceSling.cpp
    platform/graphics/surfaces/sling/GraphicsSurfaceTextureHostNatives.cpp

    platform/image-decoders/cairo/ImageDecoderCairo.cpp

    platform/network/SynchronousLoaderClient.cpp

    platform/network/sling/CertificateVerifier.cpp

    platform/posix/FileSystemPOSIX.cpp
    platform/posix/SharedBufferPOSIX.cpp

    platform/sling/CursorSling.cpp
    platform/sling/ErrorsSling.cpp
    platform/sling/EventLoopSling.cpp
    platform/sling/FileSystemSling.cpp
    platform/sling/KeyboardUtilitiesSling.cpp
    platform/sling/KeyedDecoderSling.cpp
    platform/sling/KeyedEncoderSling.cpp
    platform/sling/LanguageSling.cpp
    platform/sling/LocalizedStringsSling.cpp
    platform/sling/LoggingSling.cpp
    platform/sling/MIMETypeRegistrySling.cpp
    platform/sling/MainThreadSharedTimerSling.cpp
    platform/sling/PackageNotifier.cpp
    platform/sling/PasteboardSling.cpp
    platform/sling/PlatformBridgeNatives.cpp
    platform/sling/PlatformKeyboardEventSling.cpp
    platform/sling/PlatformMouseEventSling.cpp
    platform/sling/PlatformScreenSling.cpp
    platform/sling/PopupMenuSling.cpp
    platform/sling/SSLKeyGeneratorSling.cpp
    platform/sling/ScrollbarThemeSling.cpp
    platform/sling/SoundSling.cpp
    platform/sling/TemporaryLinkStubs.cpp
    platform/sling/ThreadCallbackContext.cpp
    platform/sling/UserAgentSling.cpp
    platform/sling/Variant.cpp
    platform/sling/WebMediaPlayerNatives.cpp
    platform/sling/WidgetSling.cpp

    platform/text/Hyphenation.cpp
    platform/text/LocaleICU.cpp

    rendering/RenderThemeSling.cpp
)

if (USE_CURL)
    list(APPEND WebCore_SOURCES
        platform/network/NetworkStorageSessionStub.cpp

        platform/network/curl/CookieJarCurl.cpp
        platform/network/curl/CredentialStorageCurl.cpp
        platform/network/curl/CurlCacheEntry.cpp
        platform/network/curl/CurlCacheManager.cpp
        platform/network/curl/CurlDownload.cpp
        platform/network/curl/DNSCurl.cpp
        platform/network/curl/FormDataStreamCurl.cpp
        platform/network/curl/MultipartHandle.cpp
        platform/network/curl/ProxyServerCurl.cpp
        platform/network/curl/ResourceHandleCurl.cpp
        platform/network/curl/ResourceHandleManager.cpp
        platform/network/curl/SocketStreamHandleCurl.cpp
        platform/network/curl/SSLHandle.cpp
    )
endif ()

if (USE_FREETYPE)
    list(APPEND WebCore_SOURCES
        platform/graphics/harfbuzz/HarfBuzzFace.cpp
        platform/graphics/harfbuzz/HarfBuzzFaceCairo.cpp
        platform/graphics/harfbuzz/HarfBuzzShaper.cpp

        platform/graphics/cairo/FontCairoHarfbuzzNG.cpp

        platform/graphics/freetype/FontCacheFreeType.cpp
        platform/graphics/freetype/FontCustomPlatformDataFreeType.cpp
        platform/graphics/freetype/FontPlatformDataFreeType.cpp
        platform/graphics/freetype/GlyphPageTreeNodeFreeType.cpp
        platform/graphics/freetype/SimpleFontDataFreeType.cpp
    )
endif ()

if (USE_CAIRO_WINFONT)
    list(APPEND WebCore_SOURCES
        platform/graphics/FontPlatformData.cpp

        platform/graphics/win/FontCacheWin.cpp
        platform/graphics/win/FontCustomPlatformDataCairo.cpp
        platform/graphics/win/FontPlatformDataCairoWin.cpp
        platform/graphics/win/FontPlatformDataWin.cpp
        platform/graphics/win/FontWin.cpp
        platform/graphics/win/GlyphPageTreeNodeCairoWin.cpp
        platform/graphics/win/SimpleFontDataCairoWin.cpp
        platform/graphics/win/SimpleFontDataWin.cpp
        platform/graphics/win/UniscribeController.cpp
    )
endif ()

if (WIN32)
    list(APPEND WebCore_SOURCES
        platform/crypto/win/CryptoDigestWin.cpp

        platform/graphics/opentype/OpenTypeUtilities.cpp

        platform/win/GDIUtilities.cpp
    )

    set(_all_in_one ${DERIVED_SOURCES_WEBCORE_DIR}/JSBindingsCustomAllInOne.cpp)
    file(WRITE ${_all_in_one}
        "// AUTO-GENERATED FILE. DO NOT MODIFY.\n"
        "#include \"config.h\"\n"
        "#include \"DOMWrapperWorld.h\"\n"
    )
    foreach (_source ${WebCore_SOURCES})
        string(REGEX MATCH "bindings/js/.+Custom[.]cpp" _match ${_source})
        if (_match)
            get_filename_component(_name ${_source} NAME)
            file(APPEND ${_all_in_one} "#include \"${_name}\"\n")
            list(REMOVE_ITEM WebCore_SOURCES ${_source})
        endif ()
    endforeach ()
    list(APPEND WebCore_SOURCES ${_all_in_one})
elseif (ANDROID)
    list(APPEND WebCore_SOURCES
        platform/crypto/android/CryptoDigestAndroid.cpp
    )
endif ()

list(APPEND WebCore_USER_AGENT_STYLE_SHEETS
    ${WEBCORE_DIR}/Modules/mediacontrols/mediaControlsBase.css
)

set(WebCore_USER_AGENT_SCRIPTS
    ${WEBCORE_DIR}/English.lproj/mediaControlsLocalizedStrings.js
    ${WEBCORE_DIR}/Modules/mediacontrols/mediaControlsBase.js
)

add_custom_command(
    OUTPUT ${DERIVED_SOURCES_WEBCORE_DIR}/WebKitVersion.h
    MAIN_DEPENDENCY ${WEBKIT_DIR}/scripts/generate-webkitversion.pl
    DEPENDS ${WEBKIT_DIR}/mac/Configurations/Version.xcconfig
    COMMAND ${PERL_EXECUTABLE} ${WEBKIT_DIR}/scripts/generate-webkitversion.pl --config ${WEBKIT_DIR}/mac/Configurations/Version.xcconfig --outputDir ${DERIVED_SOURCES_WEBCORE_DIR}
    VERBATIM)
list(APPEND WebCore_SOURCES ${DERIVED_SOURCES_WEBCORE_DIR}/WebKitVersion.h)

set(WebCore_USER_AGENT_SCRIPTS_DEPENDENCIES ${WEBCORE_DIR}/rendering/RenderThemeSling.cpp)

list(APPEND WebCore_INCLUDE_DIRECTORIES
    "${DERIVED_SOURCES_JAVASCRIPTCORE_DIR}"
    "${DERIVED_SOURCES_JAVASCRIPTCORE_DIR}/inspector"
    "${JAVASCRIPTCORE_DIR}"
    "${JAVASCRIPTCORE_DIR}/ForwardingHeaders"
    "${JAVASCRIPTCORE_DIR}/API"
    "${JAVASCRIPTCORE_DIR}/assembler"
    "${JAVASCRIPTCORE_DIR}/bytecode"
    "${JAVASCRIPTCORE_DIR}/bytecompiler"
    "${JAVASCRIPTCORE_DIR}/dfg"
    "${JAVASCRIPTCORE_DIR}/disassembler"
    "${JAVASCRIPTCORE_DIR}/heap"
    "${JAVASCRIPTCORE_DIR}/debugger"
    "${JAVASCRIPTCORE_DIR}/interpreter"
    "${JAVASCRIPTCORE_DIR}/jit"
    "${JAVASCRIPTCORE_DIR}/llint"
    "${JAVASCRIPTCORE_DIR}/parser"
    "${JAVASCRIPTCORE_DIR}/profiler"
    "${JAVASCRIPTCORE_DIR}/runtime"
    "${JAVASCRIPTCORE_DIR}/yarr"
    "${DERIVED_SOURCES_DIR}/NativeInterfaces/WebCore"
    "${ANGLE_INCLUDE_DIR}"
    "${ANGLE_INCLUDE_DIR}/include/KHR"
    "${WEBCORE_DIR}/page/sling"
    "${WEBCORE_DIR}/platform/sling"
    "${WEBCORE_DIR}/platform/graphics/sling"
    "${WEBCORE_DIR}/platform/graphics/cairo"
    "${WEBCORE_DIR}/platform/graphics/egl"
    "${WEBCORE_DIR}/platform/graphics/opengl"
    "${WEBCORE_DIR}/platform/graphics/surfaces"
    "${WEBCORE_DIR}/platform/graphics/surfaces/sling"
    "${WEBCORE_DIR}/platform/graphics/surfaces/egl"
    "${WEBCORE_DIR}/platform/network/sling"
    "${WTF_DIR}"
    "${WTF_DIR}/wtf/sling"
    "${CAIRO_INCLUDE_DIR}"
)

if (USE_CURL)
    list(APPEND WebCore_INCLUDE_DIRECTORIES
        "${WEBCORE_DIR}/platform/network/curl"
    )
endif ()

if (USE_FREETYPE)
    list(APPEND WebCore_INCLUDE_DIRECTORIES
        "${WEBCORE_DIR}/platform/graphics/freetype"
    )
endif ()

if (USE_CAIRO_WINFONT)
    list(APPEND WebCore_INCLUDE_DIRECTORIES
        "${WEBCORE_DIR}/platform/graphics/win"
    )
endif ()

if (WIN32)
    list(APPEND WebCore_INCLUDE_DIRECTORIES
        "${WEBCORE_DIR}/platform/win"
        "${ANGLE_INCLUDE_DIR}/include"
        "${ANGLE_INCLUDE_DIR}/include/EGL"
    )
elseif (ANDROID)
    list(APPEND WebCore_INCLUDE_DIRECTORIES
        "${ANDROID_SYS_ROOT}/usr/include/EGL"
    )
endif ()

set(WebCore_OUTPUT_NAME
    WebCore${DEBUG_SUFFIX}
)

set(WebCore_FRAMEWORK_SOURCES
    platform/audio/sling/WebAudioDestination.java
    platform/audio/sling/WebAudioFileReader.java

    platform/graphics/surfaces/sling/GraphicsSurfacePbuffer.java
    platform/graphics/surfaces/sling/GraphicsSurfaceTextureHost.java

    platform/sling/Messages.java
    platform/sling/PlatformBridge.java
    platform/sling/WebMediaPlayer.java
    platform/sling/WebMediaPlayerChannel.java
    platform/sling/WebMediaPlayerChannelMessages.java
    platform/sling/WebMediaPlayerHost.java
    platform/sling/WebMediaPlayerHostMessages.java
)

GENERATE_WEBKIT_NATIVE_INTERFACE_SOURCES(WebCore_SOURCES "${WebCore_FRAMEWORK_SOURCES}" PRIVATE)
