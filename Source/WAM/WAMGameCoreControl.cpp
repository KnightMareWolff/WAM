// Fill out your copyright notice in the Description page of Project Settings.

#include "WAMGameCoreControl.h"
#include "WAM.h"


WAMGameCoreControl::WAMGameCoreControl()
{
	pWAM_GameOk = false;
	CreateObjects(8,8);
	pWAM_GameOk = true;
}

WAMGameCoreControl::WAMGameCoreControl(int pWAMSizeX, int pWAMSizeY)
{
	pWAM_GameOk = false;
	CreateObjects(pWAMSizeX,pWAMSizeY);
	pWAM_GameOk = true;
}

WAMGameCoreControl::WAMGameCoreControl(UTexture2D *pWAMTextureMap)
{
	pWAM_GameOk = false;
	CreateObjects(pWAMTextureMap);
	pWAM_GameOk = true;
}

WAMGameCoreControl::WAMGameCoreControl(UDataTable *pWAMMapDataTable, int pWAMMapSize)
{
	pWAM_GameOk = false;
	CreateObjects(pWAMMapDataTable, pWAMMapSize);
	pWAM_GameOk = true;
}

WAMGameCoreControl::~WAMGameCoreControl()
{
}

bool WAMGameCoreControl::CreateMap(int pWAMSizeX, int pWAMSizeY)
{
	pWAM_GameMap = new WAMGameMap(pWAMSizeX, pWAMSizeY);
	
	WAMGameMap::BuildMap();
	
	return true;
}

bool WAMGameCoreControl::CreateMap(UTexture2D *pWAMTextureMap)
{
	pWAM_GameMap = new WAMGameMap(pWAMTextureMap);
	
	WAMGameMap::BuildMapTex();
	
	return true;
}

bool WAMGameCoreControl::CreateMap(UDataTable *pWAMMapDataTable, int pWAMMapSize)
{
	pWAM_GameMap = new WAMGameMap(pWAMMapDataTable, pWAMMapSize);
	
	WAMGameMap::BuildMapData();

	return true;
}

bool WAMGameCoreControl::CreateObjects(int pWAMSizeX, int pWAMSizeY)
{
	CreateMap(pWAMSizeX, pWAMSizeY);
	CreatePlayers();
	CreateElements();
	return true;
}

bool WAMGameCoreControl::CreateObjects(UTexture2D *pWAMTextureMap)
{
	CreateMap(pWAMTextureMap);
	CreatePlayers();
	CreateElements();
	return true;
}

bool WAMGameCoreControl::CreateObjects(UDataTable *pWAMMapDataTable, int pWAMMapSize)
{
	CreateMap(pWAMMapDataTable, pWAMMapSize);
	CreatePlayers();
	CreateElements();
	return true;
}

bool WAMGameCoreControl::CreatePlayers()
{
	for (int x = 0; x < WAMGameMap::GetSizeX(); x++)
	{
		for (int y = 0; y < WAMGameMap::GetSizeY(); y++)
		{
			WAMGameMapNode *tNode = NULL;

			tNode = WAMGameMap::GetNode(x, y);

			switch (tNode->pWAM_Block->iWAM_BlockType)
			{
			case WAM_BLOCK_TYPE_SPAWN_P1: {Player01 = new WAMGamePlayer(0, tNode->vWAM_Position); }break;
			case WAM_BLOCK_TYPE_SPAWN_P2: {Player02 = new WAMGamePlayer(0, tNode->vWAM_Position); }break;
			}
		}
	}

	return true;
}

bool WAMGameCoreControl::CreateElements()
{
	Explosion       = new WAMGameExplosion(WAM_EXPLOSION_ST_BORN,FVector(0,0,0));
	pWAM_PathFinder = new WAMGamePathfinder();
	return true;
}

WAMGamePlayer* WAMGameCoreControl::GetPlayer(int pWAM_PlayerId)
{
	switch (pWAM_PlayerId)
	{
	case 0: {return Player01; }break;
	case 1: {return Player02; }break;
	}

	return NULL;
}

TArray<WAMGameMapNode*> WAMGameCoreControl::GetMapNodes()
{
	pWAM_GameMapNodesArray.Empty();

	for (int x = 0; x < WAMGameMap::GetSizeX(); x++)
	{
		for (int y = 0; y < WAMGameMap::GetSizeY(); y++)
		{
			WAMGameMapNode *tNode = NULL;

			tNode = WAMGameMap::GetNode(x, y);

			pWAM_GameMapNodesArray.Add(tNode);
		}
	}

	return pWAM_GameMapNodesArray;
}

TArray<WAMGameMapNode*> WAMGameCoreControl::GetMapFlags()
{
	pWAM_GameFlagArray.Empty();

	for (int x = 0; x < WAMGameMap::GetSizeX(); x++)
	{
		for (int y = 0; y < WAMGameMap::GetSizeY(); y++)
		{
			WAMGameMapNode *tNode = NULL;

			tNode = WAMGameMap::GetNode(x, y);

			if (tNode->pWAM_Block->iWAM_BlockType == WAM_BLOCK_TYPE_FLAG)pWAM_GameFlagArray.Add(tNode);
		}
	}

	return pWAM_GameFlagArray;
}

