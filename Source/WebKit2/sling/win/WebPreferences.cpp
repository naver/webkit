/*
 * Copyright (C) 2015 Naver Corp. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "WebKitDLLMain.h"
#include "WebPreferences.h"

#include "Assertions.h"

// WebPreferences ----------------------------------------------------------------

WebPreferences* sharedStandardPreferences()
{
    static WebPreferences* standardPreferences;
    if (!standardPreferences) {
        standardPreferences = WebPreferences::createInstance();
        standardPreferences->setAutosaves(TRUE);
    }

    return standardPreferences;
}

WebPreferences::WebPreferences()
{
    gClassCount++;
}

WebPreferences::~WebPreferences()
{
    gClassCount--;
}

WebPreferences* WebPreferences::createInstance()
{
    WebPreferences* instance = new WebPreferences();
    instance->AddRef();
    return instance;
}

// IUnknown -------------------------------------------------------------------

HRESULT WebPreferences::QueryInterface(_In_ REFIID riid, _COM_Outptr_ void** ppvObject)
{
    if (!ppvObject)
        return E_POINTER;
    *ppvObject = nullptr;
    if (IsEqualGUID(riid, IID_IUnknown))
        *ppvObject = static_cast<IWebPreferences*>(this);
    else if (IsEqualGUID(riid, IID_IWebPreferences))
        *ppvObject = static_cast<IWebPreferences*>(this);
    else if (IsEqualGUID(riid, IID_IWebPreferencesPrivate))
        *ppvObject = static_cast<IWebPreferencesPrivate*>(this);
    else if (IsEqualGUID(riid, IID_IWebPreferencesPrivate2))
        *ppvObject = static_cast<IWebPreferencesPrivate2*>(this);
    else if (IsEqualGUID(riid, IID_IWebPreferencesPrivate3))
        *ppvObject = static_cast<IWebPreferencesPrivate3*>(this);
    else if (IsEqualGUID(riid, CLSID_WebPreferences))
        *ppvObject = this;
    else
        return E_NOINTERFACE;

    AddRef();
    return S_OK;
}

ULONG WebPreferences::AddRef()
{
    return ++m_refCount;
}

ULONG WebPreferences::Release()
{
    ULONG newRef = --m_refCount;
    if (!newRef)
        delete(this);

    return newRef;
}

// IWebPreferences ------------------------------------------------------------

HRESULT WebPreferences::standardPreferences(_COM_Outptr_opt_ IWebPreferences** standardPreferences)
{
    if (!standardPreferences)
        return E_POINTER;
    *standardPreferences = sharedStandardPreferences();
    (*standardPreferences)->AddRef();
    return S_OK;
}

HRESULT WebPreferences::initWithIdentifier(_In_ BSTR anIdentifier, _COM_Outptr_opt_ IWebPreferences** preferences)
{
    return S_OK;
}

HRESULT WebPreferences::identifier(__deref_opt_out BSTR* ident)
{
    return S_OK;
}

HRESULT WebPreferences::standardFontFamily(__deref_opt_out BSTR* family)
{
    return S_OK;
}

HRESULT WebPreferences::setStandardFontFamily(_In_ BSTR family)
{
    return S_OK;
}

HRESULT WebPreferences::fixedFontFamily(__deref_opt_out BSTR* family)
{
    return S_OK;
}

HRESULT WebPreferences::setFixedFontFamily(_In_ BSTR family)
{
    return S_OK;
}

HRESULT WebPreferences::serifFontFamily(__deref_opt_out BSTR* fontFamily)
{
    return S_OK;
}

HRESULT WebPreferences::setSerifFontFamily(_In_ BSTR family)
{
    return S_OK;
}

HRESULT WebPreferences::sansSerifFontFamily(__deref_opt_out BSTR* family)
{
    return S_OK;
}

HRESULT WebPreferences::setSansSerifFontFamily(_In_ BSTR family)
{
    return S_OK;
}

HRESULT WebPreferences::cursiveFontFamily(__deref_opt_out BSTR* family)
{
    return S_OK;
}

HRESULT WebPreferences::setCursiveFontFamily(_In_ BSTR family)
{
    return S_OK;
}

HRESULT WebPreferences::fantasyFontFamily(__deref_opt_out BSTR* family)
{
    return S_OK;
}

HRESULT WebPreferences::setFantasyFontFamily(_In_ BSTR family)
{
    return S_OK;
}

HRESULT WebPreferences::pictographFontFamily(__deref_opt_out BSTR* family)
{
    return S_OK;
}

HRESULT WebPreferences::setPictographFontFamily(_In_ BSTR family)
{
    return S_OK;
}

HRESULT WebPreferences::defaultFontSize(_Out_  int* fontSize)
{
    return S_OK;
}

HRESULT WebPreferences::setDefaultFontSize(int fontSize)
{
    return S_OK;
}

HRESULT WebPreferences::defaultFixedFontSize(_Out_ int* fontSize)
{
    return S_OK;
}

HRESULT WebPreferences::setDefaultFixedFontSize(int fontSize)
{
    return S_OK;
}

HRESULT WebPreferences::minimumFontSize(_Out_ int* fontSize)
{
    return S_OK;
}

HRESULT WebPreferences::setMinimumFontSize(int fontSize)
{
    return S_OK;
}

HRESULT WebPreferences::minimumLogicalFontSize(_Out_ int* fontSize)
{
    return S_OK;
}

HRESULT WebPreferences::setMinimumLogicalFontSize(int fontSize)
{
    return S_OK;
}

HRESULT WebPreferences::defaultTextEncodingName(__deref_opt_out BSTR* name)
{
    return S_OK;
}

HRESULT WebPreferences::setDefaultTextEncodingName(_In_ BSTR name)
{
    return S_OK;
}

HRESULT WebPreferences::userStyleSheetEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setUserStyleSheetEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::userStyleSheetLocation(__deref_opt_out BSTR* location)
{
    return (*location) ? S_OK : E_FAIL;
}

HRESULT WebPreferences::setUserStyleSheetLocation(_In_ BSTR location)
{
    return S_OK;
}

HRESULT WebPreferences::isJavaEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setJavaEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::isJavaScriptEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setJavaScriptEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::javaScriptRuntimeFlags(_Out_ unsigned* flags)
{
    return S_OK;
}

HRESULT WebPreferences::setJavaScriptRuntimeFlags(unsigned flags)
{
    return S_OK;
}

HRESULT WebPreferences::isWebSecurityEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setWebSecurityEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::allowUniversalAccessFromFileURLs(_Out_ BOOL* allowAccess)
{
    return S_OK;
}

HRESULT WebPreferences::setAllowUniversalAccessFromFileURLs(BOOL allowAccess)
{
    return S_OK;
}

HRESULT WebPreferences::allowFileAccessFromFileURLs(_Out_ BOOL* allowAccess)
{
    return S_OK;
}

HRESULT WebPreferences::setAllowFileAccessFromFileURLs(BOOL allowAccess)
{
    return S_OK;
}

HRESULT WebPreferences::javaScriptCanAccessClipboard(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setJavaScriptCanAccessClipboard(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::isXSSAuditorEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setXSSAuditorEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::isFrameFlatteningEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setFrameFlatteningEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::javaScriptCanOpenWindowsAutomatically(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setJavaScriptCanOpenWindowsAutomatically(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::arePlugInsEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setPlugInsEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::isCSSRegionsEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setCSSRegionsEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::allowsAnimatedImages(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setAllowsAnimatedImages(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::allowAnimatedImageLooping(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setAllowAnimatedImageLooping(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setLoadsImagesAutomatically(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::loadsImagesAutomatically(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setLoadsSiteIconsIgnoringImageLoadingPreference(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::loadsSiteIconsIgnoringImageLoadingPreference(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setHixie76WebSocketProtocolEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::hixie76WebSocketProtocolEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setMediaPlaybackRequiresUserGesture(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::mediaPlaybackRequiresUserGesture(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setMediaPlaybackAllowsInline(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::mediaPlaybackAllowsInline(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setAutosaves(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::autosaves(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setShouldPrintBackgrounds(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::shouldPrintBackgrounds(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setPrivateBrowsingEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::privateBrowsingEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setTabsToLinks(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::tabsToLinks(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setUsesPageCache(BOOL usesPageCache)
{
    return S_OK;
}

HRESULT WebPreferences::usesPageCache(_Out_ BOOL* usesPageCache)
{
    return S_OK;
}

HRESULT WebPreferences::textAreasAreResizable(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setTextAreasAreResizable(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::unused1()
{
    return E_FAIL;
}

HRESULT WebPreferences::unused2()
{
    return E_FAIL;
}

HRESULT WebPreferences::iconDatabaseLocation(__deref_opt_out BSTR* location)
{
    return (*location) ? S_OK : E_FAIL;
}

HRESULT WebPreferences::setIconDatabaseLocation(_In_ BSTR location)
{
    return S_OK;
}

HRESULT WebPreferences::iconDatabaseEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setIconDatabaseEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::fontSmoothing(_Out_ FontSmoothingType* smoothingType)
{
    return S_OK;
}

HRESULT WebPreferences::setFontSmoothing(FontSmoothingType smoothingType)
{
    return S_OK;
}

HRESULT WebPreferences::fontSmoothingContrast(_Out_ float* contrast)
{
    return S_OK;
}

HRESULT WebPreferences::setFontSmoothingContrast(float contrast)
{
    return S_OK;
}

HRESULT WebPreferences::editableLinkBehavior(_Out_ WebKitEditableLinkBehavior* editableLinkBehavior)
{
    return S_OK;
}

HRESULT WebPreferences::setEditableLinkBehavior(WebKitEditableLinkBehavior behavior)
{
    return S_OK;
}

HRESULT WebPreferences::unused5()
{
    ASSERT_NOT_REACHED();
    return E_FAIL;
}

HRESULT WebPreferences::unused6()
{
    ASSERT_NOT_REACHED();
    return E_FAIL;
}

HRESULT WebPreferences::mockScrollbarsEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setMockScrollbarsEnabled(BOOL enabled)
{
    return S_OK;
}

// These two methods are no-ops, and only retained to keep
// the Interface consistent. DO NOT USE THEM.
HRESULT WebPreferences::screenFontSubstitutionEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setScreenFontSubstitutionEnabled(BOOL)
{
    return S_OK;
}

HRESULT WebPreferences::hyperlinkAuditingEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setHyperlinkAuditingEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::cookieStorageAcceptPolicy(_Out_ WebKitCookieStorageAcceptPolicy* acceptPolicy)
{
    return S_OK;
}

HRESULT WebPreferences::setCookieStorageAcceptPolicy(WebKitCookieStorageAcceptPolicy acceptPolicy)
{
    return S_OK;
}

HRESULT WebPreferences::continuousSpellCheckingEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setContinuousSpellCheckingEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::grammarCheckingEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setGrammarCheckingEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::allowContinuousSpellChecking(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setAllowContinuousSpellChecking(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::unused7()
{
    ASSERT_NOT_REACHED();
    return E_FAIL;
}

HRESULT WebPreferences::unused8()
{
    ASSERT_NOT_REACHED();
    return E_FAIL;
}

HRESULT WebPreferences::isDOMPasteAllowed(_Out_ BOOL* enabled)
{
    return S_OK;
}
    
HRESULT WebPreferences::setDOMPasteAllowed(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::cacheModel(_Out_ WebCacheModel* cacheModel)
{
    return S_OK;
}

HRESULT WebPreferences::setCacheModel(WebCacheModel cacheModel)
{
    return S_OK;
}

HRESULT WebPreferences::unused3()
{
    ASSERT_NOT_REACHED();
    return E_FAIL;
}

HRESULT WebPreferences::unused4()
{
    ASSERT_NOT_REACHED();
    return E_FAIL;
}

// These two methods are no-ops, and only retained to keep
// the Interface consistent. DO NOT USE THEM.
HRESULT WebPreferences::shouldPaintNativeControls(_Out_ BOOL* enable)
{
    if (!enable)
        return E_POINTER;
    *enable = FALSE;
    return S_OK;
}

HRESULT WebPreferences::setShouldPaintNativeControls(BOOL)
{
    return S_OK;
}

HRESULT WebPreferences::setDeveloperExtrasEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::developerExtrasEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setAutomaticallyDetectsCacheModel(BOOL automaticallyDetectsCacheModel)
{
    return S_OK;
}

HRESULT WebPreferences::automaticallyDetectsCacheModel(_Out_ BOOL* automaticallyDetectsCacheModel)
{
    return S_OK;
}

HRESULT WebPreferences::setAuthorAndUserStylesEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::authorAndUserStylesEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

// These two methods are no-ops, and only retained to keep
// the Interface consistent. DO NOT USE THEM.
HRESULT WebPreferences::inApplicationChromeMode(_Out_ BOOL* enabled)
{
    if (!enabled)
        return E_POINTER;
    *enabled = FALSE;
    return S_OK;
}

HRESULT WebPreferences::setApplicationChromeMode(BOOL)
{
    return S_OK;
}

HRESULT WebPreferences::setOfflineWebApplicationCacheEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::offlineWebApplicationCacheEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setDatabasesEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::databasesEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setLocalStorageEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::localStorageEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::localStorageDatabasePath(__deref_opt_out BSTR* location)
{
    return (*location) ? S_OK : E_FAIL;
}

HRESULT WebPreferences::setLocalStorageDatabasePath(_In_ BSTR location)
{
    return S_OK;
}

HRESULT WebPreferences::setExperimentalNotificationsEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::experimentalNotificationsEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setZoomsTextOnly(BOOL zoomsTextOnly)
{
    return S_OK;
}

HRESULT WebPreferences::zoomsTextOnly(_Out_ BOOL* zoomsTextOnly)
{
    return S_OK;
}

HRESULT WebPreferences::setShouldUseHighResolutionTimers(BOOL useHighResolutionTimers)
{
    return S_OK;
}

HRESULT WebPreferences::shouldUseHighResolutionTimers(_Out_ BOOL* useHighResolutionTimers)
{
    return S_OK;
}

HRESULT WebPreferences::setPreferenceForTest(_In_ BSTR key, _In_ BSTR value)
{
    return S_OK;
}

HRESULT WebPreferences::setAcceleratedCompositingEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::acceleratedCompositingEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::showDebugBorders(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setShowDebugBorders(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::showRepaintCounter(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setShowRepaintCounter(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setCustomDragCursorsEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::customDragCursorsEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::setDNSPrefetchingEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::isDNSPrefetchingEnabled(_Out_ BOOL* enabled)
{
    return S_OK;
}

HRESULT WebPreferences::isFullScreenEnabled(_Out_ BOOL* enabled)
{
#if ENABLE_FULLSCREEN_API
    if (!enabled)
        return E_POINTER;

    *enabled = false;
    return S_OK;
#else
    return E_NOTIMPL;
#endif
}

HRESULT WebPreferences::setFullScreenEnabled(BOOL enabled)
{
#if ENABLE_FULLSCREEN_API
    return S_OK;
#else
    return E_NOTIMPL;
#endif
}

HRESULT WebPreferences::avFoundationEnabled(_Out_ BOOL* enabled)
{
    return E_NOTIMPL;
}

HRESULT WebPreferences::setAVFoundationEnabled(BOOL enabled)
{
    return E_NOTIMPL;
}

HRESULT WebPreferences::showsToolTipOverTruncatedText(_Out_ BOOL* showsToolTip)
{
    return S_OK;
}

HRESULT WebPreferences::setShowsToolTipOverTruncatedText(BOOL showsToolTip)
{
    return S_OK;
}

HRESULT WebPreferences::shouldInvertColors(_Out_ BOOL* shouldInvertColors)
{
    return S_OK;
}

HRESULT WebPreferences::setShouldInvertColors(BOOL shouldInvertColors)
{
    return S_OK;
}

HRESULT WebPreferences::shouldDisplaySubtitles(_Out_ BOOL* enabled)
{
#if ENABLE_VIDEO_TRACK
    if (!enabled)
        return E_POINTER;

    *enabled = false;
    return S_OK;
#else
    return E_NOTIMPL;
#endif
}

HRESULT WebPreferences::setShouldDisplaySubtitles(BOOL enabled)
{
#if ENABLE_VIDEO_TRACK
    return S_OK;
#else
    return E_NOTIMPL;
#endif
}

HRESULT WebPreferences::shouldDisplayCaptions(_Out_ BOOL* enabled)
{
#if ENABLE_VIDEO_TRACK
    if (!enabled)
        return E_POINTER;

    *enabled = false;
    return S_OK;
#else
    return E_NOTIMPL;
#endif
}

HRESULT WebPreferences::setShouldDisplayCaptions(BOOL enabled)
{
#if ENABLE_VIDEO_TRACK
    return S_OK;
#else
    return E_NOTIMPL;
#endif
}

HRESULT WebPreferences::shouldDisplayTextDescriptions(_Out_ BOOL* enabled)
{
#if ENABLE_VIDEO_TRACK
    if (!enabled)
        return E_POINTER;

    *enabled = false;
    return S_OK;
#else
    return E_NOTIMPL;
#endif
}

HRESULT WebPreferences::setShouldDisplayTextDescriptions(BOOL enabled)
{
#if ENABLE_VIDEO_TRACK
    return S_OK;
#else
    return E_NOTIMPL;
#endif
}

HRESULT WebPreferences::setRequestAnimationFrameEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::requestAnimationFrameEnabled(_Out_ BOOL* enabled)
{
    if (!enabled)
        return E_POINTER;
    *enabled = true;
    return S_OK;
}

HRESULT WebPreferences::isInheritURIQueryComponentEnabled(_Out_ BOOL* enabled)
{
    if (!enabled)
        return E_POINTER;
    *enabled = false;
    return S_OK;
}

HRESULT WebPreferences::setEnableInheritURIQueryComponent(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::allowDisplayAndRunningOfInsecureContent(_Out_ BOOL* enabled)
{
    if (!enabled)
        return E_POINTER;
    *enabled = false;
    return S_OK;
}

HRESULT WebPreferences::setAllowDisplayAndRunningOfInsecureContent(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::showTiledScrollingIndicator(_Out_ BOOL* enabled)
{
    if (!enabled)
        return E_POINTER;
    *enabled = false;
    return S_OK;
}

HRESULT WebPreferences::setShowTiledScrollingIndicator(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::domIteratorEnabled(BOOL *enabled)
{
    if (!enabled)
        return E_POINTER;
    *enabled = false;
    return S_OK;
}

HRESULT WebPreferences::setDOMIteratorEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::fetchAPIEnabled(BOOL *enabled)
{
    if (!enabled)
        return E_POINTER;
    *enabled = false;
    return S_OK;
}

HRESULT WebPreferences::setFetchAPIEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::shadowDOMEnabled(BOOL *enabled)
{
    if (!enabled)
        return E_POINTER;
    *enabled = false;
    return S_OK;
}

HRESULT WebPreferences::setShadowDOMEnabled(BOOL enabled)
{
    return S_OK;
}

HRESULT WebPreferences::customElementsEnabled(BOOL *enabled)
{
    if (!enabled)
        return E_POINTER;
    *enabled = false;
    return S_OK;
}

HRESULT WebPreferences::setCustomElementsEnabled(BOOL enabled)
{
    return S_OK;
}
