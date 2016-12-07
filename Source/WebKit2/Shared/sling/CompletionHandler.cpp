/*
 * Copyright (C) 2014 Naver Corp. All rights reserved.
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
#include "CompletionHandler.h"

#include <ManagedBoolean.h>
#include <ManagedInteger.h>
#include <ManagedLong.h>
#include <ManagedString.h>

namespace webkit {

void CompletionHandler::invoke()
{
    WebKit::Managed::CompletionHandler::nativeInvoke(std::shared_ptr<void>(nullptr));
}

void CompletionHandler::invoke(bool value)
{
    WebKit::Managed::CompletionHandler::nativeInvoke(Managed::Boolean::create(value));
}

void CompletionHandler::invoke(int32_t value)
{
    WebKit::Managed::CompletionHandler::nativeInvoke(Managed::Integer::create(value));
}

void CompletionHandler::invoke(int64_t value)
{
    WebKit::Managed::CompletionHandler::nativeInvoke(Managed::Long::create(value));
}

void CompletionHandler::invoke(const std::string& value)
{
    WebKit::Managed::CompletionHandler::nativeInvoke(Managed::createString(value.c_str()));
}

void CompletionHandler::invoke(std::shared_ptr<void> value)
{
    WebKit::Managed::CompletionHandler::nativeInvoke(value);
}

}

namespace WebKit {
namespace Managed {

void CompletionHandler::INIT(const std::string& typeName)
{
    nativeCreate(typeName);
}

}
} // namespace WebKit
