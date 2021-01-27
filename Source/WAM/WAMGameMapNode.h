/************************************************************************************/
/*Project: Whammy Bombs - WAM                                                       */
/*----------------------------------------------------------------------------------*/
/*                                 WAMGameMapNode                                   */
/*----------------------------------------------------------------------------------*/
/*Description:                                                                      */
/*The WAMGameMapNode is the base class to be used as a container of a x,y location. */
/*all the game are being developed with cubes and this can give to us a lot of      */
/*information since in the future, dungeons and other classes can be developed.     */
/*----------------------------------------------------------------------------------*/
/*Author: William D. Wolff - 2018                                                   */
/************************************************************************************/
#pragma once
#include "WAMGameBlock.h"

#define WAM_NODE_SIZE 100
#define BLOCKED       3000

/**
 * 
 */
class WAM_API WAMGameMapNode
{
public:
	 WAMGameMapNode();
	 WAMGameMapNode(FVector pWAM_Position, int pBlockType, int pHiddenItem);
	 WAMGameMapNode(FVector pWAM_Position, bool PrtyEndNode);
	 WAMGameMapNode(const WAMGameMapNode &copy);
	~WAMGameMapNode();

	 virtual WAMGameMapNode &operator= (const WAMGameMapNode &opr);
	 virtual bool            operator==(const WAMGameMapNode &opr);
	 virtual bool            operator< (const WAMGameMapNode &opr);
	 virtual bool            operator> (const WAMGameMapNode &opr);

	 virtual bool ResetNode();

	 virtual bool Equal(const WAMGameMapNode &opr) const
	 {
		 return ((vWAM_Position.X == opr.vWAM_Position.X) && (vWAM_Position.Y == opr.vWAM_Position.Y));
	 }

	 //We have the costs in the Map
	 virtual void SetMapCost(const int pWAM_MapCost);
	 virtual int  GetMapCost(                      ) const;

	 //We have the costs calculated during the game...based on the costs in the map
	 virtual void SetPathCost(const int pWAM_PathCost);
	 virtual int  GetPathCost(                       ) const;

	 //Map Logic Pointers & Organization
	 FVector       vWAM_Position;
	 WAMGameBlock *pWAM_Block;

	 //Map Algorithm Informations
	 bool          bWAM_Updated;

	 //PathFinder Algorith Informations
	 WAMGameMapNode *pWAM_Father;
	 int             iWAM_Cost;
	 int             iWAM_g;
	 int             iWAM_f;
	 int             iWAM_h;
};
