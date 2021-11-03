#include <iostream>

#include "Mem.h"

#include <Windows.h>

int main()
{
	std::cout << "Waiting for Diabotical to launch..." << std::endl;
	uintptr_t pID = 0;
	do
	{
		pID = mem::GetProcId(L"Diabotical-Launcher.exe");
		Sleep(25);
	} while (!pID);
	uintptr_t base = mem::GetModule(pID, L"Diabotical-Launcher.exe");
	std::cout << "Diabotical found!\n[PID] = " << pID << "\n[BASE] = " << (FARPROC)base << std::endl;
	{ // Install patch
		HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, false, pID);
		mem::PatchMem((BYTE*)(base + 0x1044AA), (BYTE*)"\x75\x35", 2, hProc);
	}
	std::cout << "Successfuly installed patch at " << (FARPROC)(base + 0x104482) << std::endl;
	std::cin.get();
	return 0;
}