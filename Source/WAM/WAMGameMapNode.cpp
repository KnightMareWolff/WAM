// Fill out your copyright notice in the Description page of Project Settings.

#include "WAM.h"
#include "WAMGameMapNode.h"

WAMGameMapNode::WAMGameMapNode()
{
	vWAM_Position              = FVector(0, 0, 0);
	pWAM_Block                 = new WAMGameBlock();
	pWAM_Block->iWAM_BlockType = WAM_BLOCK_TYPE_BLOCK;
	pWAM_Block->iWAM_HidenItem = 0;
	bWAM_Updated               = false;

	//PathFinder Algorith Informations
	pWAM_Father = NULL;
	iWAM_Cost   = 1;
	iWAM_g=0;
	iWAM_f=0;
	iWAM_h=0;
}


WAMGameMapNode::WAMGameMapNode(const WAMGameMapNode &copy)
{
	vWAM_Position              = copy.vWAM_Position;
	pWAM_Block                 = copy.pWAM_Block;
	pWAM_Block->iWAM_BlockType = copy.pWAM_Block->iWAM_BlockType;
	pWAM_Block->iWAM_HidenItem = copy.pWAM_Block->iWAM_HidenItem;
	bWAM_Updated               = copy.bWAM_Updated;

	//PathFinder Algorith Informations
	pWAM_Father = copy.pWAM_Father;
	iWAM_Cost   = copy.iWAM_Cost;
	iWAM_g      = copy.iWAM_g;
	iWAM_f      = copy.iWAM_f;
	iWAM_h      = copy.iWAM_h;

}

WAMGameMapNode::WAMGameMapNode(FVector pWAM_Position, int pBlockType, int pHiddenItem)
{
	vWAM_Position               = pWAM_Position;
	pWAM_Block                  = new WAMGameBlock();
	pWAM_Block->iWAM_BlockType  = pBlockType;
	pWAM_Block->iWAM_HidenItem  = pHiddenItem;
	bWAM_Updated                = false;

	//PathFinder Algorith Informations
	if (pWAM_Block->iWAM_BlockType != WAM_BLOCK_TYPE_BLOCK &&
		pWAM_Block->iWAM_BlockType != WAM_BLOCK_TYPE_DESTR)
	{
		pWAM_Father = NULL;
		iWAM_Cost = 1;
		iWAM_g = 0;
		iWAM_f = 0;
		iWAM_h = 0;
	}
	else 
	{
		pWAM_Father = NULL;
		iWAM_Cost   = BLOCKED;
		iWAM_g = 0;
		iWAM_f = 0;
		iWAM_h = 0;
	}
}

WAMGameMapNode::WAMGameMapNode(FVector pWAM_Position, bool PrtyEndNode)
{
	vWAM_Position = pWAM_Position;
	pWAM_Block = new WAMGameBlock();
	pWAM_Block->iWAM_BlockType = WAM_BLOCK_TYPE_BLOCK;
	pWAM_Block->iWAM_HidenItem = 0;
	bWAM_Updated = false;

	//PathFinder Algorith Informations
	if (PrtyEndNode == true)
	{
		pWAM_Father = NULL;
		iWAM_Cost = 10000000;
		iWAM_g = 0;
		iWAM_f = 0;
		iWAM_h = 0;
	}
	else
	{
		pWAM_Father = NULL;
		iWAM_Cost = -1;
		iWAM_g = 0;
		iWAM_f = 0;
		iWAM_h = 0;
	}
}
WAMGameMapNode::~WAMGameMapNode()
{
}

WAMGameMapNode & WAMGameMapNode::operator=(const WAMGameMapNode &opr)
{
	vWAM_Position              = opr.vWAM_Position;
	pWAM_Block                 = opr.pWAM_Block;
	pWAM_Block->iWAM_BlockType = opr.pWAM_Block->iWAM_BlockType;
	pWAM_Block->iWAM_HidenItem = opr.pWAM_Block->iWAM_HidenItem;
	pWAM_Father                = opr.pWAM_Father;
	iWAM_Cost                  = opr.iWAM_Cost;
	iWAM_g                     = opr.iWAM_g;
	iWAM_f                     = opr.iWAM_f;
	iWAM_h                     = opr.iWAM_h;
	return *this;
}

bool WAMGameMapNode::operator==(const WAMGameMapNode &opr)
{
	return this->Equal(opr);
}

bool WAMGameMapNode::operator<(const WAMGameMapNode &opr)
{
	return iWAM_Cost < opr.iWAM_Cost;
}

bool WAMGameMapNode::operator>(const WAMGameMapNode &opr)
{
	return iWAM_Cost > opr.iWAM_Cost;
}

void WAMGameMapNode::SetMapCost(const int pWAM_MapCost)
{
	iWAM_Cost = pWAM_MapCost;
}

int WAMGameMapNode::GetMapCost() const
{
	return iWAM_Cost;
}

void WAMGameMapNode::SetPathCost(const int pWAM_PathCost)
{
	iWAM_f = pWAM_PathCost;
}

int WAMGameMapNode::GetPathCost() const
{
	return iWAM_f;
}

bool WAMGameMapNode::ResetNode()
{
	if (pWAM_Block)
	{
		pWAM_Block->iWAM_BlockType = WAM_BLOCK_TYPE_BLOCK;
		pWAM_Block->iWAM_HidenItem = 0;
	}

	vWAM_Position = FVector(0, 0, 0);
	bWAM_Updated  = false;
	return true;
}