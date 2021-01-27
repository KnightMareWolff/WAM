// Fill out your copyright notice in the Description page of Project Settings.

#include "WAM.h"
#include "WAMGameMap.h"

//1 Map is composed of other 8 submaps that will be transformed at creation
WAMGameMapNode**       WAMGameMap::pWAM_Map   =NULL;
WAMGameMapNode**       WAMGameMap::pWAM_MapL1 = NULL;
WAMGameMapNode**       WAMGameMap::pWAM_MapL2 = NULL;
WAMGameMapNode**       WAMGameMap::pWAM_MapL3 = NULL;
WAMGameMapNode**       WAMGameMap::pWAM_MapL4 = NULL;
WAMGameMapNode**       WAMGameMap::pWAM_MapL5 = NULL;
WAMGameMapNode**       WAMGameMap::pWAM_MapL6 = NULL;
WAMGameMapNode**       WAMGameMap::pWAM_MapL7 = NULL;
WAMGameMapNode**       WAMGameMap::pWAM_MapL8 = NULL;

int                    WAMGameMap::iWAM_SizeX=0;
int                    WAMGameMap::iWAM_SizeY=0;
UTexture2D*            WAMGameMap::tWAM_TextureMap=NULL;
UDataTable*            WAMGameMap::tWAM_MapDataTable = NULL;

WAMGameMap::WAMGameMap()
{
	tWAM_TextureMap = NULL;
}

WAMGameMap::WAMGameMap(int pWAMSizeX, int pWAMSizeY)
{
	int Idx;

	tWAM_TextureMap = NULL;

	iWAM_SizeX = pWAMSizeX;
	iWAM_SizeY = pWAMSizeY;

	pWAM_Map = new WAMGameMapNode*[iWAM_SizeX];

	for (Idx = 0; Idx < iWAM_SizeX; Idx++)
	{
		pWAM_Map[Idx] = new WAMGameMapNode[iWAM_SizeY];
	}
}

WAMGameMap::WAMGameMap(UTexture2D   *pWAMTextureMap)
{
	int Idx;

	tWAM_TextureMap = NULL;

	tWAM_TextureMap = pWAMTextureMap;

	iWAM_SizeX = pWAMTextureMap->GetSizeX();
	iWAM_SizeY = pWAMTextureMap->GetSizeY();

	pWAM_Map = new WAMGameMapNode*[iWAM_SizeX];

	for (Idx = 0; Idx < iWAM_SizeX; Idx++)
	{
		pWAM_Map[Idx] = new WAMGameMapNode[iWAM_SizeY];
	}
}

WAMGameMap::WAMGameMap(UDataTable   *pWAMMapDataTable, int pWAMMapSize)
{
	int Idx;

	tWAM_MapDataTable = NULL;

	tWAM_MapDataTable = pWAMMapDataTable;

	SetSize(pWAMMapSize);

	pWAM_Map = new WAMGameMapNode*[iWAM_SizeX];

	for (Idx = 0; Idx < iWAM_SizeX; Idx++)
	{
		pWAM_Map[Idx] = new WAMGameMapNode[iWAM_SizeY];
	}
}

bool WAMGameMap::Reset()
{
	int Idxi, Idxj; //Indices i,j

	for (Idxi = 0; Idxi < iWAM_SizeX; Idxi++)
	{
		for (Idxj = 0; Idxj < iWAM_SizeY; Idxj++)
		{
			pWAM_Map[Idxi][Idxj].ResetNode();
		}
	}
	return true;
}

bool WAMGameMap::Clear()
{
	int Idx;

	//Limpa Colunas alocadas
	for (Idx = 0; Idx < iWAM_SizeY; Idx++)
	{
		if (pWAM_Map[Idx])
		{
			delete[] pWAM_Map[Idx];
			pWAM_Map[Idx] = NULL;
		}
	}

	//Limpa Linhas alocadas
	delete[] pWAM_Map;
	pWAM_Map = NULL;

	//Zera os tamanhos
	iWAM_SizeX = 0;
	iWAM_SizeY = 0;

	return true;
}

WAMGameMap::~WAMGameMap()
{
	//Limpa a Matrix
	Clear();
}

int WAMGameMap::GetSizeX()
{
	return iWAM_SizeX;
}

int WAMGameMap::GetSizeY()
{
	return iWAM_SizeY;
}

WAMGameMapNode* WAMGameMap::GetNode(int x, int y)
{
	if (x > iWAM_SizeX || y > iWAM_SizeY || x < 0 || y < 0)return NULL;
	//Return the desired Node
	return &pWAM_Map[x][y];
}

WAMGameMapNode* WAMGameMap::GetCenter()
{
	//Return the desired Node
	return &pWAM_Map[iWAM_SizeX/2][iWAM_SizeY/2];
}

