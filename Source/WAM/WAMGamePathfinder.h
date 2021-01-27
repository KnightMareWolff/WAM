// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "WAMGameMap.h"
#include "WAMGamePriorityQueue.h"
#include "WAMPathFinderMask.h"

/*************************************/
/*Process Enumerator                 */
/*************************************/
typedef enum ONGOING
{
	SEARCHING,
	FINDTHEPATH,
	IMPOSSIBLE
}STDONGOING;

/**
 * 
 */
class WAM_API WAMGamePathfinder : public WAMPathFinderMask
{
public:
	 WAMGamePathfinder();
	~WAMGamePathfinder();

	TArray<WAMGameMapNode*> GetPath();

	bool                    FindPath(WAMGameMapNode* pWAM_Start, WAMGameMapNode* pWAM_End);

private:

	STDONGOING           Pass();
	void                 Reset();
	int                  Estimate      (WAMGameMapNode* pWAM_Visitor);
	void                 Visit         (WAMGameMapNode* pWAM_Visitor);
	void                 SetSearchNodes(WAMGameMapNode* pWAM_Start   , WAMGameMapNode* pWAM_End);


	WAMGamePriorityQueue  qWAM_OpenQueue;
	WAMGamePriorityQueue  qWAM_ClosedQueue;
	WAMGameMapNode       *nWAM_Start,
		                 *nWAM_Actual,
		                 *nWAM_End;
	float                 fWAM_HeuristicHeight;
};
