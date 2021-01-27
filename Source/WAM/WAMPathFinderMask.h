/************************************************************************************/
/*Project: Whammy Bombs - WAM                                                       */
/*----------------------------------------------------------------------------------*/
/*                                 WAMPathFinderMask                                */
/*----------------------------------------------------------------------------------*/
/*Description:                                                                      */
/*The WAMPathFinderMask is the class to be used to control the navigation in the map*/
/*during the pathfinding operations                                                 */
/*----------------------------------------------------------------------------------*/
/*Author: William D. Wolff - 2018                                                   */
/************************************************************************************/
#pragma once
#include "WAMGameMapMask.h"

/**
 * 
 */
class WAM_API WAMPathFinderMask : public WAMGameMapMask
{
public:
	 WAMPathFinderMask();
	~WAMPathFinderMask();

	bool MoveToLocation(FVector   pWAMLocation);
	bool MoveToLocation(FVector2D pWAMLocation);

	WAMGameMapNode *pWAM_NorthLest;
	WAMGameMapNode *pWAM_NorthWest;
	WAMGameMapNode *pWAM_SouthLest;
	WAMGameMapNode *pWAM_SouthWest;
};
