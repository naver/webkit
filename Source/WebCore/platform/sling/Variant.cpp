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
#include "Variant.h"

#include "SharedBuffer.h"
#include <wtf/text/CString.h>
#include <vector>

namespace WebCore {

RefPtr<Variant> Variant::create()
{
    return adoptRef(*new Variant());
}

RefPtr<Variant> Variant::create(const String& key, DataType type, const String& value)
{
    return adoptRef(*new Variant(key, type, value));
}

Variant::Variant()
    : m_type(DataType::NoType)
{
}

Variant::Variant(const String& key, DataType type, const String& value)
    : m_type(type)
    , m_key(key)
    , m_value(value)
{
}

template<typename T>
static void serializeData(SharedBuffer& buffer, T&& data)
{
    buffer.append(reinterpret_cast<const char*>(&data), sizeof(T));
}

static void serializeData(SharedBuffer& buffer, String& data)
{
    serializeData(buffer, data.length());
    buffer.append(data.latin1().data(), data.length());
}

void Variant::serialize(SharedBuffer& buffer)
{
    serializeData(buffer, m_type);
    serializeData(buffer, m_key);
    serializeData(buffer, m_value);
}

template<typename T>
static void deserializeData(SharedBuffer& buffer, T& data, unsigned& pos)
{
    const char* dataPtr;
    unsigned size = buffer.getSomeData(dataPtr, pos);
    ASSERT(size >= sizeof(T));
    memcpy(&data, dataPtr, sizeof(T));
    pos += sizeof(T);
}

static void deserializeData(SharedBuffer& buffer, String& data, unsigned& pos)
{
    unsigned length;
    deserializeData(buffer, length, pos);
    const char* charsPtr;
    unsigned size = buffer.getSomeData(charsPtr, pos);
    ASSERT(size >= length);
    data = String(charsPtr, length);
    pos += length;
}

void Variant::deserialize(SharedBuffer& buffer, unsigned& pos)
{
    deserializeData(buffer, m_type, pos);
    deserializeData(buffer, m_key, pos);
    deserializeData(buffer, m_value, pos);
}

} // namespace WebCore
