#pragma once

#include <cstddef>
#include <cstdint>

#pragma region classes / structs
class bfRead;
class bfWrite;

class CRecvDecoder;
class DVariant;
class CRecvProxyData;
struct RecvProp;
struct RecvTable;
struct ClientClass;
class CSaveRestoreData;

class CUserCmd;

class INetMessage;
class INetChannelInfo;

class IBaseClientDLL;
class CHLClient;
class CGlobalVarsBase;
class ClientModeShared;
class CCSGO_HudChat;
class CHudChat;
#pragma endregion

#pragma region type definitions
using createInterface_t = void* (*)(const char*, int*);

using createClientClassFn = void* (*)(int entSum, int serialNum);
using createEventFn = void* (*)();

using recvVarProxyFn = void(*)(const CRecvProxyData* data, void* sstruct, void* out);
using dataTableRecvVarProxyFn = void(*)(const RecvProp* prop, void** out, void* data, int objectId);
using arrayLengthRecvProxyFn = void(*)(void* sstruct, int objectId, int curArrLen);
#pragma endregion