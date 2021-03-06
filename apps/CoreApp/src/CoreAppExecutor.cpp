/*
Copyright (c) 2018, Globallogic s.r.o.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
 * Neither the name of the Globallogic s.r.o. nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL GLOBALLOGIC S.R.O. BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* 
 * File:   CoreAppExecutor.cpp
 * Author: Peter Kocity
 *
 * Created on February 8, 2018, 10:42 AM
 */

#include "FleXdLogger.h"
#include "CoreAppExecutor.h"
#include <stdio.h>


namespace flexd {
    namespace core {

        CoreAppExecutor::CoreAppExecutor() {
        }

        void CoreAppExecutor::runOsCmd(const std::string& cmd) const {
            std::string newconsole = "konsole -e \"" + cmd + "\"";
            FLEX_LOG_DEBUG("CoreAppExecutor::runOsCmd() executing command: ", newconsole);
            system(newconsole.c_str());
        }

        std::string CoreAppExecutor::runOsCmdWithResult(const std::string& cmd, const std::string& path) {
            FLEX_LOG_DEBUG("CoreAppExecutor::runOsCmdWithResult() executing command: ", cmd);
            std::string cmdHelp=cmd;
            if(path != "./")
                cmdHelp=cmdHelp + path;
            FLEX_LOG_DEBUG("command+path ", cmdHelp);
            std::string data;
            std::FILE * stream;
            const int max_buffer = 256;
            char buffer[max_buffer];
            cmdHelp.append(" 2>&1"); //potlacenie error mesage
            stream = popen(cmdHelp.c_str(), "r");
            if (stream) {
                while (!feof(stream))
                    if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
                pclose(stream);
            }
            return data;
        }
    }
}
    

