/************************************************************************************/
/*Project: Whammy Bombs - WAM                                                       */
/*----------------------------------------------------------------------------------*/
/*                                 WAMGameExplosion                                 */
/*----------------------------------------------------------------------------------*/
/*Description:                                                                      */
/*The WAMGameExplosion is the class to be used to control a explosion that occours. */
/*the explosions have especific rules in the map and have their own mask in the game*/
/*----------------------------------------------------------------------------------*/
/*Author: William D. Wolff - 2018                                                   */
/************************************************************************************/
#pragma once
#include "WAMGameExplosionMask.h"

#define WAM_EXPLOSION_ST_BORN      0
#define WAM_EXPLOSION_ST_SWITCHED  1
#define WAM_EXPLOSION_ST_EXPLODING 2
#define WAM_EXPLOSION_ST_EXTINCT   3
/**
 * 
 */
class WAM_API WAMGameExplosion : public WAMGameExplosionMask
{
public:
	 WAMGameExplosion();
	 WAMGameExplosion(int pWAM_ExplosionState, FVector pWAM_ExplosionPosition);
	~WAMGameExplosion();

	bool MoveExplosion(FVector pWAM_TargetPosition);
	bool MoveExplosion(int     pWAM_TargetDirection);

	FVector GetLocation();
	int     GetState();

	bool    SetState(int pWAM_TargetState);

private:
	int     iWAM_ExplosionState;
	FVector vWAM_ExplosionPosition;
	int     iWAM_ExplosionPower;
};
