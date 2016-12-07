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
#include "KeyedDecoderSling.h"

#include "SharedBuffer.h"
#include "Variant.h"
#include <wtf/text/CString.h>

namespace WebCore {

std::unique_ptr<KeyedDecoder> KeyedDecoder::decoder(const uint8_t* data, size_t size)
{
    return std::make_unique<KeyedDecoderSling>(data, size);
}

KeyedDecoderSling::KeyedDecoderSling(const uint8_t* data, size_t size)
{
    ASSERT(size > 0);
    m_dictionaryStack.append(dictionaryFromBytes(reinterpret_cast<const char*>(data), size));
}

KeyedDecoderSling::~KeyedDecoderSling()
{
    ASSERT(m_dictionaryStack.size() == 1);
    ASSERT(m_arrayStack.isEmpty());
    ASSERT(m_arrayIndexStack.isEmpty());
}

KeyedDecoderSling::VariantHashMap KeyedDecoderSling::dictionaryFromBytes(const char* data, size_t size)
{
    RefPtr<SharedBuffer> buffer = SharedBuffer::create(data, size);

    size_t dictionarySize;
    memcpy(&dictionarySize, buffer->data(), sizeof(size_t));

    VariantHashMap dictionary;
    unsigned pos = sizeof(size_t);
    for (int i = 0; i < dictionarySize; ++i) {
        RefPtr<Variant> variant = Variant::create();
        variant->deserialize(*buffer, pos);
        String keyString(variant->key());
        ASSERT(!keyString.isEmpty());
        dictionary.set(keyString, variant);
    }

    return WTFMove(dictionary);
}

KeyedDecoderSling::VariantVector KeyedDecoderSling::variantsFromBytes(const char* data, size_t size)
{
    RefPtr<SharedBuffer> buffer = SharedBuffer::create(data, size);

    size_t dictionarySize;
    memcpy(&dictionarySize, buffer->data(), sizeof(size_t));

    VariantVector variants;
    unsigned pos = sizeof(size_t);
    for (int i = 0; i < dictionarySize; ++i) {
        RefPtr<Variant> variant = Variant::create();
        variant->deserialize(*buffer, pos);
        variants.append(variant);
    }

    return WTFMove(variants);
}

bool KeyedDecoderSling::decodeBytes(const String& key, const uint8_t*& bytes, size_t& size)
{
    RefPtr<Variant> variant = m_dictionaryStack.last().get(key);
    if (!variant || variant->type() != DataType::Bytes)
        return false;

    size = variant->value().length();
    bytes = reinterpret_cast<const uint8_t*>(variant->value().latin1().data());
    return true;
}

bool KeyedDecoderSling::decodeBool(const String& key, bool& result)
{
    RefPtr<Variant> variant = m_dictionaryStack.last().get(key);
    if (!variant || variant->type() != DataType::Boolean)
        return false;

    result = variant->value() == "1" ? true : false;
    return true;
}

bool KeyedDecoderSling::decodeUInt32(const String& key, uint32_t& result)
{
    RefPtr<Variant> variant = m_dictionaryStack.last().get(key);
    if (!variant || variant->type() != DataType::UInt32)
        return false;

    result = variant->value().toUInt();
    return true;
}

bool KeyedDecoderSling::decodeInt32(const String& key, int32_t& result)
{
    RefPtr<Variant> variant = m_dictionaryStack.last().get(key);
    if (!variant || variant->type() != DataType::Int32)
        return false;

    result = variant->value().toInt();
    return true;
}

bool KeyedDecoderSling::decodeInt64(const String& key, int64_t& result)
{
    RefPtr<Variant> variant = m_dictionaryStack.last().get(key);
    if (!variant || variant->type() != DataType::Int64)
        return false;

    result = variant->value().toInt64();
    return true;
}

bool KeyedDecoderSling::decodeFloat(const String& key, float& result)
{
    RefPtr<Variant> variant = m_dictionaryStack.last().get(key);
    if (!variant || variant->type() != DataType::Float)
        return false;

    result = variant->value().toFloat();
    return true;
}

bool KeyedDecoderSling::decodeDouble(const String& key, double& result)
{
    RefPtr<Variant> variant = m_dictionaryStack.last().get(key);
    if (!variant || variant->type() != DataType::Double)
        return false;

    result = variant->value().toDouble();
    return true;
}

bool KeyedDecoderSling::decodeString(const String& key, String& result)
{
    RefPtr<Variant> variant = m_dictionaryStack.last().get(key);
    if (!variant || variant->type() != DataType::String)
        return false;

    result = variant->value();
    return true;
}

bool KeyedDecoderSling::beginObject(const String& key)
{
    RefPtr<Variant> variant = m_dictionaryStack.last().get(key);
    if (!variant || variant->type() != DataType::Object)
        return false;

    m_dictionaryStack.append(dictionaryFromBytes(variant->value().latin1().data(), variant->value().length()));
    return true;
}

void KeyedDecoderSling::endObject()
{
    m_dictionaryStack.removeLast();
}

bool KeyedDecoderSling::beginArray(const String& key)
{
    RefPtr<Variant> variant = m_dictionaryStack.last().get(key);
    if (!variant || variant->type() != DataType::Array)
        return false;

    m_arrayStack.append(variantsFromBytes(variant->value().latin1().data(), variant->value().length()));
    m_arrayIndexStack.append(0);
    return true;
}

bool KeyedDecoderSling::beginArrayElement()
{
    if (m_arrayIndexStack.last() >= m_arrayStack.last().size())
        return false;

    RefPtr<Variant> variant = m_arrayStack.last().at(m_arrayIndexStack.last()++);
    if (!variant || variant->type() != DataType::Variants)
        return false;

    m_dictionaryStack.append(dictionaryFromBytes(variant->value().latin1().data(), variant->value().length()));
    return true;
}

void KeyedDecoderSling::endArrayElement()
{
    m_dictionaryStack.removeLast();
}

void KeyedDecoderSling::endArray()
{
    m_arrayStack.removeLast();
    m_arrayIndexStack.removeLast();
}

} // namespace WebCore
