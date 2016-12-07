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
#include "SWKContextMenuDelegate.h"

#include "SWKContextMenuItem.h"
#include <ManagedPoint.h>
#include <ManagedVector.h>

namespace WebKit {
namespace Managed {

void SWKContextMenuDelegate::INIT()
{
}

void SWKContextMenuDelegate::getContextMenuFromProposedMenu(std::shared_ptr<Managed::Vector> items)
{
}

void SWKContextMenuDelegate::customContextMenuItemSelected(std::shared_ptr<Managed::SWKContextMenuItem>)
{
}

bool SWKContextMenuDelegate::showContextMenu(std::shared_ptr<Managed::Point>, std::shared_ptr<Native::Managed::Vector>)
{
    return false;
}

bool SWKContextMenuDelegate::hideContextMenu()
{
    return false;
}

} // namespace Managed
} // namespace WebKit
