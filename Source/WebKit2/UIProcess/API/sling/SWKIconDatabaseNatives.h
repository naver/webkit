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

#ifndef SWKIconDatabase_h
#define SWKIconDatabase_h

#include "SWKIconDatabaseNativesBase.h"

#include "SWKIconDatabaseDelegateNatives.h"
#include "WebIconDatabase.h"

#include <onig/GlobalRef.h>

namespace WebKit {

class SWKIconDatabase : public Natives::SWKIconDatabase {
    friend class Natives::SWKIconDatabase;
public:
    static Native::PassLocalRef<SWKIconDatabase> create(WebIconDatabase*);
    virtual ~SWKIconDatabase();

    Native::PassLocalRef<Natives::SWKIconDatabaseDelegate> delegate() { return m_delegate; }

protected:
    void retainIconForPageURL(const std::string&) override;
    void releaseIconForPageURL(const std::string&) override;
    void setIconURLForPageURL(const std::string&, const std::string&) override;
    void setIconDataForIconURL(Native::PassLocalRef<Natives::WebBitmap>, const std::string&) override;
    void setIconDatabaseDelegate(Native::PassLocalRef<Natives::SWKIconDatabaseDelegate> delegate) override;
    Native::ImmutableArray<int8_t> getIconDataForPageURL(const std::string&) override;
    void removeAllIcons() override;

private:
    WebIconDatabase& iconDatabase() { return *m_iconDatabase.get(); }

    RefPtr<WebIconDatabase> m_iconDatabase;
    Native::GlobalRef<Natives::SWKIconDatabaseDelegate> m_delegate;
};

}

#endif // SWKIconDatabase_h
