/************************************************************************************/
/*Project: Whammy Bombs - WAM                                                       */
/*----------------------------------------------------------------------------------*/
/*                             UWAMGameInterface                                    */
/*----------------------------------------------------------------------------------*/
/*Description:                                                                      */
/*The WAMGameInterface Objects and Structs are the main communication pipeline      */
/*between the Low-Level Game Functionalities and the High-Level part of the project */
/*With this main interface we can code the High Level part using simple game dev    */
/*concepts and decrease the size of blueprints necessary to develop such game       */
/*For example: All Unreal functionalities runs its functionalities using a event    */
/*based core, and its difficult have single update point for the update/change game */
/*rules since all this objects are managed by Unreal itself.                        */
/*With this interface we can intercomunicate the Unreal with the low level core     */
/*with the benefit of extend the blueprint code with custom functions and structures*/
/*----------------------------------------------------------------------------------*/
/*Author: William D. Wolff - 2018                                                   */
/************************************************************************************/
#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "WAMGameCoreControl.h"
#include "WAMGameMapData.h"
#include "WAMGameInterface.generated.h"

UENUM(BlueprintType, Category = "WAMGameInterface|WAM Game Enums")		//"BlueprintType" is essential to include
enum class EBlockTypeEnum : uint8
{
	VE_Empty 	     UMETA(DisplayName = "Empty"),
	VE_Blocked       UMETA(DisplayName = "Blocked"),
	VE_Destructible  UMETA(DisplayName = "Destructible"),
	VE_SpawnP1       UMETA(DisplayName = "SpawnP1"),
	VE_SpawnP2       UMETA(DisplayName = "SpawnP2"),
	VE_Bomb          UMETA(DisplayName = "Bomb"),
	VE_Explosion     UMETA(DisplayName = "Explosion"),
	VE_Enemy         UMETA(DisplayName = "Enemy"),
	VE_Flag          UMETA(DisplayName = "Flag")
};

UENUM(BlueprintType, Category = "WAMGameInterface|WAM Game Enums")		//"BlueprintType" is essential to include
enum class EActorTypeEnum : uint8
{
	VE_Bomb 	 UMETA(DisplayName = "Bomb"     ),
	VE_Player01  UMETA(DisplayName = "Player 01"),
	VE_Player02  UMETA(DisplayName = "Player 02"),
	VE_Enemy     UMETA(DisplayName = "Enemy"    ),
	VE_Explosion UMETA(DisplayName = "Explosion"),
	VE_DBlock    UMETA(DisplayName = "Destructible Block"),
	VE_Flag      UMETA(DisplayName = "Target Flag")
};

USTRUCT(BlueprintType, Category = "WAMGameInterface|WAM Game Structs")
struct FWAMActorStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WAMGameInterface|WAM Game Structs")
	FVector        vWAM_ActorPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WAMGameInterface|WAM Game Structs")
	EActorTypeEnum eWAMActorType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WAMGameInterface|WAM Game Structs")
	int            iWAM_ActorState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WAMGameInterface|WAM Game Structs")
    int            iWAM_ActorMunition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WAMGameInterface|WAM Game Structs")
	int            iWAM_ActorProtection;
};

USTRUCT(BlueprintType, Category = "WAMGameInterface|WAM Game Structs")
struct FWAMBlockStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WAMGameInterface|WAM Game Structs")
	FVector        vWAM_Position;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WAMGameInterface|WAM Game Structs")
	EBlockTypeEnum eWAMBlockType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WAMGameInterface|WAM Game Structs")
	int            iWAM_HidenItem;
};

USTRUCT(BlueprintType, Category = "WAMGameInterface|WAM Game Structs")
struct FWAMGameStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WAMGameInterface|WAM Game Structs")
	TArray<FWAMBlockStruct> vWAM_MapBlocks;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WAMGameInterface|WAM Game Structs")
	FWAMActorStruct         sWAMPlayer01;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WAMGameInterface|WAM Game Structs")
	FWAMActorStruct         sWAMPlayer02;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WAMGameInterface|WAM Game Structs")
	UTexture2D              *tWAMMapTexture = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WAMGameInterface|WAM Game Structs")
	TArray<UDataTable*>     tWAMMapDataTableArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WAMGameInterface|WAM Game Structs")
    FVector                  tWAMMapCenter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WAMGameInterface|WAM Game Structs")
	int                      tWAMMapSize;
};
/**
 * 
 */
