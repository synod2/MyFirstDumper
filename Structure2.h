#pragma once
#include "memory.h"
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;
DWORD64 Gcount = 1023;
LPWSTR** FnameList[3] = { 0, };
UINT32 OffsetList[1024] = { 0, };

wofstream fout("Dumper.txt");

struct FIntVector
{
	UINT32 X;
	UINT32 Y;
	UINT32 Z;
};

struct FVector
{
	float X;
	float Y;
	float Z;
};


struct UObjectBase {
	DWORD_PTR* vfptr;								//0x00
	DWORD32 ObjectFlags;							//0x08
	DWORD32 Internalindex;							//0x0c
	UObjectBase* ClassPrivate;						//0x10
	DWORD64 NamePrivate;							//0x18
	UObjectBase* OuterPrivate;						//0x20
	DWORD64 ClassPrivateidx;						//0x28
	DWORD64 OuterPrivateidx;						//0x30
};

struct UStruct {
	UObjectBase baseclass;							//0x00
	DWORD64	SuperStruct[2];							//0x40
	DWORD64	Children;								//0x48
	DWORD_PTR* ChildProperties;						//0x50
	DWORD64 PropertiesSize;							//0x58
	DWORD_PTR* MinAlignment;						//0x60
	DWORD_PTR* Script;								//0x68
	DWORD_PTR* PropertyLink;						//0x70
	DWORD_PTR* RefLink;								//0x78
	DWORD_PTR* DestructorLink;						//0x80
	DWORD_PTR* PostConstructLink;					//0x88
	DWORD_PTR* ScriptAndPropertyObjectReferences;	//0x90
	DWORD_PTR* UnresolvedScriptProperties;			//0x98
	DWORD_PTR* UnversionedSchema;					//0xA0
};

