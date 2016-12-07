/*
 * Copyright (C) 2012 Samsung Electronics Ltd. All Rights Reserved.
 * Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies)
 * Copyright (C) 2013 Naver Corp. All rights reserved.
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
#include "WebInspectorServer.h"

#if ENABLE(INSPECTOR_SERVER)

#include "WebInspectorProxy.h"
#include "WebPageProxy.h"
#include <WebCore/FileSystem.h>
#include <WebCore/MIMETypeRegistry.h>
#include <sys/stat.h>
#include <wtf/text/CString.h>
#include <wtf/text/StringBuilder.h>

namespace WebKit {

static String inspectorBaseURL()
{
    String inspectorFilesPath = String::fromUTF8(getenv("WEBKIT_WEB_INSPECTOR_INSTALL_DIR"));
    if (!inspectorFilesPath.isEmpty() && access(inspectorFilesPath.utf8().data(), R_OK))
        return inspectorFilesPath;

    inspectorFilesPath = String::fromUTF8(WebCore::applicationDirectoryPath().data());
    inspectorFilesPath.append("/WebKit.resources/WebInspectorUI");
    return inspectorFilesPath;
}

bool WebInspectorServer::platformResourceForPath(const String& path, Vector<char>& data, String& contentType)
{
    // The page list contains an unformated list of pages that can be inspected with a link to open a session.
    if (path == "/pagelist.json") {
        buildPageList(data, contentType);
        return true;
    }

    // Point the default path to a formatted page that queries the page list and display them.
    String localPath = inspectorBaseURL() + ((path == "/") ? ASCIILiteral("/inspectorPageIndex.html") : path);

    FILE* fileHandle = fopen(localPath.utf8().data(), "rb");
    if (!fileHandle) {
        LOG_ERROR("File not found: %s", localPath.utf8().data());
        return false;
    }

    struct stat fileStat;
    if (fstat(fileno(fileHandle), &fileStat)) {
        fclose(fileHandle);
        return false;
    }

    data.grow(fileStat.st_size);
    int bytesRead = fread(data.data(), 1, fileStat.st_size, fileHandle);
    fclose(fileHandle);

    if (bytesRead < fileStat.st_size)
        return false;

    size_t extStart = localPath.reverseFind('.');
    if (extStart == notFound)
        return false;

    String ext = localPath.substring(extStart + 1);
    if (ext.isEmpty())
        return false;

    contentType = WebCore::MIMETypeRegistry::getMIMETypeForExtension(ext);

    return true;
}

void WebInspectorServer::buildPageList(Vector<char>& data, String& contentType)
{
    StringBuilder builder;
    builder.appendLiteral("[ ");
    ClientMap::iterator end = m_clientMap.end();
    for (ClientMap::iterator it = m_clientMap.begin(); it != end; ++it) {
        WebPageProxy* webPage = it->value->page();
        if (it != m_clientMap.begin())
            builder.appendLiteral(", ");
        builder.appendLiteral("{ \"id\": ");
        builder.appendNumber(it->key);
        builder.appendLiteral(", \"title\": \"");
        builder.append(webPage->pageLoadState().title());
        builder.appendLiteral("\", \"url\": \"");
        builder.append(webPage->pageLoadState().activeURL());
        builder.appendLiteral("\", \"inspectorUrl\": \"");
        builder.appendLiteral("/Main.html?page=");
        builder.appendNumber(it->key);
        builder.appendLiteral("\" }");
    }
    builder.appendLiteral(" ]");
    CString cstr = builder.toString().utf8();
    data.append(cstr.data(), cstr.length());
    contentType = "application/json; charset=utf-8";
}

}

#endif // ENABLE(INSPECTOR_SERVER)