WAMGameMapNode* WAMGameMap::GetNode(FVector pWAM_Position)
{
	int Idxi, Idxj; //Indices i,j
	int tBlockType = 0;

	for (Idxi = 0; Idxi < iWAM_SizeX; Idxi++)
	{
		for (Idxj = 0; Idxj < iWAM_SizeY; Idxj++)
		{
			WAMGameMapNode* pBlock = GetNode(Idxi, Idxj);
			if (pBlock->vWAM_Position == pWAM_Position)
			{
				//Return the desired Node
				return &pWAM_Map[Idxi][Idxj];
			}
		}
	}
	
	return NULL;
}

WAMGameMapNode* WAMGameMap::GetNode(FVector pWAM_Position, int  &x, int  &y)
{
	int Idxi, Idxj; //Indices i,j
	int tBlockType = 0;

	for (Idxi = 0; Idxi < iWAM_SizeX; Idxi++)
	{
		for (Idxj = 0; Idxj < iWAM_SizeY; Idxj++)
		{
			WAMGameMapNode* pBlock = GetNode(Idxi, Idxj);
			if (pBlock->vWAM_Position == pWAM_Position)
			{
				//Return the desired Node and the Map Indices
				x = Idxi;
				y = Idxj;
				return &pWAM_Map[Idxi][Idxj];
			}
		}
	}

	return NULL;
}

bool WAMGameMap::SetNode(int x, int y, WAMGameMapNode* pWAM_Node)
{
	if (x > iWAM_SizeX || y > iWAM_SizeY || x < 0 || y < 0)return false;

	pWAM_Map[x][y] = *pWAM_Node;

	return true;
}

bool WAMGameMap::SetNode(FVector pWAM_Position, WAMGameMapNode* pWAM_Node)
{
	int Idxi, Idxj; //Indices i,j
	int tBlockType = 0;

	for (Idxi = 0; Idxi < iWAM_SizeX; Idxi++)
	{
		for (Idxj = 0; Idxj < iWAM_SizeY; Idxj++)
		{
			WAMGameMapNode* pBlock = GetNode(Idxi, Idxj);
			if (pBlock->vWAM_Position == pWAM_Position)
			{
				pWAM_Map[Idxi][Idxj] = *pWAM_Node;
			}
		}
	}

	return true;
}

bool WAMGameMap::SetSize(int     pWAM_MapSize)
{
	iWAM_SizeX = pWAM_MapSize;
	iWAM_SizeY = pWAM_MapSize;

	return true;
}

bool WAMGameMap::BuildMap()
{
	int Idxi, Idxj; //Indices i,j
	int tBlockType = 0;
	int tHiddenItem = 0;

	for (Idxi = 0; Idxi < iWAM_SizeX; Idxi++)
	{
		for (Idxj = 0; Idxj < iWAM_SizeY; Idxj++)
		{
			
			WAMGameMapNode* pBlock;
			/*
			I know, I know...This is pretty ugly...but for now works for tests... ;)
			00000000
			01010110
			01110010
			01000010
			01111110
			01001000
			01101110
			00000000
			*/

			//Setup the default block
			tBlockType  = WAM_BLOCK_TYPE_BLOCK;
			tHiddenItem = 0;
			//Setup Free Blocks
			if (Idxi == 1 && Idxj == 1)tBlockType = WAM_BLOCK_TYPE_SPAWN_P1;
			if (Idxi == 1 && Idxj == 2)tBlockType = WAM_BLOCK_TYPE_FREE;
			if (Idxi == 1 && Idxj == 4)tBlockType = WAM_BLOCK_TYPE_FREE;
			if (Idxi == 1 && Idxj == 5)tBlockType = WAM_BLOCK_TYPE_FREE;
			if (Idxi == 1 && Idxj == 6)tBlockType = WAM_BLOCK_TYPE_FREE;
			if (Idxi == 2 && Idxj == 1)tBlockType = WAM_BLOCK_TYPE_FREE;
			if (Idxi == 2 && Idxj == 4)tBlockType = WAM_BLOCK_TYPE_FREE;
			if (Idxi == 3 && Idxj == 1)tBlockType = WAM_BLOCK_TYPE_FREE;
			if (Idxi == 3 && Idxj == 2)tBlockType = WAM_BLOCK_TYPE_FREE;
			if (Idxi == 3 && Idxj == 3)tBlockType = WAM_BLOCK_TYPE_FREE;
			if (Idxi == 3 && Idxj == 4)tBlockType = WAM_BLOCK_TYPE_FREE;
			if (Idxi == 3 && Idxj == 5)tBlockType = WAM_BLOCK_TYPE_FREE;
			if (Idxi == 3 && Idxj == 6)tBlockType = WAM_BLOCK_TYPE_DESTR;
			if (Idxi == 4 && Idxj == 1)tBlockType = WAM_BLOCK_TYPE_FREE;
			if (Idxi == 4 && Idxj == 6)tBlockType = WAM_BLOCK_TYPE_FREE;
			if (Idxi == 5 && Idxj == 1)tBlockType = WAM_BLOCK_TYPE_FREE;
			if (Idxi == 5 && Idxj == 2)tBlockType = WAM_BLOCK_TYPE_FREE;
			if (Idxi == 5 && Idxj == 3)tBlockType = WAM_BLOCK_TYPE_FREE;
			if (Idxi == 5 && Idxj == 6)tBlockType = WAM_BLOCK_TYPE_FREE;
			if (Idxi == 6 && Idxj == 1)tBlockType = WAM_BLOCK_TYPE_FREE;
			if (Idxi == 6 && Idxj == 3)tBlockType = WAM_BLOCK_TYPE_FREE;
			if (Idxi == 6 && Idxj == 5)tBlockType = WAM_BLOCK_TYPE_FREE;
			if (Idxi == 6 && Idxj == 6)tBlockType = WAM_BLOCK_TYPE_SPAWN_P2;

			if (tBlockType == WAM_BLOCK_TYPE_DESTR)tHiddenItem = 1;

			pBlock = new WAMGameMapNode(FVector(Idxi * WAM_NODE_SIZE, Idxj * WAM_NODE_SIZE, 50), tBlockType, tHiddenItem);
			
			SetNode(Idxi, Idxj, pBlock);
		}
	}

	return true;

}

