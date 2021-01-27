// Fill out your copyright notice in the Description page of Project Settings.

#include "WAM.h"
#include "WAMGamePriorityQueue.h"


WAMGamePriorityQueue::WAMGamePriorityQueue()
{
	iWAM_QueueSize = 0;
	pWAM_QueueBegin = new WAMPriorityNode(new WAMGameMapNode(FVector(0,0,0),false));
	pWAM_QueueEnd   = new WAMPriorityNode(new WAMGameMapNode(FVector(0,0,0),true ));
	pWAM_QueueBegin->pWAM_NextNode  = pWAM_QueueEnd;
	pWAM_QueueBegin->pWAM_PriorNode = NULL;
	pWAM_QueueEnd->pWAM_PriorNode   = pWAM_QueueBegin;
	pWAM_QueueEnd->pWAM_NextNode    = NULL;
}


void WAMGamePriorityQueue::Enqueue(WAMGameMapNode * no)
{
	WAMPriorityNode *novo = new WAMPriorityNode(no);

	/*******************************************************************/
	/*The Nodes are enqueued acoordingly with your priority            */
	/*in this case how much greater is the cost...less is your priority*/
	/*******************************************************************/
	WAMPriorityNode *temp = pWAM_QueueBegin;

	//we cannot have a empty begin node AND ENQUEUE NODE...
	if (temp == NULL || no == NULL)return;

	while (no->GetMapCost() > temp->GetMapCost())
	{
		temp = temp->pWAM_NextNode;
	}

	/****************************************/
	/*Insert the node in the prior position */
	/****************************************/
	novo->pWAM_PriorNode = temp->pWAM_PriorNode;
	novo->pWAM_NextNode  = temp;
	temp->pWAM_PriorNode = novo;
	novo->pWAM_PriorNode->pWAM_NextNode = novo;

	iWAM_QueueSize++;
}

WAMGameMapNode* WAMGamePriorityQueue::Dequeue()
{
	/******************************************/
	/*we allways remove from the beggining....*/
	/******************************************/
	WAMGameMapNode *item = NULL;
	
	if (iWAM_QueueSize > 0)
	{
		WAMPriorityNode *temp = new WAMPriorityNode();

		pWAM_QueueBegin->pWAM_NextNode->pWAM_NextNode->pWAM_PriorNode = pWAM_QueueBegin;
		temp = pWAM_QueueBegin->pWAM_NextNode;
		pWAM_QueueBegin->pWAM_NextNode = pWAM_QueueBegin->pWAM_NextNode->pWAM_NextNode;

		item = new WAMGameMapNode(*temp);
		delete temp;
	}

	iWAM_QueueSize--;

	return item;
}

void WAMGamePriorityQueue::Remove(WAMGameMapNode* no)
{
	/*************************************/
	/*Exclude without criteria...        */
	/*************************************/
	WAMPriorityNode *temp = pWAM_QueueBegin;
	while (!no->Equal(*(temp)))
	{
		temp = temp->pWAM_NextNode;
	}

	temp->pWAM_NextNode->pWAM_PriorNode = temp->pWAM_PriorNode;
	temp->pWAM_PriorNode->pWAM_NextNode = temp->pWAM_NextNode;

	iWAM_QueueSize--;

	delete temp;
}

/**************************************/
/*check if the node exists            */
/**************************************/
bool WAMGamePriorityQueue::Contain(WAMGameMapNode* no) const
{
	WAMPriorityNode *temp = pWAM_QueueBegin;

	while (temp != pWAM_QueueEnd)
	{
		if (temp->Equal(*no))
			return true;
		temp = temp->pWAM_NextNode;
	}
	return false;
}

/**************************************/
/*Clean-Up the Queue                  */
/**************************************/
void WAMGamePriorityQueue::QueueClean()
{
	while (!QueueEmpty())
	{
		Dequeue();
	}
}
