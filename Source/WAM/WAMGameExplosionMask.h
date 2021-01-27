/************************************************************************************/
/*Project: Whammy Bombs - WAM                                                       */
/*----------------------------------------------------------------------------------*/
/*                                 WAMGameExplosionMask                             */
/*----------------------------------------------------------------------------------*/
/*Description:                                                                      */
/*The WAMGameExplosionMask is the class to be used to control the explosion mask    */
/*the explosions have especific rules in the map and have their own mask in the game*/
/*----------------------------------------------------------------------------------*/
/*Author: William D. Wolff - 2018                                                   */
/************************************************************************************/
#pragma once
#include "WAMGameMapMask.h"

/**
 * 
 */
class WAM_API WAMGameExplosionMask : public WAMGameMapMask
{
public:
	 WAMGameExplosionMask();
	~WAMGameExplosionMask();

	bool MoveToLocation(FVector   pWAMLocation);
	bool MoveToLocation(FVector2D pWAMLocation);
	bool SetBlockData(int pWAMBlockType, int pWAMHiddenItem, bool pWAMUpdated);
};
