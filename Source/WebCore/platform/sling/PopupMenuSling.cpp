/*
 * This file is part of the popup menu implementation for <select> elements in WebCore.
 *
 * Copyright 2009, The Android Open Source Project
 * Copyright (C) 2006 Apple Computer, Inc.
 * Copyright (C) 2006 Michael Emmel mike.emmel@gmail.com 
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
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

#include "config.h"
#include "PopupMenuSling.h"

#include "IntRect.h"
#include "NotImplemented.h"
#include "PopupMenuClient.h"

using namespace WebCore;

namespace WebCore {

PopupMenuSling::PopupMenuSling(PopupMenuClient* menuList)
    : m_popupClient(menuList)
    , m_reply(0)
{
}

PopupMenuSling::~PopupMenuSling()
{
    disconnectClient();
}

void PopupMenuSling::disconnectClient()
{
    m_popupClient = 0;
    notImplemented();
}

void PopupMenuSling::show(const IntRect&, FrameView*, int)
{
    notImplemented();
}

} // namespace WebCore
