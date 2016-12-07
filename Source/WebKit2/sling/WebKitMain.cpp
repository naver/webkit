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

#include "ChildProcessLauncher.h"

#include <util/StringConversion.h>

#include <cassert>
#include <regex>
#include <unordered_map>

class CommandLine {
public:
    bool parse(int argc, char* argv[])
    {
        m_options.clear();

        std::string commandLine;
        for (int i = 0; i < argc; ++i)
            commandLine.append(argv[i]).append(" ");

        // The pattern below searches for typical command line options like
        // "-option value" or "-option a single freeform value".
        static std::regex pattern("-\\S+ [^-]+\\b");
        std::sregex_iterator next(commandLine.begin(), commandLine.end(), pattern);
        std::sregex_iterator end;

        while (next != end) {
            std::string option = (*next).str();
            auto pivot = option.find_first_of(' ');

            std::string key = option.substr(1, pivot - 1);
            std::string value = option.substr(pivot + 1);
            m_options.emplace(key, value);

            next++;
        }

        return true;
    }

    std::string& operator[](const std::string& key)
    {
        return m_options[key];
    }

private:
    std::unordered_map<std::string, std::string> m_options;
};

extern "C" WEBKIT_EXPORT
int WebKitMain(int argc, char* argv[])
{
    assert(argc > 0 && argv && argv[0]);

    CommandLine commandLine;
    if (!commandLine.parse(argc, argv))
        return EXIT_FAILURE;

    webkit::ChildProcessLauncher::threadRunWebKitMain(
        commandLine["type"], 
        commandLine["clientIdentifier"],
        commandLine["extraInfo"]);

    return 0;
}
