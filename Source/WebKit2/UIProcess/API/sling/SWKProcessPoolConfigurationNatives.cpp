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
#include "SWKProcessPoolConfigurationNatives.h"

#include <NativesVector.h>

namespace WebKit {

Native::PassLocalRef<SWKProcessPoolConfiguration> SWKProcessPoolConfiguration::create(Ref<API::ProcessPoolConfiguration> configuration)
{
    Native::LocalRef<SWKProcessPoolConfiguration> wrapper = Natives::SWKProcessPoolConfiguration::create();
    wrapper->m_configuration = WTFMove(configuration);
    return wrapper;
}

static SWKProcessPoolConfiguration& ptr(Natives::SWKProcessPoolConfiguration* p)
{
    return *static_cast<SWKProcessPoolConfiguration*>(p);
}

namespace Natives {

int32_t SWKProcessPoolConfiguration::getMaximumProcessCount()
{
    return ptr(this).m_configuration->maximumProcessCount();
}

void SWKProcessPoolConfiguration::setMaximumProcessCount(int64_t maximumProcessCount)
{
    ptr(this).m_configuration->setMaximumProcessCount(maximumProcessCount);
}

std::string SWKProcessPoolConfiguration::getInjectedBundlePath()
{
    return ptr(this).m_configuration->injectedBundlePath().utf8().data();
}

void SWKProcessPoolConfiguration::setInjectedBundlePath(const std::string& injectedBundlePath)
{
    ptr(this).m_configuration->setInjectedBundlePath(String::fromUTF8(injectedBundlePath.c_str()));
}

Native::PassLocalRef<Natives::Vector> SWKProcessPoolConfiguration::getCachePartitionedURLSchemes()
{
    return nullptr;
}

void SWKProcessPoolConfiguration::setCachePartitionedURLSchemes(Native::PassLocalRef<Natives::Vector> cachePartitionedURLSchemes)
{
}

SWKProcessPoolConfiguration* SWKProcessPoolConfiguration::nativeCreate()
{
    return new ::WebKit::SWKProcessPoolConfiguration();
}

}
} // namespace WebKit