bool WAMGameMap::BuildMapTex()
{
	int Idxi, Idxj; //Indices i,j
	int tBlockType = 0;

	//Prepeare the texture memory for processing
	uint8* raw = NULL;
	FTexture2DMipMap& Mip = tWAM_TextureMap->PlatformData->Mips[0];
	void* Data = Mip.BulkData.Lock(LOCK_READ_WRITE);
	raw = (uint8*)Data;

	//Traverse building the block accordingly with the colormap
	for (Idxi = 0; Idxi < iWAM_SizeX; Idxi++)
	{
		for (Idxj = 0; Idxj < iWAM_SizeY; Idxj++)
		{

			WAMGameMapNode* pBlock;
			
			//Setup the default block
			//tBlockType = WAM_BLOCK_TYPE_BLOCK;

			// read here in low level:
			//let's say I want pixel x = 300, y = 23
			//basic formula, data[channels * (width * y + x)];
			FColor pixel = FColor(0, 0, 0, 255);
			pixel.B = raw[4 * ((iWAM_SizeY * iWAM_SizeX) * Idxj + Idxi) + 0];
			pixel.G = raw[4 * ((iWAM_SizeY * iWAM_SizeX) * Idxj + Idxi) + 1];
			pixel.R = raw[4 * ((iWAM_SizeY * iWAM_SizeX) * Idxj + Idxi) + 2];
			pixel.A = raw[4 * ((iWAM_SizeY * iWAM_SizeX) * Idxj + Idxi) + 3];
			//if color is black
			if (pixel.B == 0)tBlockType = WAM_BLOCK_TYPE_BLOCK;

			//if color is white
			if (pixel.B != 0)tBlockType = WAM_BLOCK_TYPE_FREE;

			if (Idxi == 1 && Idxj == 1)tBlockType = WAM_BLOCK_TYPE_SPAWN_P1;
			if (Idxi == 6 && Idxj == 6)tBlockType = WAM_BLOCK_TYPE_SPAWN_P2;

			pBlock = new WAMGameMapNode(FVector(Idxi * WAM_NODE_SIZE, Idxj * WAM_NODE_SIZE, 50), tBlockType, 0);

			SetNode(Idxi, Idxj, pBlock);
		}
	}

	Mip.BulkData.Unlock();
	tWAM_TextureMap->UpdateResource();
	
	return true;

}

bool WAMGameMap::BuildMapData()
{
	int Idxi, Idxj; //Indices i,j
	int tBlockType = 0;
	int tRowID=1;

	WAMGameMapNode* pBlock;

	for (tRowID = 1; tRowID <= (iWAM_SizeX * iWAM_SizeY); tRowID++)
	{
		FString StringID    = FString::FromInt(tRowID);
		FName   ConvertedID = FName(*StringID);

		//Search the block data
		FWAMGameMapData* row = tWAM_MapDataTable->FindRow<FWAMGameMapData>(ConvertedID, TEXT("DataBlockSearch"));
		
		//get the block information
		FString someString = row->WAM_BlockDescription;
		tBlockType = row->WAM_BlockType;
		Idxi = row->WAM_BlockPosX;
		Idxj = row->WAM_BlockPosY;

		//Build the map node
		pBlock = new WAMGameMapNode(FVector(Idxi * WAM_NODE_SIZE, Idxj * WAM_NODE_SIZE, 50), tBlockType, 0);

		//Set the node in the map...
		SetNode(Idxi, Idxj, pBlock);
	}
	
	return true;

}
