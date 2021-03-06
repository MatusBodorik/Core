
/*
Copyright (c) 2017, Globallogic s.r.o.
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
  *  Autogenerated output, do not edit!
  */


#include "JsonObj.h"
#include "FleXdIPCConnector.h"
#include "FleXdEpoll.h"
#include "FleXdIPCMsg.h"
#include "IPCInterface.h"
#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <cstdint>

    
namespace flexd {
  namespace gen {
  
	IPCInterface::IPCInterface (flexd::icl::ipc::FleXdEpoll& poller)
	:IPCConnector(11111, poller),
	 m_counter(0)
	{     
         
	  addPeer(12345);
	}
	
        IPCInterface::~IPCInterface()
        {
        }
       
       
       void IPCInterface::sendRequestCoreAckMsg(bool OperationAck, const std::string& Message, const std::string& AppID)
       {
	   uint8_t msgtype = 1;
           uint8_t msgCounter = m_counter;
           uint32_t timeStamp = getTimestamp();
           uint32_t from = getMyID();
           uint32_t to = 12345;
           int id = 2;
           
	   flexd::icl::JsonObj json = {};
	   
	    
	   json.add<int>("/id", id);
	   json.add<bool>("/payload/OperationAck", OperationAck);
	   json.add<std::string>("/payload/Message", Message);
	   json.add<std::string>("/payload/AppID", AppID);

	   std::string tmp = json.getJson();
           std::vector<uint8_t> payload(tmp.begin(), tmp.end());
           
           auto msg = std::make_shared<flexd::icl::ipc::FleXdIPCMsg>(std::move(payload),true);
           auto addHeader = msg->getAdditionalHeader();
	   
                 addHeader->setValue_0(msgtype);
                 addHeader->setValue_1(msgCounter);
                 addHeader->setValue_3(timeStamp);
                 addHeader->setValue_4(from);
                 addHeader->setValue_5(to);
           send(msg);
       }
       
        void IPCInterface::receiveMsg(flexd::icl::ipc::pSharedFleXdIPCMsg msg)
        {
            try{
		std::string str(msg->getPayload().begin(),msg->getPayload().end());
		flexd::icl::JsonObj json(str);
		if(json.exist("/id"))
		{
		    int id; 
		    json.get<int>("/id", id);
		    switch(id)
		    {
			case 1: {
			    uint8_t Operation;
                            std::string Message;
                            std::string AppID;
                            
			    bool tmp = true;
			    
			    if(json.exist("/payload/Operation")){
				json.get<uint8_t>("/payload/Operation", Operation); 
			    } else {
				tmp = false;}
			    
			    if(json.exist("/payload/Message")){
				json.get<std::string>("/payload/Message", Message); 
			    } else {
				tmp = false;}
			    
			    if(json.exist("/payload/AppID")){
				json.get<std::string>("/payload/AppID", AppID); 
			    } else {
				tmp = false;}
			    
                            
			    if(tmp){
			       receiveRequestCoreMsg(Operation, Message, AppID);}
			    break; }
	    
	           }
	        }
	   }catch(...){
		return;
	   }
        }
        
       
	void IPCInterface::send(std::shared_ptr<flexd::icl::ipc::FleXdIPCMsg> Msg)
        {
	   if(sendMsg(Msg))
	   {
	      m_counter++;
	   }
        }
        
        uint32_t IPCInterface::getTimestamp()
        {
	    std::chrono::time_point<std::chrono::system_clock> p;
	    p = std::chrono::system_clock::now();
	    std::time_t time = std::chrono::duration_cast<std::chrono::milliseconds>(p.time_since_epoch()).count();
	    return static_cast<uint32_t> (time);
        }  
        
     }
}
