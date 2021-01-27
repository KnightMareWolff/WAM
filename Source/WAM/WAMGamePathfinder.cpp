// Fill out your copyright notice in the Description page of Project Settings.

#include "WAM.h"
#include "WAMGamePathfinder.h"

WAMGamePathfinder::WAMGamePathfinder()
{
	nWAM_Actual          = NULL;
	fWAM_HeuristicHeight = 5000.0f;
}

WAMGamePathfinder::~WAMGamePathfinder()
{
	
}


STDONGOING WAMGamePathfinder::Pass()
{
	if (!qWAM_OpenQueue.QueueEmpty())
	{
		nWAM_Actual = qWAM_OpenQueue.Dequeue();
		
		if (nWAM_Actual->Equal(*nWAM_End))
		{
			return FINDTHEPATH;
		}

		if (MoveToLocation(nWAM_Actual->vWAM_Position))
		{
			Visit(pWAM_North);
			Visit(pWAM_South);
			Visit(pWAM_Lest);
			Visit(pWAM_West);
			//Visit(pWAM_NorthLest);
			//Visit(pWAM_NorthWest);
			//Visit(pWAM_SouthLest);
			//Visit(pWAM_SouthWest);

			qWAM_ClosedQueue.Enqueue(nWAM_Actual);
			return SEARCHING;
		}
	}

	return IMPOSSIBLE;
}



void WAMGamePathfinder::Visit(WAMGameMapNode* pWAM_Visitor)
{
	int new_g;

	if (pWAM_Visitor->GetMapCost() == BLOCKED)
		return;

	new_g = nWAM_Actual->iWAM_g + pWAM_Visitor->GetMapCost();


	if ((qWAM_OpenQueue  .Contain(pWAM_Visitor) || 
		 qWAM_ClosedQueue.Contain(pWAM_Visitor) )  && pWAM_Visitor->iWAM_g <= new_g) return;


	pWAM_Visitor->pWAM_Father = nWAM_Actual;
	pWAM_Visitor->iWAM_g      = new_g;
	pWAM_Visitor->iWAM_h      = Estimate(pWAM_Visitor);
	pWAM_Visitor->iWAM_f      = pWAM_Visitor->iWAM_g + pWAM_Visitor->iWAM_h;


	if (qWAM_ClosedQueue.Contain(pWAM_Visitor))
	{
		qWAM_ClosedQueue.Remove(pWAM_Visitor);
	}

	if (!qWAM_OpenQueue.Contain(pWAM_Visitor))
	{
		qWAM_OpenQueue.Enqueue(pWAM_Visitor);
	}
	else
	{
		qWAM_OpenQueue.Remove (pWAM_Visitor);
		qWAM_OpenQueue.Enqueue(pWAM_Visitor);
	}
}
/**************************************/
/*Limpa para nova Busca               */
/**************************************/
void WAMGamePathfinder::Reset()
{	
	qWAM_OpenQueue.QueueClean();
	qWAM_ClosedQueue.QueueClean();

	nWAM_Actual = NULL;

	nWAM_Start->iWAM_g = 0;
	nWAM_Start->iWAM_h = Estimate(nWAM_Start);
	nWAM_Start->iWAM_f = nWAM_Start->iWAM_g + nWAM_Start->iWAM_h;

	qWAM_OpenQueue.Enqueue(nWAM_Start);
}

int WAMGamePathfinder::Estimate(WAMGameMapNode *pWAM_Visitor)
{
	int est;

	est = (int)floorf(sqrtf((float)(pWAM_Visitor->vWAM_Position.X - nWAM_End->vWAM_Position.X) *
		                           (pWAM_Visitor->vWAM_Position.X - nWAM_End->vWAM_Position.X) +
		                    (float)(pWAM_Visitor->vWAM_Position.Y - nWAM_End->vWAM_Position.Y) *
		                           (pWAM_Visitor->vWAM_Position.Y - nWAM_End->vWAM_Position.Y)));

	return (int)(est*fWAM_HeuristicHeight);
}

void WAMGamePathfinder::SetSearchNodes(WAMGameMapNode* pWAM_Start, WAMGameMapNode* pWAM_End)
{
	nWAM_Start = pWAM_Start;
    nWAM_End   = pWAM_End;
}

bool WAMGamePathfinder::FindPath(WAMGameMapNode* pWAM_Start, WAMGameMapNode* pWAM_End)
{
	STDONGOING PathSearchState;
	
	SetSearchNodes(pWAM_Start, pWAM_End);
	
	Reset();

	while ((PathSearchState = Pass()) == SEARCHING);

	if (PathSearchState == FINDTHEPATH)return true;
	if (PathSearchState == IMPOSSIBLE)
	{
		nWAM_Actual = NULL;
		nWAM_End    = NULL;
		nWAM_Start  = NULL;
		return false;
	}

	//never happen but...
	return true;
}

TArray<WAMGameMapNode*> WAMGamePathfinder::GetPath()
{ 
	TArray<WAMGameMapNode*> tPath;
	WAMGameMapNode* tNode;

	tNode = nWAM_End;
	if (tNode != NULL)
	{
		tPath.Add(tNode);

		while (tNode->pWAM_Father != NULL)
		{
			tNode = tNode->pWAM_Father;
			tPath.Add(tNode);
		}
	}
	
	return tPath;
}