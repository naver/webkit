/*
 * Copyright (C) 2014 Igalia S.L.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "config.h"
#include "CustomProtocolManagerImpl.h"

#include "ChildProcess.h"
#include "CustomProtocolManagerProxyMessages.h"
#include "DataReference.h"
#include "WebCoreArgumentCoders.h"
#include <WebCore/ResourceError.h>
#include <WebCore/ResourceRequest.h>
#include <WebCore/ResourceResponse.h>

namespace WebKit {

CustomProtocolManagerImpl::CustomProtocolManagerImpl(ChildProcess* childProcess)
    : m_childProcess(childProcess)
{
}

CustomProtocolManagerImpl::~CustomProtocolManagerImpl()
{
}

void CustomProtocolManagerImpl::registerScheme(const String& scheme)
{
    notImplemented();
}

bool CustomProtocolManagerImpl::supportsScheme(const String& scheme)
{
    notImplemented();
    return false;
}

void CustomProtocolManagerImpl::didFailWithError(uint64_t customProtocolID, const WebCore::ResourceError& error)
{
    notImplemented();
}

void CustomProtocolManagerImpl::didLoadData(uint64_t customProtocolID, const IPC::DataReference& dataReference)
{
    notImplemented();
}

void CustomProtocolManagerImpl::didReceiveResponse(uint64_t customProtocolID, const WebCore::ResourceResponse& response)
{
    notImplemented();
}

void CustomProtocolManagerImpl::didFinishLoading(uint64_t customProtocolID)
{
    notImplemented();
}

} // namespace WebKit
