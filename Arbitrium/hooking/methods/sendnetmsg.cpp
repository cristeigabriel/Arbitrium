#include <CSGO/include.h>

#include "../hooking.h"
#include "../prototypes.h"

bool __fastcall prototypes::sendNetMsg::hooked(void* ecx, void* edx,
	INetMessage& message, bool forceReliable, bool voice)
{
	// look at "CNetMessagePB<14,CCLCMsg_FileCRCCheck,0,1>"

	// prevent the server from receiving the message if it's passed this bs
	if (message.getType() == clcMessages::CLC_FILE_CRC_CHECK)
		return false;

	if (message.getGroup() == netChannelMessages::NCM_VOICE)
		return false;

	return original(ecx, edx, message, forceReliable, voice);
}