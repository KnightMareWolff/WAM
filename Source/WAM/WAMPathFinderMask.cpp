// Fill out your copyright notice in the Description page of Project Settings.

#include "WAM.h"
#include "WAMPathFinderMask.h"

WAMPathFinderMask::WAMPathFinderMask()
{
	pWAM_NorthLest = NULL;
	pWAM_NorthWest = NULL;
	pWAM_SouthLest = NULL;
	pWAM_SouthWest = NULL;
}

WAMPathFinderMask::~WAMPathFinderMask()
{
}

bool WAMPathFinderMask::MoveToLocation(FVector pWAMLocation)
{
	pWAM_3DLocation = pWAMLocation;
	pWAM_2DLocation = FVector2D(pWAM_3DLocation.X, pWAM_3DLocation.Y);

	FVector tPosNorth;
	FVector tPosSouth;
	FVector tPosLest;
	FVector tPosWest;
	FVector tPosCenter;
	FVector tPosNorthLest;
	FVector tPosNorthWest;
	FVector tPosSouthLest;
	FVector tPosSouthWest;

	//Centralize all the nodes at the central position
	tPosNorth     = pWAM_3DLocation;
	tPosSouth     = pWAM_3DLocation;
	tPosLest      = pWAM_3DLocation;
	tPosWest      = pWAM_3DLocation;
	tPosCenter    = pWAM_3DLocation;
	tPosNorthLest = pWAM_3DLocation;
	tPosNorthWest = pWAM_3DLocation;
	tPosSouthLest = pWAM_3DLocation;
	tPosSouthWest = pWAM_3DLocation;

	//Calculate the final positions
	tPosNorth.X     += WAM_NODE_SIZE;
	tPosSouth.X     -= WAM_NODE_SIZE;
	tPosLest.Y      -= WAM_NODE_SIZE;
	tPosWest.Y      += WAM_NODE_SIZE;
	tPosNorthLest.X += WAM_NODE_SIZE;
	tPosNorthLest.Y -= WAM_NODE_SIZE;
	tPosNorthWest.X += WAM_NODE_SIZE;
	tPosNorthWest.Y += WAM_NODE_SIZE;
	tPosSouthLest.X -= WAM_NODE_SIZE;
	tPosSouthLest.Y -= WAM_NODE_SIZE;
	tPosSouthWest.X -= WAM_NODE_SIZE;
	tPosSouthWest.Y += WAM_NODE_SIZE;

	//Get all the mask map nodes for future reference.
	pWAM_North  = WAMGameMap::GetNode(tPosNorth);
	pWAM_South  = WAMGameMap::GetNode(tPosSouth);
	pWAM_Lest   = WAMGameMap::GetNode(tPosLest);
	pWAM_West   = WAMGameMap::GetNode(tPosWest);

	pWAM_Center = WAMGameMap::GetNode(tPosCenter);
	
	pWAM_NorthLest = WAMGameMap::GetNode(tPosNorthLest);
	pWAM_NorthWest = WAMGameMap::GetNode(tPosNorthWest);
	pWAM_SouthLest = WAMGameMap::GetNode(tPosSouthLest);
	pWAM_SouthWest = WAMGameMap::GetNode(tPosSouthWest);

	//if (pWAM_Center->pWAM_Block->iWAM_BlockType != WAM_BLOCK_TYPE_FREE)return false;

	return true;
}

bool WAMPathFinderMask::MoveToLocation(FVector2D pWAMLocation)
{
	pWAM_2DLocation = pWAMLocation;
	pWAM_3DLocation = FVector(pWAM_2DLocation.X, pWAM_2DLocation.Y, 50);

	FVector tPosNorth;
	FVector tPosSouth;
	FVector tPosLest;
	FVector tPosWest;
	FVector tPosCenter;
	FVector tPosNorthLest;
	FVector tPosNorthWest;
	FVector tPosSouthLest;
	FVector tPosSouthWest;

	//Centralize all the nodes at the central position
	tPosNorth = pWAM_3DLocation;
	tPosSouth = pWAM_3DLocation;
	tPosLest = pWAM_3DLocation;
	tPosWest = pWAM_3DLocation;
	tPosCenter = pWAM_3DLocation;
	tPosNorthLest = pWAM_3DLocation;
	tPosNorthWest = pWAM_3DLocation;
	tPosSouthLest = pWAM_3DLocation;
	tPosSouthWest = pWAM_3DLocation;

	//Calculate the final positions
	tPosNorth.X += WAM_NODE_SIZE;
	tPosSouth.X -= WAM_NODE_SIZE;
	tPosLest.Y -= WAM_NODE_SIZE;
	tPosWest.Y += WAM_NODE_SIZE;
	tPosNorthLest.X += WAM_NODE_SIZE;
	tPosNorthLest.Y -= WAM_NODE_SIZE;
	tPosNorthWest.X += WAM_NODE_SIZE;
	tPosNorthWest.Y += WAM_NODE_SIZE;
	tPosSouthLest.X -= WAM_NODE_SIZE;
	tPosSouthLest.Y -= WAM_NODE_SIZE;
	tPosSouthWest.X -= WAM_NODE_SIZE;
	tPosSouthWest.Y += WAM_NODE_SIZE;

	//Get all the mask map nodes for future reference.
	pWAM_North = WAMGameMap::GetNode(tPosNorth);
	pWAM_South = WAMGameMap::GetNode(tPosSouth);
	pWAM_Lest = WAMGameMap::GetNode(tPosLest);
	pWAM_West = WAMGameMap::GetNode(tPosWest);

	pWAM_Center = WAMGameMap::GetNode(tPosCenter);

	pWAM_NorthLest = WAMGameMap::GetNode(tPosNorthLest);
	pWAM_NorthWest = WAMGameMap::GetNode(tPosNorthWest);
	pWAM_SouthLest = WAMGameMap::GetNode(tPosSouthLest);
	pWAM_SouthWest = WAMGameMap::GetNode(tPosSouthWest);


	//if (pWAM_Center->pWAM_Block->iWAM_BlockType != WAM_BLOCK_TYPE_FREE)return false;

	return true;
}
