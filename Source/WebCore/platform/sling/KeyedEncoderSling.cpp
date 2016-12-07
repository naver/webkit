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
#include "KeyedEncoderSling.h"

#include "SharedBuffer.h"
#include <wtf/text/CString.h>

namespace WebCore {

std::unique_ptr<KeyedEncoder> KeyedEncoder::encoder()
{
    return std::make_unique<KeyedEncoderSling>();
}

KeyedEncoderSling::KeyedEncoderSling()
{
    m_variants = std::make_shared<VariantVector>();
    m_variantsStack.append(m_variants);
}

KeyedEncoderSling::~KeyedEncoderSling()
{
    ASSERT(m_variantsStack.size() == 1);
    ASSERT(m_variantsStack.last() == m_variants);
    ASSERT(m_arrayStack.isEmpty());
    ASSERT(m_objectStack.isEmpty());
}

void KeyedEncoderSling::encodeBytes(const String& key, const uint8_t* bytes, size_t size)
{
    m_variantsStack.last()->append(Variant::create(key, DataType::Bytes, String(bytes, size)));
}

void KeyedEncoderSling::encodeBool(const String& key, bool value)
{
    m_variantsStack.last()->append(Variant::create(key, DataType::Boolean, String(value ? "1" : "0")));
}

template<typename T>
void KeyedEncoderSling::encodeNumber(const String& key, T value, DataType type)
{
    String number= String::number(value);
    m_variantsStack.last()->append(Variant::create(key, type, number));
}

void KeyedEncoderSling::encodeUInt32(const String& key, uint32_t value)
{
    encodeNumber(key, value, DataType::UInt32);
}

void KeyedEncoderSling::encodeInt32(const String& key, int32_t value)
{
    encodeNumber(key, value, DataType::Int32);
}

void KeyedEncoderSling::encodeInt64(const String& key, int64_t value)
{
    encodeNumber(key, value, DataType::Int64);
}

void KeyedEncoderSling::encodeFloat(const String& key, float value)
{
    encodeNumber(key, value, DataType::Float);
}

void KeyedEncoderSling::encodeDouble(const String& key, double value)
{
    encodeNumber(key, value, DataType::Double);
}

void KeyedEncoderSling::encodeString(const String& key, const String& value)
{
    m_variantsStack.last()->append(Variant::create(key, DataType::String, value));
}

String KeyedEncoderSling::variantsToBytes(const std::shared_ptr<VariantVector>& variants)
{
    RefPtr<SharedBuffer> buffer = SharedBuffer::create();
    size_t dictionarySize = variants->size();
    buffer->append(reinterpret_cast<const char*>(&dictionarySize), sizeof(size_t));
    for (auto& variant : *variants)
        variant->serialize(*buffer);

    return String(buffer->data(), buffer->size());
}

void KeyedEncoderSling::beginObject(const String& key)
{
    std::shared_ptr<VariantVector> vector = std::make_shared<VariantVector>();
    m_objectStack.append(std::make_pair(key, vector));
    m_variantsStack.append(vector);
}

void KeyedEncoderSling::endObject()
{
    String value = variantsToBytes(m_variantsStack.takeLast());
    m_variantsStack.last()->append(Variant::create(m_objectStack.last().first, DataType::Object, value));
    m_objectStack.removeLast();
}

void KeyedEncoderSling::beginArray(const String& key)
{
    std::shared_ptr<VariantVector> vector = std::make_shared<VariantVector>();
    m_arrayStack.append(std::make_pair(key, vector));
}

void KeyedEncoderSling::beginArrayElement()
{
    std::shared_ptr<VariantVector> vector = std::make_shared<VariantVector>();
    m_variantsStack.append(vector);
}

void KeyedEncoderSling::endArrayElement()
{
    String value = variantsToBytes(m_variantsStack.takeLast());
    m_arrayStack.last().second->append(Variant::create(m_arrayStack.last().first, DataType::Variants, value));
}

void KeyedEncoderSling::endArray()
{
    String value = variantsToBytes(m_arrayStack.last().second);
    m_variantsStack.last()->append(Variant::create(m_arrayStack.last().first, DataType::Array, value));
    m_arrayStack.removeLast();
}

PassRefPtr<SharedBuffer> KeyedEncoderSling::finishEncoding()
{
    RefPtr<SharedBuffer> buffer = SharedBuffer::create();
    String data = variantsToBytes(m_variantsStack.last());
    return SharedBuffer::create(data.latin1().data(), data.length());;
}

} // namespace WebKit
