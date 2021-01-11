#pragma once

#include "defines.h"
#include "enums.h"

class DVariant
{
public:
	union
	{
		float	vFloat;
		long	vInt;
		char* vString;
		void* vData;
		float	vVector[3];
		int64_t	vInt64;
	};

	sendPropType vType;
};

class CRecvProxyData
{
public:
	const RecvProp* recvProp; // The property it's receiving.
	DVariant		value; // The value given to you to store.
	int				element; // Which array element you're getting.
	int				objectId; // The object being referred to.
};

struct RecvProp
{
	// This info comes from the receive data table.

	char* varName;
	int						recvType;
	int						flags;
	int						stringBufSize;

	bool					insideArray;

	const void* extraData;

	RecvProp* arrayProp;
	arrayLengthRecvProxyFn	arrayLengthProxy;

	recvVarProxyFn			proxyFn;
	dataTableRecvVarProxyFn	dataTableProxyFn;

	RecvTable* dataTable;
	int						offset;

	int						elementStride;
	int						elements;

	const char* parentArrayPropName;
};

struct RecvTable
{
	RecvProp* pProps;
	int				iProps;

	CRecvDecoder* pDecoder;

	char* netTableName;

private:
	bool			initialized;
	bool			inMainList;
};

struct ClientClass
{
	createClientClassFn		createFn;
	createEventFn			createEventFn; // Only called for event objects.
	char* networkName;
	RecvTable* pRecvTable;
	ClientClass* pNext;
	classIds						classId; // Managed by the engine.
};
