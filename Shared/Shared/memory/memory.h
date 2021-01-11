#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <winnt.h>

#include <array>
#include <unordered_map>
#include <stdexcept>
#include <cstddef>

#include <CSGO/defines.h>

#include "../hashing/hashing.h"

namespace memory
{
	class memoryWrapper
	{
	public:
		template <typename T, uint32_t index, uint32_t offset>
		inline static T getMethod(void* thisptr)
		{
			return (T)((*(uint32_t**)(thisptr))[index] + offset);
		}
	};

	class modulesWrapper
	{
	public:
		using moduleType = HMODULE;
		using moduleMapType = std::unordered_map<hashing::hashType, moduleType>;

	public:
		moduleMapType modules;

	public:
		modulesWrapper();

		template <size_t N>
		constexpr void initializer(const std::array<const char*, N> baseModules)
		{
			for (const auto& _module : baseModules)
			{
				const moduleType result = GetModuleHandleA(_module);

				if (!result)
					throw std::runtime_error("Failed to get module");

				modules[strHashRT(_module)] = result;
			}
		}

		template <size_t N>
		constexpr modulesWrapper(const std::array<const char*, N> baseModules)
		{
			initializer(baseModules);
		}

		~modulesWrapper();
	};

	class addressesWrapper
	{
	public:
		using addressesType = uint8_t*;
		using addressesSignatureContainer = int;
		using addressesCStrikeCreateInterface = createInterface_t;

	private:
		modulesWrapper modulesObject;

	private:
		modulesWrapper::moduleType moduleCheckRoutine(const char* moduleHandleName);

	private:
		template <size_t N>
		addressesType baseFind(const char* moduleHandleName, const addressesSignatureContainer(&signature)[N])
		{
			const modulesWrapper::moduleType _module = moduleCheckRoutine(moduleHandleName);

			if (!_module)
				throw std::runtime_error("Failed getting module");

			const auto dosHeaders = PIMAGE_DOS_HEADER(_module);
			const auto ntHeaders = PIMAGE_NT_HEADERS(addressesType(_module) + dosHeaders->e_lfanew);
		
			const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
			constexpr auto sizeOfSignature = sizeof(signature) / sizeof(*signature);
			const auto scanBytes = addressesType(_module);

			for (DWORD i = 0; i < sizeOfImage - sizeOfSignature; ++i)
			{
				bool proceed = true;
				
				for (size_t j = 0; j < sizeOfSignature; ++j)
				{
					if (scanBytes[i + j] != signature[j] && signature[j] != -1)
					{
						proceed = false;
						break;
					}
				}
			
				if (proceed)
					return &scanBytes[i];
			}

			throw std::runtime_error("Failed getting signature");
			return {};
		}

		template <typename T>
		T baseFind(const char* moduleHandleName, const char* interfaceName)
		{
			const modulesWrapper::moduleType _module = moduleCheckRoutine(moduleHandleName);

			if (!_module)
				throw std::runtime_error("Failed getting module");

			const auto createInterface = addressesCStrikeCreateInterface(GetProcAddress(_module, "CreateInterface"));

			const T result = T(createInterface(interfaceName, nullptr));
			if (!result)
			{
				throw std::runtime_error("Failed to get interface");
				return {};
			}

			return result;
		}

		template <typename T>
		T baseFind(const char* hudElementName)
		{
			static uint32_t* fn = *find<uint32_t**>("client.dll",
				{ 0xB9, -1, -1, -1, -1, 0xE8, -1, -1, -1, -1, 0x8B, 0x5D, 0x08 },
				1
				);

			static auto findElement = find<uint32_t(__thiscall*)(void*, const char*)>("client.dll",
				{ 0x55, 0x8B, 0xEC, 0x53, 0x8B, 0x5D, 0x08, 0x56, 0x57, 0x8B, 0xF9, 0x33, 0xF6, 0x39, 0x77, 0x28 }
			);

			const T result = T(findElement(fn, hudElementName));

			if (!result)
				throw std::runtime_error("failed to find hud elemnet");

			return result;
		}

		template <typename T>
		T relativeToAbsolute(uint32_t address)
		{
			return T(address + 4 + *(int*)address);
		}

	public:
		addressesWrapper();

		void initializer(const modulesWrapper& object);

		template <class T, size_t N>
		T find(const char* moduleHandleName, const addressesSignatureContainer(&signature)[N], int pad = 0)
		{
			return T(baseFind(moduleHandleName, signature) + pad);
		}

		template <class T, size_t N>
		T findRelToAbs(const char* moduleHandleName, const addressesSignatureContainer(&signature)[N], int pad = 0)
		{
			return relativeToAbsolute<T>(find<uint32_t>(moduleHandleName, signature, pad));
		}

		template <typename T>
		T find(const char* moduleHandleName, const char* interfaceName)
		{
			return baseFind<T>(moduleHandleName, interfaceName);
		}

		template <typename T>
		T find(const char* hudElement)
		{
			return baseFind<T>(hudElement);
		}

		addressesWrapper(const modulesWrapper& object);

		~addressesWrapper();
	};
}