struct UWrold {
	UObjectBase	baseclass_0;						//0x00000000
	DWORD_PTR* baseclass_28;						//0x00000028
	DWORD64	PersistentLevel;						//0x00000030
	DWORD64	NetDriver;								//0x00000038
	DWORD64	LineBatcher;							//0x00000040
	DWORD64	PersistentLineBatcher;					//0x00000048
	DWORD64	ForegroundLineBatcher;					//0x00000050
	DWORD64	NetworkManager;							//0x00000058
	DWORD64	PhysicsCollisionHandler;				//0x00000060
	DWORD_PTR* ExtraReferencedObjects[2];			//0x00000068
	DWORD_PTR* PerModuleDataObjects[2];				//0x00000078
	DWORD_PTR* LevelSequenceActors[2];				//0x00000088
	DWORD_PTR* StreamingLevels[2];					//0x00000098
	DWORD_PTR* StreamingLevelsToConsider[5];		//0x000000A8
	DWORD_PTR* StreamingLevelsPrefix[2];			//0x000000D0
	DWORD64	CurrentLevelPendingVisibility;			//0x000000E0
	DWORD64	CurrentLevelPendingInvisibility;		//0x000000E8
	DWORD64	DemoNetDriver;							//0x000000F0
	DWORD64	MyParticleEventManager;					//0x000000F8
	DWORD64	DefaultPhysicsVolume;					//0x00000100
	DWORD_PTR* ViewLocationsRenderedLastFrame[2];	//0x00000108
	BYTE	FeatureLevel;							//0x00000118
	BYTE	TickGroup;								//0x00000119
	BYTE	WorldType;								//0x0000011A
	BYTE	_bf11b;									//0x0000011B
	BYTE	_bf11c;									//0x0000011C
	BYTE	_bf11d;									//0x0000011D
	BYTE	_bf11e;									//0x0000011E
	BYTE	_bf11f;									//0x0000011F
	DWORD64	NavigationSystem;						//0x00000120
	DWORD64	AuthorityGameMode;						//0x00000128
	DWORD64	GameState;								//0x00000130
	DWORD64	AISystem;								//0x00000138
	DWORD64	AvoidanceManager;						//0x00000140
	DWORD_PTR* Levels[2];							//0x00000148
	DWORD_PTR* LevelCollections[2];					//0x00000158
	BYTE	ActiveLevelCollectionIndex;				//0x00000168
	BYTE	_16c;									//0x0000016C
	BYTE	_16d;									//0x0000016D
	BYTE	_16E;									//0x0000016E
	BYTE	_16F;									//0x0000016F
	DWORD_PTR* AudioDeviceHandle[3];				//0x00000170
	DWORD64	OwningGameInstance;						//0x00000188
	DWORD_PTR* ParameterCollectionInstances[2];		//0x00000190
	DWORD64	CanvasForRenderingToTarget;				//0x000001A0
	DWORD64	CanvasForDrawMaterialToRenderTarget;	//0x000001A8
	DWORD64	Scene;									//0x000001B0
	DWORD_PTR* ControllerList[2];					//0x000001B8
	DWORD_PTR* PlayerControllerList[2];				//0x000001C8
	DWORD_PTR* AutoCameraActorList[2];				//0x000001D8
	DWORD_PTR* NonDefaultPhysicsVolumeList[2];		//0x000001E8
	DWORD64	PhysicsScene;							//0x000001F8
	DWORD_PTR* ComponentsThatNeedEndOfFrameUpdate[2];//0x00000200
	DWORD_PTR* ComponentsThatNeedEndOfFrameUpdate_OnGameThread[2];//0x00000210
	DWORD_PTR* AsyncTraceState[25];					//0x00000220
	DWORD_PTR* OnActorSpawned[3];					//0x000002E8
	DWORD64	TimerManager;							//0x00000300
	DWORD_PTR* LatentActionManager[12];				//0x00000308
	DWORD64	BuildStreamingDataTimer;				//0x00000368
	DWORD_PTR* TickDispatchEvent[3];				//0x00000370
	DWORD_PTR* PostTickDispatchEvent[3];			//0x00000388
	DWORD_PTR* TickFlushEvent[3];					//0x000003A0
	DWORD_PTR* PostTickFlushEvent[3];				//0x000003B8
	DWORD_PTR* LevelsChangedEvent[3];				//0x000003D0
	DWORD_PTR* BeginTearingDownEvent[3];			//0x000003E8
	DWORD_PTR* URL[13];								//0x00000400
	DWORD64	FXSystem;								//0x00000468
	DWORD64	TickTaskLevel;							//0x00000470
	DWORD_PTR* StartPhysicsTickFunction[6];			//0x00000478
	DWORD_PTR* EndPhysicsTickFunction[6];			//0x000004A8
	UINT32	PlayerNum;								//0x000004D8
	UINT32	StreamingVolumeUpdateDelay;				//0x000004DC
	DWORD_PTR* OnBeginPostProcessSettings[3];		//0x000004E0
	DWORD_PTR* PostProcessVolumes[2];				//0x000004F8
	DWORD_PTR* AudioVolumes[2];						//0x00000508
	DWORD64	LastTimeUnbuiltLightingWasEncountered;	//0x00000518
	UINT32	TimeSeconds;							//0x00000520
	UINT32	UnpausedTimeSeconds;					//0x00000524
	UINT32	RealTimeSeconds;						//0x00000528
	UINT32	AudioTimeSeconds;						//0x0000052C
	UINT32	DeltaTimeSeconds;						//0x00000530
	UINT32	PauseDelay;								//0x00000534
	FIntVector	OriginLocation;						//0x00000538
	FIntVector	RequestedOriginLocation;			//0x00000544
	FVector	OriginOffsetThisFrame;					//0x00000550
	UINT32	NextSwitchCountdown;					//0x0000055C
	DWORD64	WorldComposition;						//0x00000560
	BYTE	FlushLevelStreamingType;				//0x00000568
	BYTE	NextTravelType;							//0x00000569
	UINT16	NumStreamingLevelsBeingLoaded;			//0x0000056A
	BYTE	_56c;									//0x0000056C
	BYTE	_56d;									//0x0000056D
	BYTE	_56E;									//0x0000056E
	BYTE	_56F;									//0x0000056F
	DWORD_PTR* NextURL[2];							//0x00000570
	DWORD_PTR* PreparingLevelNames[2];				//0x00000580
	DWORD_PTR* CommittedPersistentLevelName;		//0x00000590
	UINT32	_bf598;									//0x00000598
	UINT32	CleanupWorldTag;						//0x0000059C
	DWORD64	PerfTrackers;							//0x000005A0
	DWORD_PTR* OnActorsInitialized[3];				//0x000005A8
	DWORD_PTR* OnWorldBeginPlay[3];					//0x000005C0
	DWORD_PTR* GameStateSetEvent[5];				//0x000005D8
	DWORD_PTR* PSCPool[11];							//0x000005F0
	DWORD_PTR* SubsystemCollection[25];				//0x00000648
};

