#include "memory.h"

memory::modulesWrapper::modulesWrapper()
{

}

memory::modulesWrapper::~modulesWrapper()
{
	modules.clear();
}

memory::modulesWrapper::moduleType memory::addressesWrapper::moduleCheckRoutine(const char* moduleHandleName)
{
#ifndef ONLY_USE_PREACQUIRED_MODULES
	if (modulesObject.modules.contains(strHashRT(moduleHandleName)))
		return modulesObject.modules.at(strHashRT(moduleHandleName));

	modulesObject.modules.at(strHashRT(moduleHandleName)) = GetModuleHandleA(moduleHandleName);
#endif

	return modulesObject.modules.at(strHashRT(moduleHandleName));
}

memory::addressesWrapper::addressesWrapper()
{

}

void memory::addressesWrapper::initializer(const memory::modulesWrapper& object)
{
	modulesObject = object;
}

memory::addressesWrapper::addressesWrapper(const memory::modulesWrapper& object)
{
	initializer(object);
}

memory::addressesWrapper::~addressesWrapper()
{
	modulesObject.~modulesWrapper();
}