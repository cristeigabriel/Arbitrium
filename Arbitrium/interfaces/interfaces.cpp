#include "interfaces.h"
#include "../main/entry.h"

#include <CSGO/include.h>


cInterfaces::cInterfaces()
{

}

bool cInterfaces::initializer()
{
	client = gAddresses.find<CHLClient*>("client.dll", "VClient018");
	if (!client)
		return false;

	do
	{
		clientModeShared = **getMethod<ClientModeShared***, 10, 5>(client);
	} while (!clientModeShared);

	do
	{
		globalVars = **getMethod<CGlobalVarsBase***, 11, 10>(client);
	} while (!globalVars);

	csgoHudChat = gAddresses.find<CCSGO_HudChat*>("CCSGO_HudChat");
	if (!csgoHudChat)
		return false;

	hudChat = gAddresses.find<CHudChat*>("CHudChat");
	if (!hudChat)
		return false;

	return true;
}

cInterfaces::~cInterfaces()
{
	client = nullptr;
	clientModeShared = nullptr;
	globalVars = nullptr;
	csgoHudChat = nullptr;
	hudChat = nullptr;
}