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
#include "CompletionHandlerNatives.h"

namespace WebKit {
namespace Natives {

CompletionHandler* CompletionHandler::nativeCreate(std::string typeName)
{
    CString type(typeName.data());

    if (type == NativeTypeTraits<void>::name())
        return new ::WebKit::CompletionHandler<void>();
    else if (type == NativeTypeTraits<bool>::name())
        return new ::WebKit::CompletionHandler<bool>();
    else if (type == NativeTypeTraits<int32_t>::name())
        return new ::WebKit::CompletionHandler<int32_t>();
    else if (type == NativeTypeTraits<int64_t>::name())
        return new ::WebKit::CompletionHandler<int64_t>();
    else if (type == NativeTypeTraits<WTF::String>::name())
        return new ::WebKit::CompletionHandler<WTF::String>();
    else if (type == NativeTypeTraits<WebCore::IntPoint>::name())
        return new ::WebKit::CompletionHandler<WebCore::IntPoint>();
    else if (type == NativeTypeTraits<WebCore::IntRect>::name())
        return new ::WebKit::CompletionHandler<WebCore::IntRect>();

    ASSERT_NOT_REACHED();
    return new ::WebKit::CompletionHandler<void>();
}

}
}