WAMGameMapNode* WAMGameCoreControl::GetRandomFlag()
{
	GetMapFlags();

	if (pWAM_GameFlagArray.Num() == 0)return NULL;

	int id = FMath::RandRange(0, pWAM_GameFlagArray.Num()-1);

	return pWAM_GameFlagArray[id];
}

TArray<WAMGameMapNode*> WAMGameCoreControl::GetImpactedNodes()
{
	pWAM_GameImpactedArray.Empty();

	for (int x = 0; x < WAMGameMap::GetSizeX(); x++)
	{
		for (int y = 0; y < WAMGameMap::GetSizeY(); y++)
		{
			WAMGameMapNode *tNode = NULL;

			//get the node pointer of the map
			tNode = WAMGameMap::GetNode(x, y);

			//if the node was impacted by a explosion
			if (tNode->pWAM_Block->iWAM_Impacted)
			{
				pWAM_GameImpactedArray.Add(tNode);
			}
		}
	}

	return pWAM_GameImpactedArray;
}

bool WAMGameCoreControl::UpdateBlock(WAMGameMapNode* pWAM_UpdatedBlock)
{
	WAMGameMapNode* pBlock = NULL;
	FVector tActualPosition;

	tActualPosition = pWAM_UpdatedBlock->vWAM_Position;
	
	pBlock = pWAM_GameMap->GetNode(tActualPosition);
	if (pBlock)
	{
		pWAM_GameMap->SetNode(tActualPosition, pWAM_UpdatedBlock);
	}

	return true;
}

//directions 0-up 1-down 2-lef 3-right
bool WAMGameCoreControl::MovePlayer(int pWAM_PlayerId, int pWAM_Direction)
{
	FVector tActualPosition, tNextPosition;
	switch (pWAM_PlayerId)
	{
	case 0: 
	{
		Player01->MovePlayer(pWAM_Direction);
		return true;
		
	}break;
	case 1: 
	{
		Player02->MovePlayer(pWAM_Direction);
		return true;
	}break;
	}

	return false;
}

//directions 0-up 1-down 2-lef 3-right
bool WAMGameCoreControl::ThrowBomb(int pWAM_PlayerId)
{
	FVector tActualPosition;
	switch (pWAM_PlayerId)
	{
	case 0:
	{
		//decrease the munition of the player
		if (Player01->PopMunition())
		{
			WAMGameMapNode* pMapNode = NULL;
			//get actual position of the player
			tActualPosition = Player01->GetLocation();
			//get the map node related to this position
			pMapNode = pWAM_GameMap->GetNode(tActualPosition);
			if (pMapNode)
			{
				pMapNode->pWAM_Block->iWAM_BlockType = WAM_BLOCK_TYPE_BOMB;
				pMapNode->bWAM_Updated = true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}

		return true;

	}break;
	case 1:
	{
		WAMGameMapNode* pMapNode = NULL;

		tActualPosition = Player02->GetLocation();
		
		pMapNode = pWAM_GameMap->GetNode(tActualPosition);
		if (pMapNode)
		{
			pMapNode->pWAM_Block->iWAM_BlockType = WAM_BLOCK_TYPE_BOMB;
			pMapNode->bWAM_Updated = true;
		}
		else
		{
			return false;
		}

		return true;
	}break;
	}

	return false;
}

//Explosions born at the location of the destroyed bomb...
bool WAMGameCoreControl::ThrowExplosion(FVector pWAM_BombLocation)
{
	FVector tActualPosition;
	
	//get actual position of the player
	tActualPosition = pWAM_BombLocation;
	
	Explosion->MoveExplosion(pWAM_BombLocation);
	Explosion->SetBlockData(WAM_BLOCK_TYPE_EXPLOSION, 0, true);
	

	return true;
}

//Set the size of the Map directly from the game.(This is Usefull when we load from a DataTable...)
bool WAMGameCoreControl::SetMapSize(int pWAM_MapSize)
{
	WAMGameMap::SetSize(pWAM_MapSize);
	return true;
}

//Set the size of the Map directly from the game.(This is Usefull when we load from a DataTable...)
FVector WAMGameCoreControl::GetCenterMap()
{
	
	return WAMGameMap::GetCenter()->vWAM_Position;
}

//Set the size of the Map directly from the game.(This is Usefull when we load from a DataTable...)
bool WAMGameCoreControl::GetGameStatus()
{
	return pWAM_GameOk;
}

//return a array of blocks to be traversed by the autonomous actor
TArray<WAMGameMapNode*> WAMGameCoreControl::FindPath(FVector pWAM_Begin, FVector pWAM_End)
{
	TArray<WAMGameMapNode*> tPath;
	pWAM_PathFinder->FindPath(WAMGameMap::GetNode(pWAM_Begin), WAMGameMap::GetNode(pWAM_End));
	tPath = pWAM_PathFinder->GetPath();
	Algo::Reverse(tPath);
	return tPath;
}