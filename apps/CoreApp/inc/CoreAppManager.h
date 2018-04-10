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
 * File:   CoreAppManager.h
 * Author: Peter Kocity
 *
 * Created on February 8, 2018, 10:48 AM
 */


#include "CoreAppExecutor.h"
#include "CoreAppDatabase.h"
#include "InstallRequest.h"
#include "UninstallRequest.h"
#include "StartRequest.h"
#include "StopRequest.h"
#include "FreezRequest.h"
#include "UnfreezRequest.h"
#include "UpdateRequest.h"
#include "InvalidRequest.h"


#ifndef COREAPPMANAGER_H
#define COREAPPMANAGER_H

namespace flexd {
    namespace core {

        class CoreAppManager{
        public:
            CoreAppManager(const std::string& dbPath);
            virtual ~CoreAppManager() = default;

            bool tryProcesRequest(InstallRequest& rqst);
            bool tryProcesRequest(UninstallRequest& rqst);
            bool tryProcesRequest(StartRequest& rqst);
            bool tryProcesRequest(StopRequest& rqst);
            bool tryProcesRequest(FreezRequest& rqst);
            bool tryProcesRequest(UnfreezRequest& rqst);
            bool tryProcesRequest(UpdateRequest& rqst);
            bool tryProcesRequest(InvalidRequest& rqst);

            CoreAppManager(const CoreAppManager& orig) = delete;
            CoreAppManager operator=(const CoreAppManager& orig) = delete;

        private:
            bool appExecute(const std::string cmd /*TODO*/); /*set private*/
            
            CoreAppExecutor m_exe;
            const std::string m_dbName;
            CoreAppDatabase m_db;
        };
    } // namespace core
} // namespace flexd


#endif /* COREAPPMANAGER_H */