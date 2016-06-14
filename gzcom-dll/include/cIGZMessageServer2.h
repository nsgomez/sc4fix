#pragma once
#include "cIGZUnknown.h"

class cIGZMessage2;
class cIGZMessageTarget2;

class cIGZMessageServer2 : public cIGZUnknown
{
	public:
		virtual bool MessageSend(cIGZMessage2* pMessage) = 0;
		virtual bool MessagePost(cIGZMessage2* pMessage, bool bHighPriority) = 0;

		virtual bool AddNotification(cIGZMessageTarget2* pTarget, uint32_t dwMessageID) = 0;
		virtual bool RemoveNotification(cIGZMessageTarget2* pTarget, uint32_t dwMessageID) = 0;

		virtual bool GeneralMessagePostToTarget(cIGZMessage2* pMessage, cIGZMessageTarget2* pTarget) = 0;
		virtual bool CancelGeneralMessagePostsToTarget(cIGZMessageTarget2* pTarget) = 0;
		
		virtual bool OnTick(void) = 0;

		virtual uint32_t GetMessageQueueSize(void) = 0;
		virtual cIGZMessageServer2* SetAlwaysClearQueueOnTick(bool bToggle) = 0;

		virtual uint32_t GetRefCount(void) = 0;
		virtual cIGZMessage2* CreateMessage(uint32_t clsid, uint32_t msgid, void** ppData) = 0;
};