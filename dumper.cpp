#include "dumper.h"
#include "Structure.h"

UObjectBase GObjBase[1024] = { 0, };

int main() {
	LPCSTR ProcessName = "UnrealWindow";
	LPWSTR ModuleName = (LPWSTR)L"FpsProject-Win64-Shipping.exe";
	Process newProc = Process(ProcessName,ModuleName);
	Pattern GUObject = Pattern(&newProc,(PBYTE)"\x44\x8B\x54\x24\x50\x48\x8D\x05\x00\x00\x00\x00\x33\xF6", (char*)"xxxxxxxx????xx");
	Pattern FNamePool = Pattern(&newProc,(PBYTE)"\x0F\xB7\xC3\x89\x74\x24\x30\x89\x44\x24\x34\x74\x09\x4C\x8D\x05\x00\x00\x00\x00", (char*)"xxxxxxxxxxxxxxxx????");
	

	GUObject.GetOffsetAddress(8);
	GUObject.GetObjectAddress(4);
	printf("GUObject : %016llX\n", GUObject.ObjectAddress);

	FNamePool.GetOffsetAddress(16);
	FNamePool.GetObjectAddress(4);
	printf("FNamePool : %016llX\n", FNamePool.ObjectAddress);
	
	GUObjectArray objr = GUObjectArray(&newProc, GUObject.ObjectAddress, FNamePool.ObjectAddress);
	objr.MakeObjArray(GObjBase);
	objr.GetFName(GObjBase);
	for (int i = 0; i != Gcount; i++) {
		printf("%s \t %s \t %s \n", FnameList[0][i],FnameList[1][i], FnameList[2][i]);
		/*printf("Fname : %s \n", FnameList1[i]);*/
	}

	/*FNamePool.ObjectAddress = FNamePool.OffsetAddress + 4 + newProc.ReadMemoryByte((LPCVOID)FNamePool.OffsetAddress, 4);*/

}
