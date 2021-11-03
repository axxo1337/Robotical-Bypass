#include "Mem.h"

DWORD mem::GetProcId(const wchar_t* procName)
{
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);
		//loop through all process
		if (Process32First(hSnap, &procEntry))
		{

			do
			{
				//compare current lopping process name with procName parameters
				if (!_wcsicmp(procEntry.szExeFile, procName))
				{
					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}
	//close handle and return the procId of the process
	CloseHandle(hSnap);
	return procId;
}

uintptr_t mem::GetModule(DWORD dwProcID, const wchar_t* moduleName)
{
	uintptr_t modEntry = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcID);

	if (hSnapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 curr = { 0 };

		curr.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(hSnapshot, &curr))
		{
			do
			{
				if (!wcscmp(curr.szModule, moduleName))
				{
					modEntry = (uintptr_t)curr.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnapshot, &curr));
		}
		CloseHandle(hSnapshot);
	}
	return modEntry;
}

void mem::PatchMem(BYTE* lpAddress, BYTE* src, unsigned int sizeofinstruction, HANDLE hProcess)
{
	DWORD oldProtection;
	VirtualProtectEx(hProcess, lpAddress, sizeofinstruction, PROCESS_VM_READ | PROCESS_VM_WRITE, &oldProtection);
	WriteProcessMemory(hProcess, lpAddress, src, sizeofinstruction, 0);
	VirtualProtectEx(hProcess, lpAddress, sizeofinstruction, oldProtection, &oldProtection);
}