struct FField {
	DWORD_PTR* vfptr;								//0x00
	UObjectBase* ClassPrivate;						//0x08
	DWORD64 Owner[2]; 								//0x10
	FField* Next;									//0x20
	DWORD64 NamePrivate;							//0x28
	DWORD64 FlagsPrivate;							//0x30
};

struct FProperty {
	FField baseclass_0; 							//0x00
	UINT32 ArrayDim; 								//0x38
	UINT32  ElementSize; 							//0x3C
	DWORD64 PropertyFlags;  						//0x40
	UINT16 RepIndex; 								//0x48
	BYTE BlueprintReplicationCondition; 			//0x4A
	BYTE undefined; 								//0x4B
	UINT32 Offset_Internal; 						//0x4C
	DWORD64 RepNotifyFunc; 							//0x50
	DWORD64 PropertyLinkNext; 						//0x58
	DWORD64 NextRef; 								//0x60 
	DWORD64 DestructorLinkNext; 					//0x68 
	DWORD64 PostConstructLinkNext; 					//0x70
};


class GUObjectArray {
private:
	Process* Proc;
	LPVOID Objects;
	DWORD64 FUObjectItem;
	DWORD64 FNamePoolAddr;
	UINT32 NumElement;

public:
	GUObjectArray(Process* Proc, DWORD64 ObjectAddress, DWORD64 FNamePoolAddr);
	DWORD64 GetNamePrivate(DWORD64 idx);
	void GetObjBase(DWORD64 idx, UObjectBase* ObjBase);
	void MakeObjArray(UStruct* ObjBase);
	void GetFName(UStruct* ObjBase);
	void MakeName(DWORD64 ID, DWORD64 idx, LPWSTR** list);
	void MakeName(DWORD64 ID);
};


//Constructor
GUObjectArray::GUObjectArray(Process* Proc, DWORD64 ObjectAddress, DWORD64 FNamePoolAddr) {
	this->Objects = (LPVOID)Proc->ReadMemoryByte((LPVOID)(ObjectAddress + 0x10), 8);
	this->FUObjectItem = (DWORD64)Proc->ReadMemoryByte(Objects, 8);
	this->NumElement = (UINT32)Proc->ReadMemoryByte((LPVOID)(ObjectAddress + 0x24), 4);
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
	ObjBase->ClassPrivate = (UObjectBase*)Proc->ReadMemoryByte((LPVOID)((DWORD64)resAddr + 0x10), 8);
	ObjBase->NamePrivate = Proc->ReadMemoryByte((LPVOID)((DWORD64)resAddr + 0x18), 8);
	ObjBase->OuterPrivate = (UObjectBase*)Proc->ReadMemoryByte((LPVOID)((DWORD64)resAddr + 0x20), 8);
	if (ObjBase->ClassPrivate != 0)
		ObjBase->ClassPrivateidx = Proc->ReadMemoryByte((LPVOID)((DWORD64)ObjBase->ClassPrivate + 0x18), 8);
	else
		ObjBase->ClassPrivateidx = 0;
	if (ObjBase->OuterPrivate != 0)
		ObjBase->OuterPrivateidx = Proc->ReadMemoryByte((LPVOID)((DWORD64)ObjBase->OuterPrivate + 0x18), 8);
	else
		ObjBase->OuterPrivateidx = 0;
	((UStruct*)ObjBase)->ChildProperties = (DWORD_PTR*)Proc->ReadMemoryByte((LPVOID)((DWORD64)resAddr + 0x50), 8);
}

