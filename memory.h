#pragma once

#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include <TlHelp32.h>

// ------------------------------------------------------------------------
// ------------------------Process Class Declaration------------------------
// ------------------------------------------------------------------------

class Process {
private :
	LPCSTR ProcessName;
	HWND hWindow;
	HANDLE hProcess;
public :
	DWORD32 pid;
	DWORD64 BaseAddr;
	Process(LPCSTR name,LPWSTR ModuleName);
	
	void GetProcessId();
	bool GetProcessBaseAddr(LPWSTR ModuleName);
	bool bDataCompare(DWORD64 pData, const BYTE* bMask, const char* szMask);

	HWND GetWindowHandle();
	HANDLE GetProcessHandle();	
	
	DWORD64 GetOffsetByPattern(BYTE* bMask, char* szMask);
	DWORD64 ReadMemoryByte(LPCVOID TargetAddress,int size);
	DWORD64 FindPattern(DWORD64 dwAddress, DWORD64 dwLen, BYTE* bMask, char* szMask);
};

DWORD64 GetModuleBaseAddress(DWORD procId, const wchar_t* modName);

// Process Class Constructor 
// Get WindowHandle, ProcessId, ProcessHandle, Module BaseAddr 
Process::Process(LPCSTR name, LPWSTR ModuleName) {
	ProcessName = name;
	pid = 0;

	hWindow = GetWindowHandle();
	if (hWindow == nullptr)
		printf("Get Window Handle Fail!\n");

	GetProcessId();
	if (pid == 0)
		printf("Get Proces id Fail!!\n");

	hProcess = GetProcessHandle();
	if (hProcess == nullptr)
		printf("Get Process Handle Fail!!\n");
	if (GetProcessBaseAddr(ModuleName))
		printf("Process Base : %016llX \n", BaseAddr);
	else
		printf("Get BaseAddr Fail! \n");
};

// Get WindowHandle by ProcessName
HWND Process::GetWindowHandle() {
	HWND RetHWND = FindWindowA(ProcessName, NULL);
	if (RetHWND) {
		return RetHWND;
	}
	else {
		return nullptr;
	}

};

//Get Processid by Windowhandle
void Process::GetProcessId() {
	GetWindowThreadProcessId(hWindow, (DWORD*)&pid);
};

//Get ProcessHandle by ProcessId
HANDLE Process::GetProcessHandle() {
	HANDLE RetHANDLE = OpenProcess(GENERIC_READ, 0, pid);
	if (RetHANDLE) {
		return RetHANDLE;
	}
	else {
		return nullptr;
	}

}

//Get ModuleBaseAddress by ProcessId and ModuleName
bool Process::GetProcessBaseAddr(LPWSTR ModuleName) {
	DWORD_PTR module = {};
	module = GetModuleBaseAddress(pid, ModuleName);
	BaseAddr = module;
	return true;
}

//Find Hexcode Pattern in Process's Specific Module
DWORD64 Process::GetOffsetByPattern(BYTE* bMask, char* szMask) {
	DWORD64 ret = FindPattern(BaseAddr, 0x3d00000, bMask, szMask);
	return ret;
};

//Read Bytes of Specific size from Start Address.
DWORD64 Process::ReadMemoryByte(LPCVOID TargetAddress, int size) {
	DWORD64 buf = 0;
	ReadProcessMemory(hProcess, TargetAddress, &buf, size, NULL);
	return buf;
};

//Compare Read byte with byte Code & Mask inside of process
bool Process::bDataCompare(DWORD64 pData, const BYTE* bMask, const char* szMask)
{
	BYTE Data = 0;
	for (; *szMask; ++szMask, ++pData, ++bMask) {
		Data = (BYTE)Process::ReadMemoryByte((LPCVOID)pData, 1);
		if (*szMask == 'x' && Data != *bMask)
			return false;
	}
	return (*szMask) == NULL;
}

//Find Pattern from StartAddress 
DWORD64 Process::FindPattern(DWORD64 dwAddress, DWORD64 dwLen, BYTE* bMask, char* szMask)
{
	for (DWORD i = 0; i < dwLen; i++) {
		if (bDataCompare((DWORD64)(dwAddress + i), bMask, szMask))
			return (DWORD64)(dwAddress + i);
	}
	return 0;
}

// ------------------------------------------------------------------------
// ------------------------Pattern Class Declaration------------------------
// ------------------------------------------------------------------------


class Pattern {

private : 
	Process* ProcAddr;
public:
	Pattern(Process* ProcAddr, PBYTE HexCode, char* Mask);
	PBYTE HexCode;
	char* Mask;
	DWORD64 OffsetAddress;
	DWORD64 ObjectAddress;

	void GetOffsetAddress(int offset);
	void GetObjectAddress(int offset);
};

//Class Constructor
Pattern::Pattern(Process* ProcAddr, PBYTE HexCode, char* Mask) {
	this->ProcAddr = ProcAddr;
	this->HexCode = HexCode;
	this->Mask = Mask;
	this->OffsetAddress = 0;
	this->ObjectAddress = 0;
};

//Find Pattern Offset Address from Process Class's function 
//Argument offset : distance from Opcode start address between offset location  
void Pattern::GetOffsetAddress(int offset) {
	OffsetAddress = ProcAddr->GetOffsetByPattern(HexCode, Mask) + offset;
};

//Find Pattern Object Address from Process Class's function 
//Argument offset : distance from RIP Register between offset location 
void Pattern::GetObjectAddress(int offset) {
	DWORD32 ObjectOffset = ProcAddr->ReadMemoryByte((LPCVOID)OffsetAddress, 4);
	ObjectAddress = OffsetAddress + offset + ObjectOffset;
	if (ObjectOffset >= 0x80000000)
		ObjectAddress -= 0x100000000;
};


// ------------------------------------------------------------------------
// ------------------------Pattern Class Declaration------------------------
// ------------------------------------------------------------------------

//Get Module Base Address by Procesid and modulename 
DWORD64 GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
	DWORD64 modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, modName))
				{
					modBaseAddr = (DWORD64)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}