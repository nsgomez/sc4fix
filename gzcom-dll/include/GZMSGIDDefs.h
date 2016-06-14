#pragma once
#include <stdint.h>

/**
 * @brief An enumeration of all known message IDs in SC4.
 *
 * A list of all known game message IDs. There is the possibility that some
 * messages exist in the game that do not have their IDs documented here
 * because they were not represented in a DoMessage method.
 */
class GZMSGID
{
	public:
		// <missing>

		static const uint32_t kMiscCommand_ListCommands = -1414770972;
		static const uint32_t kMiscCommand_SetDebugLevel = 733218867;
		static const uint32_t kMiscCommand_CreateGZLog = 1807486381;
		static const uint32_t kMiscCommand_GZLog = -1952371432;
		static const uint32_t kMiscCommand_SetGZLogLevel = 1271158812;
		static const uint32_t kMiscCommand_Assert = -1950516865;
		static const uint32_t kMiscCommand_RZCheckHeap = 195112219;
		static const uint32_t kMiscCommand_ExecuteScript = -1414789508;
		static const uint32_t kMiscCommand_GetDateAndTime = 1276416784;
		static const uint32_t kMiscCommand_GetTimerTime = -341044230;
		static const uint32_t kMiscCommand_GetFrameCount = 732701573;
		static const uint32_t kMiscCommand_GetFrameRate = 197064869;
		static const uint32_t kMiscCommand_ExecuteCheat = -1414781259;
		static const uint32_t kMiscCommand_WaitForMessage2 = -877907212;
		static const uint32_t kMiscCommand_CancelWaitForMessage2 = -341034665;
		static const uint32_t kMiscCommand_GetPathDirectory = 196875648;
		static const uint32_t kMiscCommand_GetPathFileName = -339995253;
		static const uint32_t kMiscCommand_GetDirectory = -877573156;
		static const uint32_t kMiscCommand_GetRandomNumber = -1951314485;
		static const uint32_t kMiscCommand_GetRandomInteger = -1951314474;
		static const uint32_t kMiscCommand_TakeSnapshot = 733050228;
		static const uint32_t kMiscCommand_GameDelay = -877560815;
		static const uint32_t kMiscCommand_GamePause = -877560814;
		static const uint32_t kMiscCommand_WriteRegistry = 733051982;
		static const uint32_t kMiscCommand_ViewWebBrowser = 196181092;
		static const uint32_t kMiscCommand_SendMessage = -1414431628;
		static const uint32_t kMiscCommand_GetAppState = 196460563;
		static const uint32_t kMiscCommand_SetScriptAutoYield = 1807334371;
		static const uint32_t kMiscCommand_CreateException = 197283728;
		static const uint32_t kMiscCommand_GetPopupModalDialogsSafe = 198085285;
		static const uint32_t kMiscCommand_GetPopupModalDialogsEnabled = -1412527449;
		static const uint32_t kMiscCommand_SetPopupModalDialogsEnabled = 1808698086;
		static const uint32_t kMiscCommand_GetOccupantCount = 1808715726;
		static const uint32_t kMiscCommand_GetMemInfo = -868862361;

		// <missing>

		static const uint32_t kModalWindowMouseMessage = -99851376;
		static const uint32_t kcGZSndEventStd = 0xDB53383B;
		
		static const uint32_t kToolCommand_Demolish = 733252929;
		static const uint32_t kToolCommand_PlaceNetwork = -877795954;
		static const uint32_t kToolCommand_PlaceLot = 733252902;
		static const uint32_t kToolCommand_PlaceZone = -340488911;
		static const uint32_t kToolCommand_UnknownCommand1 = -1950919004;
		static const uint32_t kToolCommand_UnknownCommand2 = 732820851;
		static const uint32_t kToolCommand_UnknownCommand3 = 196707644;

		// <missing>

		static const uint32_t kHTMLDocument_ResourceDownloaded = 1970635907;
		
		static const uint32_t kNetCommandGenerator_IdleMessage = 196973691;

		// <missing>

		static const uint32_t kSC424HourClock_Command = 588130220;

		// <missing>
};