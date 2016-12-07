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

#ifndef WebKitPrefix_h
#define WebKitPrefix_h

#include <stdint.h>

#undef WEBKIT_EXPORT
#if defined(WIN32)
#define COMPILER_EXPORT __declspec(dllexport)
#define COMPILER_IMPORT __declspec(dllimport)
#elif defined(__GNUC__) && !defined(__CC_ARM) && !defined(__ARMCC__)
#define COMPILER_EXPORT __attribute__((visibility("default")))
#define COMPILER_IMPORT COMPILER_EXPORT
#endif

#if defined(WebKit_EXPORTS)
#define WEBKIT_EXPORT COMPILER_EXPORT
#else
#define WEBKIT_EXPORT COMPILER_IMPORT
#endif

#undef NO_EXPORT
#define NO_EXPORT

#if !defined(ANDROID)
#include <media/ImportHeader.h>
#include <opengl/ImportHeader.h>
#include <os/ImportHeader.h>
#include <util/ImportHeader.h>
#include <view/ImportHeader.h>
#endif

#endif // WebKitPrefix_h
