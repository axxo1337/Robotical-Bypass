#pragma once

#include <Windows.h>
#include <TlHelp32.h>

namespace mem
{
	DWORD GetProcId(const wchar_t* procName);
	uintptr_t GetModule(DWORD dwProcID, const wchar_t* moduleName);
	void PatchMem(BYTE* lpAddress, BYTE* src, unsigned int sizeofinstruction, HANDLE hProcess);
}