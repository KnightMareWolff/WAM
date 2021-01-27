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
#include "WAMGameMapMask.h"

/**
 * 
 */
class WAM_API WAMGamePlayer : public WAMGameMapMask
{
public:
	 WAMGamePlayer();
	 WAMGamePlayer(int pWAM_PlayerState, FVector pWAM_PlayerPosition);
	~WAMGamePlayer();

	bool MovePlayer(FVector pWAM_TargetPosition );
	bool MovePlayer(int     pWAM_TargetDirection);

	FVector GetLocation();
	int     GetState();
	int     GetMunition();
	int     GetProtection();

	bool    SetState(int pWAM_TargetState);
	bool    PushMunition();
	bool    PopMunition();
	bool    PushProtection();
	bool    PopProtection();

private:
	int     iWAM_PlayerState;
	int     iWAM_Munition;
	int     iWAM_Protection;
	FVector vWAM_PlayerPosition;
};
