#pragma once
#include "memory.h"
#include <string>

LPWSTR* FnameList[3][1024] = { 0, };
DWORD64 Gcount = 100;


struct UObjectBase {
	DWORD_PTR* vfptr;				//0x00
	DWORD32 ObjectFlags;			//0x08
	DWORD32 Internalindex;			//0x0c
	UObjectBase* ClassPrivate;		//0x10
	DWORD64 NamePrivate;			//0x18
	UObjectBase* OuterPrivate;			//0x20
	DWORD64 ClassPrivateidx;
	DWORD64 OuterPrivateidx;
} ;

class GUObjectArray {
private : 
	Process* Proc;
	LPVOID Objects;
	DWORD64 FUObjectItem;
	DWORD64 FNamePoolAddr;

public:
	GUObjectArray(Process* Proc, DWORD64 ObjectAddress, DWORD64 FNamePoolAddr);
	DWORD64 GetNamePrivate(DWORD64 idx);
	void GetObjBase(DWORD64 idx, UObjectBase* ObjBase);
	void MakeObjArray(UObjectBase* ObjBase);
	void GetFName(UObjectBase* ObjBase);
	void MakeName(DWORD64 ID, DWORD64 idx, LPWSTR** list);
};


//Constructor
GUObjectArray::GUObjectArray(Process* Proc, DWORD64 ObjectAddress, DWORD64 FNamePoolAddr) {
	this->Objects = (LPVOID)Proc->ReadMemoryByte((LPVOID)(ObjectAddress + 0x10), 8);
	this->FUObjectItem = (DWORD64)Proc->ReadMemoryByte(Objects, 8);
	this->Proc = Proc;
	this->FNamePoolAddr = FNamePoolAddr;
}

//Make UObjectBase Structure
void GUObjectArray::GetObjBase(DWORD64 idx, UObjectBase* ObjBase) {
	LPVOID resAddr = (LPVOID)(idx * 0x18 + FUObjectItem);
	resAddr = (LPVOID)Proc->ReadMemoryByte(resAddr, 8);
	ObjBase->vfptr = (DWORD_PTR*)Proc->ReadMemoryByte((LPVOID)((DWORD64)resAddr), 8);
	ObjBase->ObjectFlags = Proc->ReadMemoryByte((LPVOID)((DWORD64)resAddr + 0x8), 4);
	ObjBase->Internalindex = Proc->ReadMemoryByte((LPVOID)((DWORD64)resAddr + 0xC), 4);
	ObjBase->ClassPrivate = (UObjectBase *)Proc->ReadMemoryByte((LPVOID)((DWORD64)resAddr + 0x10), 8);
	ObjBase->NamePrivate = Proc->ReadMemoryByte((LPVOID)((DWORD64)resAddr + 0x18), 8);
	ObjBase->OuterPrivate = (UObjectBase*)Proc->ReadMemoryByte((LPVOID)((DWORD64)resAddr + 0x20), 8);
	if (ObjBase->ClassPrivate != 0)
		ObjBase->ClassPrivateidx = Proc->ReadMemoryByte((LPVOID)((DWORD64)ObjBase->ClassPrivate + 0x18), 8);
	else
		ObjBase->ClassPrivateidx = 0;
	if (ObjBase->OuterPrivate != 0)
		ObjBase->OuterPrivateidx = Proc->ReadMemoryByte((LPVOID)((DWORD64)ObjBase->OuterPrivate +0x18), 8);
	else
		ObjBase->OuterPrivateidx = 0;
}

//Repeatable Function 
void GUObjectArray::MakeObjArray(UObjectBase* ObjBase) {
	for (int i = 0; i != Gcount; i++) {
		GetObjBase(i, &ObjBase[i]);
	}	
}


void GUObjectArray::GetFName(UObjectBase* ObjBase) {
	DWORD64 ID,Block,Offset,PoolBase,NameAddr,Len = 0;
	DWORD FNameEntryHeader = 0;
	bool bisWide = 0;
	
	for (int i = 0; i != Gcount; i++) {
		//make NamePrivate
		MakeName(ObjBase[i].ClassPrivateidx, i, FnameList[0]);
		MakeName(ObjBase[i].OuterPrivateidx, i, FnameList[1]);
		MakeName(ObjBase[i].NamePrivate,i,FnameList[2]);				
		/*ObjBase->ClassPrivate->NamePrivate;*/
	}
}

void GUObjectArray::MakeName(DWORD64 ID,DWORD64 idx, LPWSTR** list) {
	DWORD64 Block, Offset, PoolBase, NameAddr, Len = 0;
	DWORD FNameEntryHeader = 0;
	bool bisWide = 0;

	if (ID == 0)
		return;

	Block = ID >> 16;
	Offset = ID & 65535;
	PoolBase = FNamePoolAddr + 0x10 + Block * 8;
	NameAddr = Proc->ReadMemoryByte((LPVOID)PoolBase, 8) + 2 * Offset;

	FNameEntryHeader = Proc->ReadMemoryByte((LPVOID)NameAddr, 2);
	bisWide = FNameEntryHeader & 1;
	if (bisWide == 0)
		Len = FNameEntryHeader >> 6;
	else
		Len = (FNameEntryHeader >> 6) * 2;
	list[idx] = new LPWSTR[Len + 1]{ 0, };
	char* tmp = new char[Len + 1]{ '\0', };
	for (int j = 0; j != Len; j++) {
		char temp = (BYTE)Proc->ReadMemoryByte((LPVOID)((DWORD64)NameAddr + 2 + j), 1);
		memcpy(tmp + j, &temp, 1);
	}
	memcpy(list[idx], tmp, Len+1);
	delete[] tmp;
}

