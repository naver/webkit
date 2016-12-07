/*
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
#include "WebSocketServer.h"

#if ENABLE(INSPECTOR_SERVER)

#include "WebSocketServerConnection.h"
#include <WebCore/NotImplemented.h>
#include <WebCore/SocketStreamHandle.h>
#include <wtf/PassOwnPtr.h>
#include <wtf/RunLoop.h>
#include <wtf/text/CString.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace WebCore;

namespace WebKit {

static int bindSocket(const char* address, unsigned short port)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        LOG_ERROR("Failed to create a socket.");
        return -1;
    }

    sockaddr_in addr;

    memset((char *)&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    inet_aton(address, (in_addr*)&addr.sin_addr.s_addr);
    addr.sin_port = htons(port);
 
    if (::bind(sockfd, (sockaddr*)&addr, sizeof(sockaddr_in)) < 0) {
        LOG_ERROR("Failed to bind socket.");
        ::close(sockfd);
        return -1;
    }

    return sockfd;
}

static void acceptSocket(WebSocketServer* server, int sockfd)
{
    std::unique_ptr<WebSocketServerConnection> webSocketConnection = std::unique_ptr<WebSocketServerConnection>(new WebSocketServerConnection(server->client(), server));
    webSocketConnection->setSocketHandle(SocketStreamHandle::create(sockfd, webSocketConnection.get()));
    server->didAcceptConnection(std::move(webSocketConnection));
}

static void socketListen(WebSocketServer* server, int sockfd)
{
    while (::listen(sockfd, 5) != -1) {
        int size = sizeof(sockaddr_in);
        sockaddr_in addr;
        int connfd = accept(sockfd, (sockaddr*)&addr, &size);         
        if (connfd == -1) {
            LOG_ERROR("Failed accepting connection");
        } else {
            RunLoop::main().dispatch(bind(&acceptSocket, server, connfd));
        }
    }
}

void WebSocketServer::platformInitialize()
{
    m_serviceQueue = WorkQueue::create("org.WebKit.WebSocketServer");
    m_socketDescriptor = -1;
}

bool WebSocketServer::platformListen(const String& bindAddress, unsigned short port)
{
    m_socketDescriptor = bindSocket(bindAddress.ascii().data(), port);
    if (m_socketDescriptor <= 0)
        return false;

    m_serviceQueue->dispatch(bind(&socketListen, this, m_socketDescriptor));
    return true;
}

void WebSocketServer::platformClose()
{
    ::close(m_socketDescriptor);
}

}

#endif // ENABLE(INSPECTOR_SERVER)
