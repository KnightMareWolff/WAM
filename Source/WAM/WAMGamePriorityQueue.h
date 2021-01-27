// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "WAMGameMapNode.h"


class WAM_API WAMPriorityNode : public WAMGameMapNode
{
public:
	WAMPriorityNode():
		WAMGameMapNode()
	{
		//pWAM_QueueNode = NULL;
		pWAM_NextNode = pWAM_PriorNode = NULL;
	}

	WAMPriorityNode(WAMGameMapNode *no) 
	{ 
		//Map Logic Pointers & Organization
		vWAM_Position = no->vWAM_Position;
		pWAM_Block    = no->pWAM_Block;

		//Map Algorithm Informations
		bWAM_Updated  = no->bWAM_Updated;

		//PathFinder Algorith Informations
		pWAM_Father = no->pWAM_Father;
		iWAM_Cost   = no->iWAM_Cost;
		iWAM_g      = no->iWAM_g;
		iWAM_f      = no->iWAM_f;
		iWAM_h      = no->iWAM_h;
		
		pWAM_NextNode = pWAM_PriorNode = 0; 
	}

	//WAMPriorityNode   *pWAM_QueueNode;
	WAMPriorityNode   *pWAM_NextNode;
	WAMPriorityNode   *pWAM_PriorNode;
};
/**
 * 
 */
class WAM_API WAMGamePriorityQueue
{
public:
	  WAMGamePriorityQueue();
	 ~WAMGamePriorityQueue() 
	 {
		 QueueClean();
		 //delete pWAM_QueueBegin->pWAM_QueueNode;
		 //delete pWAM_QueueEnd  ->pWAM_QueueNode;
		 delete pWAM_QueueBegin; 
		 delete pWAM_QueueEnd;
	 }

	void            QueueClean();
	bool            QueueEmpty() { return iWAM_QueueSize == 0; }
	void            Enqueue(WAMGameMapNode *no);
	WAMGameMapNode* Dequeue(                  );
	void            Remove (WAMGameMapNode *no);
	bool            Contain(WAMGameMapNode *no) const;

private:
	
	unsigned int     iWAM_QueueSize;
	WAMPriorityNode *pWAM_QueueBegin;
	WAMPriorityNode *pWAM_QueueEnd;
};
