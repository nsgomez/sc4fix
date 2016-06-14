#pragma once
#include "cIGZUnknown.h"

class cGZMessage;
class cIGZMessageTarget;

class cIGZMessageServer : public cIGZUnknown
{
	public:
		virtual bool MessageSend(cGZMessage const& sMessage) = 0;
		virtual bool MessagePost(cGZMessage const& sMessage, bool bHighPriority) = 0;

		virtual bool AddNotification(cIGZMessageTarget* pTarget, uint32_t dwMessageID) = 0;
		virtual bool RemoveNotification(cIGZMessageTarget* pTarget, uint32_t dwMessageID) = 0;

		virtual bool GeneralMessagePostToTarget(cGZMessage const& sMessage, cIGZMessageTarget* pTarget) = 0;
		virtual bool CancelGeneralMessagePostsToTarget(cIGZMessageTarget* pTarget) = 0;

		virtual bool OnTick(void) = 0;

		virtual uint32_t GetMessageQueueSize(void) = 0;
		virtual cIGZMessageServer* SetAlwaysClearQueueOnTick(bool bToggle) = 0;
};