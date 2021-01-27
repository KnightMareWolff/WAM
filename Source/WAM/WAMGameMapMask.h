/************************************************************************************/
/*Project: Whammy Bombs - WAM                                                       */
/*----------------------------------------------------------------------------------*/
/*                                 WAMGameMapMask                                   */
/*----------------------------------------------------------------------------------*/
/*Description:                                                                      */
/*The WAMGameMapMask is the base class to be used as a navigation mask thru the Map.*/
/*With this technique we made the Map static and make possible access just 1 Map in */
/*many diferent navigation masks                                                    */
/*For Example: The explosion mask will change dinamically depending on the power of */
/*the bomb, so when a explosion occours the navigation mask will get the necessary  */
/*nodes to calculate the bomb impact and this is reflected in the game informing how*/
/*many actos need be spawned and where...etc...                                     */
/*----------------------------------------------------------------------------------*/
/*Author: William D. Wolff - 2018                                                   */
/************************************************************************************/
#pragma once
#include "WAMGameMap.h"

class WAM_API WAMGameMapMask
{
public:
	 WAMGameMapMask();
	~WAMGameMapMask();

	virtual bool MoveToLocation(FVector   pWAMLocation);
	virtual bool MoveToLocation(FVector2D pWAMLocation);
	virtual bool SetBlockData  (int pWAMBlockType,int pWAMHiddenItem,bool pWAMUpdated);

protected:
	WAMGameMapNode *pWAM_North;
	WAMGameMapNode *pWAM_South;
	WAMGameMapNode *pWAM_Lest;
	WAMGameMapNode *pWAM_West;
	WAMGameMapNode *pWAM_Center;

	FVector   pWAM_3DLocation;
	FVector2D pWAM_2DLocation;
};
