/*
 * Copyright (C) 2015 The SWK Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package labs.naver.webkit.clutter;

import java.util.Vector;

import labs.naver.onig.AbstractNativeMethod;
import labs.naver.onig.AccessedByNative;
import labs.naver.onig.CalledByNative;
import labs.naver.onig.NativeClassExport;
import labs.naver.onig.NativeConstructor;
import labs.naver.onig.NativeDestructor;
import labs.naver.onig.NativeNamespace;
import labs.naver.onig.NativeObjectField;

@NativeNamespace("WebKit")
@NativeClassExport("WEBCORE_EXPORT")
public class WebMediaPlayer {
    @AccessedByNative
    public static final int PLAYER_DISPOSITION_DEFAULT = 0;
    @AccessedByNative
    public static final int PLAYER_DISPOSITION_EMBED = 1;
    @AccessedByNative
    public static final int PLAYER_DISPOSITION_REMOTE = 2;

    @CalledByNative
    public WebMediaPlayer(int playerDisposition) {
        nativeCreate();
    }

    @CalledByNative
    @AbstractNativeMethod
    public void load(String url) {

    }

    @CalledByNative
    @AbstractNativeMethod
    public void cancelLoad() {

    }

    @CalledByNative
    @AbstractNativeMethod
    public void prepareToPlay() {

    }

    @CalledByNative
    @AbstractNativeMethod
    public void play() {

    }

    @CalledByNative
    @AbstractNativeMethod
    public boolean isPlaying() {
        return false;
    }

    @CalledByNative
    @AbstractNativeMethod
    public void pause() {

    }

    @CalledByNative
    @AbstractNativeMethod
    public boolean supportsFullscreen() {
        return false;
    }

    @CalledByNative
    @AbstractNativeMethod
    public boolean supportsScanning() {
        return false;
    }

    @CalledByNative
    @AbstractNativeMethod
    public boolean requiresImmediateCompositing() {
        return true;
    }

    @CalledByNative
    @AbstractNativeMethod
    public boolean canSaveMediaData() {
        return false;
    }

    @CalledByNative
    @AbstractNativeMethod
    public float naturalWidth() {
        return 0;
    }

    @CalledByNative
    @AbstractNativeMethod
    public float naturalHeight() {
        return 0;
    }

    @CalledByNative
    @AbstractNativeMethod
    public boolean hasVideo() {
        return true;
    }

    @CalledByNative
    @AbstractNativeMethod
    public boolean hasAudio() {
        return true;
    }

    @CalledByNative
    @AbstractNativeMethod
    public void setVisible(boolean visible) {
    }

    @CalledByNative
    @AbstractNativeMethod
    public float duration() {
        return 0;
    }

    @CalledByNative
    @AbstractNativeMethod
    public float currentTime() {
        return 0;
    }

    @CalledByNative
    @AbstractNativeMethod
    public void seek(float position) {
    }

    @CalledByNative
    @AbstractNativeMethod
    public boolean seeking() {
        return false;
    }

    @CalledByNative
    @AbstractNativeMethod
    public void setRate(float rate) {

    }

    @CalledByNative
    @AbstractNativeMethod
    public double rate() {
        return 0;
    }

    @CalledByNative
    @AbstractNativeMethod
    public void setPreservesPitch(boolean pitch) {

    }

    @CalledByNative
    @AbstractNativeMethod
    public boolean paused() {
        return false;
    }

    @CalledByNative
    @AbstractNativeMethod
    public void setVolume(float volume) {

    }

    @CalledByNative
    @AbstractNativeMethod
    public boolean supportsMuting() {
        return false;
    }

    @CalledByNative
    @AbstractNativeMethod
    public void setMuted(boolean mute) {

    }

    @CalledByNative
    @AbstractNativeMethod
    public boolean hasClosedCaptions() {
        return false;
    }

    @CalledByNative
    @AbstractNativeMethod
    public void setClosedCaptionsVisible(boolean visible) {

    }

    @CalledByNative
    @AbstractNativeMethod
    public long totalBytes() {
        return 0;
    }

    @CalledByNative
    @AbstractNativeMethod
    public boolean didLoadingProgress() {
        return false;
    }

    @CalledByNative
    @AbstractNativeMethod
    public void enterFullscreen() {

    }

    @CalledByNative
    @AbstractNativeMethod
    public void exitFullscreen() {

    }

    @CalledByNative
    @AbstractNativeMethod
    public boolean canEnterFullscreen() {
        return false;
    }

    @CalledByNative
    @AbstractNativeMethod
    public double maximumDurationToCacheMediaTime() {
        return 0;
    }

    @CalledByNative
    @AbstractNativeMethod
    public String engineDescription() {
        return "mediaplayer-sling";
    }

    @CalledByNative
    @AbstractNativeMethod
    boolean shouldMaintainAspectRatio() {
        return true;
    }

    @CalledByNative
    @AbstractNativeMethod
    public void setShouldMaintainAspectRatio(boolean maintainable) {

    }

    @CalledByNative
    @AbstractNativeMethod
    public boolean hasSingleSecurityOrigin() {
        return false;
    }

    @CalledByNative
    @AbstractNativeMethod
    public boolean didPassCORSAccessCheck() {
        return false;
    }

    @CalledByNative
    @AbstractNativeMethod
    public int decodedFrameCount() {
        return 0;
    }

    @CalledByNative
    @AbstractNativeMethod
    public int droppedFrameCount() {
        return 0;
    }

    @CalledByNative
    @AbstractNativeMethod
    public int audioDecodedByteCount() {
        return 0;
    }

    @CalledByNative
    @AbstractNativeMethod
    public int videoDecodedByteCount() {
        return 0;
    }

    @CalledByNative
    @AbstractNativeMethod
    public void getSitesInMediaCache(Vector<String> sites) {

    }

    @CalledByNative
    @AbstractNativeMethod
    public void clearMediaCache() {

    }

    @CalledByNative
    @AbstractNativeMethod
    public void clearMediaCacheForSite(String site) {

    }

    @CalledByNative
    @AbstractNativeMethod
    public void setPrivateBrowsingMode(boolean mode) {

    }

    @CalledByNative
    @AbstractNativeMethod
    public void resetTexture(long shareContext, int width, int height) {

    }

    @CalledByNative
    @AbstractNativeMethod
    public int swapTextureBackbuffers() {
        return 0;
    }

    @CalledByNative
    @AbstractNativeMethod
    public int getTextureShareToken() {
        return 0;
    }

    @CalledByNative
    @AbstractNativeMethod
    public void destroyFrontbufferSurface() {

    }

    @CalledByNative
    @AbstractNativeMethod
    public void restoreFrontbufferSurface(long shareContext, int width, int height) {

    }

    @NativeObjectField
    private int mNativeClass;

    @Override
    protected void finalize() {
        nativeDestroy();
    }

    @NativeConstructor
    private native void nativeCreate();
    @NativeDestructor
    private native void nativeDestroy();

    private native void mediaPlayerBufferingUpdate(int percent);
    private native void mediaPlayerCompletion();
    private native void mediaPlayerError(int type);
    private native void mediaPlayerFrameAvailable();
    private native void mediaPlayerPrepared(int duration);
    private native void mediaPlayerSeekComplete();
    private native void mediaPlayerVideoSizeChanged(int width, int height);
    private native void mediaPlayerContextLost();
}
