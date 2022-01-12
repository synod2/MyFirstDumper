#include "Structure.h"

UStruct GObjBase[1024] = { 0, };

int main() {
	LPCSTR ProcessName = "UnrealWindow";
	LPWSTR ModuleName = (LPWSTR)L"FpsProject-Win64-Shipping.exe";
	Process newProc = Process(ProcessName,ModuleName);
	Pattern GUObject = Pattern(&newProc,(PBYTE)"\x44\x8B\x54\x24\x50\x48\x8D\x05\x00\x00\x00\x00\x33\xF6", (char*)"xxxxxxxx????xx");
	Pattern FNamePool = Pattern(&newProc,(PBYTE)"\x0F\xB7\xC3\x89\x74\x24\x30\x89\x44\x24\x34\x74\x09\x4C\x8D\x05\x00\x00\x00\x00", (char*)"xxxxxxxxxxxxxxxx????");
	Pattern GWorld = Pattern(&newProc, (PBYTE)"\x33\xC9\x48\x89\x0D\x00\x00\x00\x00\x8B\xD9\x49\x8B\xBF\x80\x00\x00\x00", (char*)"xxxxx????xxxxxxxxx");
	

	GUObject.GetOffsetAddress(8);
	GUObject.GetObjectAddress(4);
	printf("GUObject : %016llX\n", GUObject.ObjectAddress);

	FNamePool.GetOffsetAddress(16);
	FNamePool.GetObjectAddress(4);
	printf("FNamePool : %016llX\n", FNamePool.ObjectAddress);

	GWorld.GetOffsetAddress(5);
	GWorld.GetObjectAddress(4);
	printf("GWorld : %016llX\n", GWorld.ObjectAddress);
	
	UOArray::GUObjectArray objr = UOArray::GUObjectArray(&newProc, GUObject.ObjectAddress, FNamePool.ObjectAddress);
	/*objr.MakeObjArray(GObjBase);
	objr.GetFName(GObjBase);*/
	AArray::AActorArray uoar = AArray::AActorArray(&newProc, GUObject.ObjectAddress, FNamePool.ObjectAddress, (PVOID)GWorld.ObjectAddress);	
		
}