UCLASS()
class WAM_API UWAMGameInterface : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/**************************************************************************/
	/*Starts all necessary objects in the core of the game                    */
	/**************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "WAMGameInterface|WAM Game Functions")
	static bool WAMBuildCoreGameObjects(FWAMGameStruct pWAMGameStruct)
	{
		//Build the game without TextureMap
		//pWAMGameCore    = new WAMGameCoreControl();

		//Build the Map with a DataTable
		if (pWAMGameStruct.tWAMMapDataTableArray.Num() > 0)
		{ 
			pWAMGameCore = new WAMGameCoreControl(pWAMGameStruct.tWAMMapDataTableArray[0], pWAMGameStruct.tWAMMapSize);
			pWAMGameStruct.tWAMMapCenter = pWAMGameCore->GetCenterMap();
		}

		
		//Build the Game with a Texture Map
		/*
		if (!pWAMGameStruct.tWAMMapTexture)
		{
			pWAMGameCore = new WAMGameCoreControl(pWAMGameStruct.tWAMMapTexture);
		}
		
		*/

		return true;
	}

	/**************************************************************************/
	/*destroy all necessary objects in the core of the game                   */
	/**************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "WAMGameInterface|WAM Game Functions")
	static bool WAMDestroyCoreGameObjects() { return true; }
	/**************************************************************************/
	/*Update the desired Game Map Block                                       */
	/**************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "WAMGameInterface|WAM Game Functions")
	static bool WAMUpdateBlock(FWAMBlockStruct pWAMUpdatedBlock) 
	{
		WAMGameMapNode* tUpdatedMapNode;
		int             tBlockType= WAM_BLOCK_TYPE_FREE;

		//convert the block type.
		if (pWAMUpdatedBlock.eWAMBlockType == EBlockTypeEnum::VE_Destructible)tBlockType = WAM_BLOCK_TYPE_DESTR;
		if (pWAMUpdatedBlock.eWAMBlockType == EBlockTypeEnum::VE_Blocked)tBlockType = WAM_BLOCK_TYPE_BLOCK;
		if (pWAMUpdatedBlock.eWAMBlockType == EBlockTypeEnum::VE_Empty)tBlockType = WAM_BLOCK_TYPE_FREE;
		if (pWAMUpdatedBlock.eWAMBlockType == EBlockTypeEnum::VE_SpawnP1)tBlockType = WAM_BLOCK_TYPE_SPAWN_P1;
		if (pWAMUpdatedBlock.eWAMBlockType == EBlockTypeEnum::VE_SpawnP2)tBlockType = WAM_BLOCK_TYPE_SPAWN_P2;
		if (pWAMUpdatedBlock.eWAMBlockType == EBlockTypeEnum::VE_Bomb)tBlockType = WAM_BLOCK_TYPE_BOMB;
		if (pWAMUpdatedBlock.eWAMBlockType == EBlockTypeEnum::VE_Explosion)tBlockType = WAM_BLOCK_TYPE_EXPLOSION;
		if (pWAMUpdatedBlock.eWAMBlockType == EBlockTypeEnum::VE_Enemy)tBlockType = WAM_BLOCK_TYPE_ENEMY;
		if (pWAMUpdatedBlock.eWAMBlockType == EBlockTypeEnum::VE_Flag)tBlockType = WAM_BLOCK_TYPE_FLAG;
		
		tUpdatedMapNode = new WAMGameMapNode(pWAMUpdatedBlock.vWAM_Position, tBlockType, pWAMUpdatedBlock.iWAM_HidenItem);

		//when we have an update from the interface means the node are being updated after a change...
		tUpdatedMapNode->bWAM_Updated = false;

		pWAMGameCore->UpdateBlock(tUpdatedMapNode);
		return true; 
	}
	/**************************************************************************/
	/*Get a Player Struct based on the player index                           */
	/**************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "WAMGameInterface|WAM Game Functions")
	static FWAMActorStruct WAMGetPlayer(int pWAMPlayerId)
	{ 
		FWAMActorStruct tPlayerStruct;
		WAMGamePlayer*  tPlayer;

		switch (pWAMPlayerId)
		{
		case 0:
		{
			tPlayer = pWAMGameCore->GetPlayer(pWAMPlayerId);
			tPlayerStruct.vWAM_ActorPosition = tPlayer->GetLocation();
			tPlayerStruct.iWAM_ActorState = tPlayer->GetState();
			tPlayerStruct.iWAM_ActorMunition = tPlayer->GetMunition();
			tPlayerStruct.iWAM_ActorProtection = tPlayer->GetProtection();
			tPlayerStruct.eWAMActorType = EActorTypeEnum::VE_Player01;
		}break;
		case 1:
		{
			tPlayer = pWAMGameCore->GetPlayer(pWAMPlayerId);
			tPlayerStruct.vWAM_ActorPosition = tPlayer->GetLocation();
			tPlayerStruct.iWAM_ActorState = tPlayer->GetState();
			tPlayerStruct.iWAM_ActorMunition = tPlayer->GetMunition();
			tPlayerStruct.iWAM_ActorProtection = tPlayer->GetProtection();
			tPlayerStruct.eWAMActorType = EActorTypeEnum::VE_Player02;
		}break;
		}

		return tPlayerStruct;
	}

	/**************************************************************************/
	/*Get a Player Struct based on the player index                           */
	/**************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "WAMGameInterface|WAM Game Functions")
		static FWAMGameStruct WAMGetGameObjects(bool &pWAMValidOperation)
	{
		FWAMGameStruct tGameStruct;
		WAMGamePlayer* tPlayer;

		pWAMValidOperation = true;

		tPlayer = pWAMGameCore->GetPlayer(0);

		tGameStruct.sWAMPlayer01.vWAM_ActorPosition = tPlayer->GetLocation();
		tGameStruct.sWAMPlayer01.iWAM_ActorState = tPlayer->GetState();
		tGameStruct.sWAMPlayer01.eWAMActorType = EActorTypeEnum::VE_Player01;

		tPlayer = pWAMGameCore->GetPlayer(1);
		tGameStruct.sWAMPlayer02.vWAM_ActorPosition = tPlayer->GetLocation();
		tGameStruct.sWAMPlayer02.iWAM_ActorState = tPlayer->GetState();
		tGameStruct.sWAMPlayer02.eWAMActorType = EActorTypeEnum::VE_Player02;

		//Here will be included all updated blocks and actors updated!!!
		TArray<WAMGameMapNode*> tBlocks;
		tBlocks = pWAMGameCore->GetMapNodes();

		if (tBlocks.Num() > 0)pWAMBlockList.Empty();

		for (int i = 0; i < tBlocks.Num(); i++)
		{
			FWAMBlockStruct tBlockStruct;

			tBlockStruct.vWAM_Position = tBlocks[i]->vWAM_Position;
			tBlockStruct.iWAM_HidenItem = tBlocks[i]->pWAM_Block->iWAM_HidenItem;

			switch (tBlocks[i]->pWAM_Block->iWAM_BlockType)
			{
			case WAM_BLOCK_TYPE_DESTR: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_Destructible; }break;
			case WAM_BLOCK_TYPE_BLOCK: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_Blocked; }break;
			case WAM_BLOCK_TYPE_FREE: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_Empty; }break;
			case WAM_BLOCK_TYPE_SPAWN_P1: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_SpawnP1; }break;
			case WAM_BLOCK_TYPE_SPAWN_P2: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_SpawnP2; }break;
			case WAM_BLOCK_TYPE_BOMB: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_Bomb; }break;
			case WAM_BLOCK_TYPE_EXPLOSION: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_Explosion; }break;
			case WAM_BLOCK_TYPE_ENEMY: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_Enemy; }break;
			case WAM_BLOCK_TYPE_FLAG: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_Flag; }break;
			}

			pWAMBlockList.Add(tBlockStruct);
		}

		//copy the map to the main game struct
		tGameStruct.vWAM_MapBlocks = pWAMBlockList;
		tGameStruct.tWAMMapCenter  = pWAMGameCore->GetCenterMap();

		return tGameStruct;
	}
	/**************************************************************************/
	/*Move a player in the desired direction                                  */
	/**************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "WAMGameInterface|WAM Game Functions")
    static FWAMActorStruct WAMMovePlayer(int pWAMPlayerId, int pWAMDirection , bool &pWAMValidMove)
	{
		FWAMActorStruct tPlayerStruct;
		WAMGamePlayer*  tPlayer;

		pWAMValidMove = pWAMGameCore->MovePlayer(pWAMPlayerId, pWAMDirection);
		if (pWAMValidMove)
		{
			switch (pWAMPlayerId)
			{
			case 0: 
			{
				tPlayer= pWAMGameCore->GetPlayer(pWAMPlayerId); 
				tPlayerStruct.vWAM_ActorPosition = tPlayer->GetLocation();
				tPlayerStruct.iWAM_ActorState    = tPlayer->GetState();
				tPlayerStruct.eWAMActorType      = EActorTypeEnum::VE_Player01;
			}break;
			case 1: 
			{
				tPlayer = pWAMGameCore->GetPlayer(pWAMPlayerId);
				tPlayerStruct.vWAM_ActorPosition = tPlayer->GetLocation();
				tPlayerStruct.iWAM_ActorState = tPlayer->GetState();
				tPlayerStruct.eWAMActorType = EActorTypeEnum::VE_Player02;
			}break;
			}
		}
		
		return tPlayerStruct;
	}

	/**************************************************************************/
	/*Move a player in the desired direction                                  */
	/**************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "WAMGameInterface|WAM Game Functions")
	static FWAMActorStruct WAMThrowBomb(int pWAMPlayerId, bool &pWAMValidMove)
	{
		FWAMActorStruct tPlayerStruct;
		WAMGamePlayer*  tPlayer;

		pWAMValidMove = pWAMGameCore->ThrowBomb(pWAMPlayerId);
		if (pWAMValidMove)
		{
			switch (pWAMPlayerId)
			{
			case 0:
			{
				tPlayer = pWAMGameCore->GetPlayer(pWAMPlayerId);
				tPlayerStruct.vWAM_ActorPosition = tPlayer->GetLocation();
				tPlayerStruct.iWAM_ActorState = tPlayer->GetState();
				tPlayerStruct.eWAMActorType = EActorTypeEnum::VE_Player01;
			}break;
			case 1:
			{
				tPlayer = pWAMGameCore->GetPlayer(pWAMPlayerId);
				tPlayerStruct.vWAM_ActorPosition = tPlayer->GetLocation();
				tPlayerStruct.iWAM_ActorState = tPlayer->GetState();
				tPlayerStruct.eWAMActorType = EActorTypeEnum::VE_Player02;
			}break;
			}
		}

		return tPlayerStruct;
	}

	/**************************************************************************/
	/*Trow an Explosion in the desired Location                               */
	/**************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "WAMGameInterface|WAM Game Functions")
	static TArray<FWAMBlockStruct> WAMThrowExplosion(FVector pWAMBombLocation, bool &pWAMValidMove)
	{
		TArray<FWAMBlockStruct> tImpactedBlocks;
		FWAMActorStruct tActorHit;
		
		
		//Clean-up the impacted blocks
		tImpactedBlocks.Empty();

		pWAMValidMove = pWAMGameCore->ThrowExplosion(pWAMBombLocation);
		if (pWAMValidMove)
		{
			//Here will be included all updated blocks and actors updated!!!
			TArray<WAMGameMapNode*> tBlocks;

			tBlocks = pWAMGameCore->GetImpactedNodes();

			for (int i = 0; i < tBlocks.Num(); i++)
			{
				FWAMBlockStruct tBlockStruct;

				//if we have a impacted block...just add it to the list.
				if (tBlocks[i]->pWAM_Block->iWAM_Impacted)
				{
					tBlockStruct.vWAM_Position = tBlocks[i]->vWAM_Position;
					tBlockStruct.iWAM_HidenItem = tBlocks[i]->pWAM_Block->iWAM_HidenItem;

					switch (tBlocks[i]->pWAM_Block->iWAM_BlockType)
					{
					case WAM_BLOCK_TYPE_DESTR: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_Destructible; }break;
					case WAM_BLOCK_TYPE_BLOCK: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_Blocked; }break;
					case WAM_BLOCK_TYPE_FREE: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_Empty; }break;
					case WAM_BLOCK_TYPE_SPAWN_P1: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_SpawnP1; }break;
					case WAM_BLOCK_TYPE_SPAWN_P2: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_SpawnP2; }break;
					case WAM_BLOCK_TYPE_BOMB: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_Bomb; }break;
					case WAM_BLOCK_TYPE_EXPLOSION: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_Explosion; }break;
					case WAM_BLOCK_TYPE_ENEMY: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_Enemy; }break;
					case WAM_BLOCK_TYPE_FLAG: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_Flag; }break;
					}
					
					tImpactedBlocks.Add(tBlockStruct);
				}
			}
		}
		//we set valid move only if kill something!!! Yey!!
		if (tImpactedBlocks.Num() == 0)pWAMValidMove = false;

		return tImpactedBlocks;
	}

	/**************************************************************************/
	/*Find a path in the map                                                  */
	/**************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "WAMGameInterface|WAM Game Functions")
	static TArray<FWAMBlockStruct> WAMFindPath(FVector pWAMBegin, FVector pWAMEnd, bool &pWAMValidMove)
	{
		TArray<FWAMBlockStruct> tPathBlocks;
		//Here will be included all updated blocks and actors updated!!!
		TArray<WAMGameMapNode*> tBlocks;
		//Clean-up the impacted blocks
		tPathBlocks.Empty();
		tBlocks.Empty();

		tBlocks = pWAMGameCore->FindPath(pWAMBegin, pWAMEnd);
		if (tBlocks.Num()>0)
		{
			for (int i = 0; i < tBlocks.Num(); i++)
			{
				FWAMBlockStruct tBlockStruct;

				tBlockStruct.vWAM_Position = tBlocks[i]->vWAM_Position;
				tBlockStruct.iWAM_HidenItem = tBlocks[i]->pWAM_Block->iWAM_HidenItem;

				switch (tBlocks[i]->pWAM_Block->iWAM_BlockType)
				{
				case WAM_BLOCK_TYPE_DESTR: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_Destructible; }break;
				case WAM_BLOCK_TYPE_BLOCK: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_Blocked; }break;
				case WAM_BLOCK_TYPE_FREE: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_Empty; }break;
				case WAM_BLOCK_TYPE_SPAWN_P1: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_SpawnP1; }break;
				case WAM_BLOCK_TYPE_SPAWN_P2: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_SpawnP2; }break;
				case WAM_BLOCK_TYPE_BOMB: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_Bomb; }break;
				case WAM_BLOCK_TYPE_EXPLOSION: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_Explosion; }break;
				case WAM_BLOCK_TYPE_ENEMY: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_Enemy; }break;
				case WAM_BLOCK_TYPE_FLAG: {tBlockStruct.eWAMBlockType = EBlockTypeEnum::VE_Flag; }break;
				}

				tPathBlocks.Add(tBlockStruct);
			}
		}
		//we set valid move only if kill something!!! Yey!!
		if (tPathBlocks.Num() == 0)pWAMValidMove = false;
		if (tPathBlocks.Num() >  0)pWAMValidMove = true ;
        
		return tPathBlocks;
	}

	/**************************************************************************/
	/*Find a path in the map                                                  */
	/**************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "WAMGameInterface|WAM Game Functions")
	static FWAMBlockStruct WAMGetRandomFlag(bool &pWAMValidMove)
	{
		FWAMBlockStruct tFlagBlock;
		WAMGameMapNode* tBlock;

		pWAMValidMove = false;

		tBlock = pWAMGameCore->GetRandomFlag();
		if (tBlock)
		{
			//if we have a impacted block...just add it to the list.
			tFlagBlock.vWAM_Position = tBlock->vWAM_Position;
			tFlagBlock.iWAM_HidenItem = tBlock->pWAM_Block->iWAM_HidenItem;

			switch (tBlock->pWAM_Block->iWAM_BlockType)
			{
			case WAM_BLOCK_TYPE_DESTR: {tFlagBlock.eWAMBlockType = EBlockTypeEnum::VE_Destructible; }break;
			case WAM_BLOCK_TYPE_BLOCK: {tFlagBlock.eWAMBlockType = EBlockTypeEnum::VE_Blocked; }break;
			case WAM_BLOCK_TYPE_FREE: {tFlagBlock.eWAMBlockType = EBlockTypeEnum::VE_Empty; }break;
			case WAM_BLOCK_TYPE_SPAWN_P1: {tFlagBlock.eWAMBlockType = EBlockTypeEnum::VE_SpawnP1; }break;
			case WAM_BLOCK_TYPE_SPAWN_P2: {tFlagBlock.eWAMBlockType = EBlockTypeEnum::VE_SpawnP2; }break;
			case WAM_BLOCK_TYPE_BOMB: {tFlagBlock.eWAMBlockType = EBlockTypeEnum::VE_Bomb; }break;
			case WAM_BLOCK_TYPE_EXPLOSION: {tFlagBlock.eWAMBlockType = EBlockTypeEnum::VE_Explosion; }break;
			case WAM_BLOCK_TYPE_ENEMY: {tFlagBlock.eWAMBlockType = EBlockTypeEnum::VE_Enemy; }break;
			case WAM_BLOCK_TYPE_FLAG: {tFlagBlock.eWAMBlockType = EBlockTypeEnum::VE_Flag; }break;
			}

			pWAMValidMove = true;
		}
		
		return tFlagBlock;
	}


	static WAMGameCoreControl       *pWAMGameCore        ;
	static TArray<FWAMBlockStruct>   pWAMBlockList       ;//Static List of blocks of the map
	static FWAMActorStruct           pWAMPlayer1         ;
	static FWAMActorStruct           pWAMPlayer2         ;
	
	
};
