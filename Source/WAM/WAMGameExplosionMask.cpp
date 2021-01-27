// Fill out your copyright notice in the Description page of Project Settings.

#include "WAM.h"
#include "WAMGameExplosionMask.h"


WAMGameExplosionMask::WAMGameExplosionMask()
{
	pWAM_North = NULL;
	pWAM_South = NULL;
	pWAM_Lest = NULL;
	pWAM_West = NULL;
}

WAMGameExplosionMask::~WAMGameExplosionMask()
{
}

bool WAMGameExplosionMask::MoveToLocation(FVector pWAMLocation)
{
	pWAM_3DLocation = pWAMLocation;
	pWAM_2DLocation = FVector2D(pWAM_3DLocation.X, pWAM_3DLocation.Y);

	FVector tPosNorth;
	FVector tPosSouth;
	FVector tPosLest;
	FVector tPosWest;
	FVector tPosCenter;

	//Centralize all the nodes at the central position
	tPosNorth = pWAM_3DLocation;
	tPosSouth = pWAM_3DLocation;
	tPosLest = pWAM_3DLocation;
	tPosWest = pWAM_3DLocation;
	tPosCenter = pWAM_3DLocation;

	//Calculate the final positions
	tPosNorth.X += WAM_NODE_SIZE;
	tPosSouth.X -= WAM_NODE_SIZE;
	tPosLest.Y -= WAM_NODE_SIZE;
	tPosWest.Y += WAM_NODE_SIZE;

	//Get all the mask map nodes for future reference.
	pWAM_North = WAMGameMap::GetNode(tPosNorth);
	pWAM_South = WAMGameMap::GetNode(tPosSouth);
	pWAM_Lest = WAMGameMap::GetNode(tPosLest);
	pWAM_West = WAMGameMap::GetNode(tPosWest);
	pWAM_Center = WAMGameMap::GetNode(tPosCenter);

	if (pWAM_Center->pWAM_Block->iWAM_BlockType != WAM_BLOCK_TYPE_FREE)return false;

	return true;
}

bool WAMGameExplosionMask::MoveToLocation(FVector2D pWAMLocation)
{
	pWAM_2DLocation = pWAMLocation;
	pWAM_3DLocation = FVector(pWAM_2DLocation.X, pWAM_2DLocation.Y, 50);

	FVector tPosNorth;
	FVector tPosSouth;
	FVector tPosLest;
	FVector tPosWest;
	FVector tPosCenter;

	//Centralize all the nodes at the central position
	tPosNorth = pWAM_3DLocation;
	tPosSouth = pWAM_3DLocation;
	tPosLest = pWAM_3DLocation;
	tPosWest = pWAM_3DLocation;
	tPosCenter = pWAM_3DLocation;

	//Calculate the final positions
	tPosNorth.X += WAM_NODE_SIZE;
	tPosSouth.X -= WAM_NODE_SIZE;
	tPosLest.Y -= WAM_NODE_SIZE;
	tPosWest.Y += WAM_NODE_SIZE;

	//Get all the mask map nodes for future reference.
	pWAM_North = WAMGameMap::GetNode(tPosNorth);
	pWAM_South = WAMGameMap::GetNode(tPosSouth);
	pWAM_Lest = WAMGameMap::GetNode(tPosLest);
	pWAM_West = WAMGameMap::GetNode(tPosWest);
	pWAM_Center = WAMGameMap::GetNode(tPosCenter);

	if (pWAM_Center->pWAM_Block->iWAM_BlockType != WAM_BLOCK_TYPE_FREE)return false;

	return true;
}

bool WAMGameExplosionMask::SetBlockData(int pWAMBlockType, int pWAMHiddenItem, bool pWAMUpdated)
{
	//In the Explosion Mask, only free way are masked has a explosion effect
	if (pWAM_North->pWAM_Block->iWAM_BlockType == WAM_BLOCK_TYPE_FREE)
	{
		pWAM_North->pWAM_Block->iWAM_BlockType = pWAMBlockType;
		pWAM_North->bWAM_Updated = pWAMUpdated;
	}
	else
	{
		//in the case is not a free block we check if a destructive block was not impacted...
		if (pWAM_North->pWAM_Block->iWAM_BlockType == WAM_BLOCK_TYPE_DESTR)
		{
			//mark the node as impacted to make possible we return the impacted actors to the game.
			pWAM_North->pWAM_Block->iWAM_Impacted = true;
		}
	}

	if (pWAM_South->pWAM_Block->iWAM_BlockType == WAM_BLOCK_TYPE_FREE)
	{
		pWAM_South->pWAM_Block->iWAM_BlockType = pWAMBlockType;
		pWAM_South->bWAM_Updated = pWAMUpdated;
	}
	else
	{
		//in the case is not a free block we check if a destructive block was not impacted...
		if (pWAM_South->pWAM_Block->iWAM_BlockType == WAM_BLOCK_TYPE_DESTR)
		{
			//mark the node as impacted to make possible we return the impacted actors to the game.
			pWAM_South->pWAM_Block->iWAM_Impacted = true;
		}
	}

	if (pWAM_Lest->pWAM_Block->iWAM_BlockType == WAM_BLOCK_TYPE_FREE)
	{
		pWAM_Lest->pWAM_Block->iWAM_BlockType = pWAMBlockType;
		pWAM_Lest->bWAM_Updated = pWAMUpdated;
	}
	else
	{
		//in the case is not a free block we check if a destructive block was not impacted...
		if (pWAM_Lest->pWAM_Block->iWAM_BlockType == WAM_BLOCK_TYPE_DESTR)
		{
			//mark the node as impacted to make possible we return the impacted actors to the game.
			pWAM_Lest->pWAM_Block->iWAM_Impacted = true;
		}
	}

	if (pWAM_West->pWAM_Block->iWAM_BlockType == WAM_BLOCK_TYPE_FREE)
	{
		pWAM_West->pWAM_Block->iWAM_BlockType = pWAMBlockType;
		pWAM_West->bWAM_Updated = pWAMUpdated;
	}
	else
	{
		//in the case is not a free block we check if a destructive block was not impacted...
		if (pWAM_West->pWAM_Block->iWAM_BlockType == WAM_BLOCK_TYPE_DESTR)
		{
			//mark the node as impacted to make possible we return the impacted actors to the game.
			pWAM_West->pWAM_Block->iWAM_Impacted = true;
		}
	}

	if (pWAM_Center->pWAM_Block->iWAM_BlockType == WAM_BLOCK_TYPE_FREE)
	{
		pWAM_Center->pWAM_Block->iWAM_BlockType = pWAMBlockType;
		pWAM_Center->bWAM_Updated = pWAMUpdated;
	}
	else
	{
		//in the case is not a free block we check if a destructive block was not impacted...
		if (pWAM_Center->pWAM_Block->iWAM_BlockType == WAM_BLOCK_TYPE_DESTR)
		{
			//mark the node as impacted to make possible we return the impacted actors to the game.
			pWAM_Center->pWAM_Block->iWAM_Impacted = true;
		}
	}

	return true;
}