//Repeatable Function 
void GUObjectArray::MakeObjArray(UStruct* ObjBase) {
	Gcount = NumElement;
	FnameList[0] = new LPWSTR * [Gcount];
	FnameList[1] = new LPWSTR * [Gcount];
	FnameList[2] = new LPWSTR * [Gcount];
	printf(" GCount : %d", Gcount);
	for (int i = 0; i != Gcount; i++) {
		GetObjBase(i, &ObjBase[i].baseclass);
	}
}


void GUObjectArray::GetFName(UStruct* ObjBase) {
	DWORD64 ID, Block, Offset, PoolBase, NameAddr, Len = 0;
	DWORD FNameEntryHeader = 0;
	bool bisWide = 0;
	char tmpstr[256] = "";

	for (int i = 0; i != Gcount; i++) {
		//make NamePrivate
		fout << "[0x";
		fout.fill('0');
		fout.width(8);
		fout << hex << i;
		fout << "] ";
		MakeName(ObjBase[i].baseclass.ClassPrivateidx, i, FnameList[0]);
		MakeName(ObjBase[i].baseclass.OuterPrivateidx, i, FnameList[1]);
		MakeName(ObjBase[i].baseclass.NamePrivate, i, FnameList[2]);
		/*ObjBase->ClassPrivate->NamePrivate;*/

		//Get Offset_Internal
		fout << endl;
		if (ObjBase[i].baseclass.ObjectFlags == 67) {

			if (ObjBase[i].ChildProperties) {

				FField* firstEntry = (FField*)ObjBase[i].ChildProperties;
				FField* PropertyEntry = firstEntry;
				int count = 0;
				//Get All SubPropety Entry 
				while (PropertyEntry) {
					UINT32 Offset = Proc->ReadMemoryByte((LPVOID)((DWORD64)PropertyEntry + 0x4C), 4);
					DWORD64 NameID = Proc->ReadMemoryByte((LPVOID)((DWORD64)PropertyEntry + 0x28), 4);
					UObjectBase* ClassPrivate = (UObjectBase*)Proc->ReadMemoryByte((LPVOID)((DWORD64)PropertyEntry + 0x8), 8);
					DWORD64 ClassPrivateidx = Proc->ReadMemoryByte((LPVOID)((DWORD64)ClassPrivate), 8);

					MakeName(ClassPrivateidx);
					MakeName(NameID);

					fout << "\t\t\t\t// Offset : " << setbase(16) << Offset << endl;
					PropertyEntry = (FField*)Proc->ReadMemoryByte((LPVOID)((DWORD64)PropertyEntry + 0x20), 8);
				}
			}
		}
	}
}

void GUObjectArray::MakeName(DWORD64 ID) {
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
	char* tmp = new char[Len + 1]{ '\0', };
	for (int j = 0; j != Len; j++) {
		char temp = (BYTE)Proc->ReadMemoryByte((LPVOID)((DWORD64)NameAddr + 2 + j), 1);
		memcpy(tmp + j, &temp, 1);
	}
	/*printf("\t%s",tmp);*/
	fout << "\t\t" << tmp;
	delete[] tmp;
}

void GUObjectArray::MakeName(DWORD64 ID, DWORD64 idx, LPWSTR** list) {
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
	if (tmp == NULL)
		memcpy(tmp, "", Len + 1);
	fout << tmp << "\t";
	memcpy(list[idx], tmp, Len + 1);
	delete[] tmp;
}