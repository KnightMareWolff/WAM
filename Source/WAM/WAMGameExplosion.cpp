// Fill out your copyright notice in the Description page of Project Settings.
#include "WAMGameExplosion.h"
#include "WAM.h"


WAMGameExplosion::WAMGameExplosion()
{
}

WAMGameExplosion::WAMGameExplosion(int pWAM_ExplosionState, FVector pWAM_ExplosionPosition)
{
	iWAM_ExplosionState = pWAM_ExplosionState;
	vWAM_ExplosionPosition = pWAM_ExplosionPosition;
}

WAMGameExplosion::~WAMGameExplosion()
{
}

bool WAMGameExplosion::MoveExplosion(FVector pWAM_TargetPosition)
{
	//The mask could not be placed in the Target position
	if (!MoveToLocation(pWAM_TargetPosition))
	{
		return false;
	}

	vWAM_ExplosionPosition = pWAM_TargetPosition;
	return true;
}

bool WAMGameExplosion::MoveExplosion(int pWAM_TargetDirection)
{
	FVector tActualPosition, tNextPosition;

	tActualPosition = vWAM_ExplosionPosition;
	tNextPosition = vWAM_ExplosionPosition;

	switch (pWAM_TargetDirection)
	{
	case 0: {tNextPosition.X += WAM_NODE_SIZE; }break;
	case 1: {tNextPosition.X -= WAM_NODE_SIZE; }break;
	case 2: {tNextPosition.Y -= WAM_NODE_SIZE; }break;
	case 3: {tNextPosition.Y += WAM_NODE_SIZE; }break;
	}

	//The mask could not be placed in the Target position
	if (!MoveToLocation(tNextPosition))
	{
		return false;
	}

	vWAM_ExplosionPosition = tNextPosition;
	return true;
}

FVector WAMGameExplosion::GetLocation()
{
	return vWAM_ExplosionPosition;
}

int WAMGameExplosion::GetState()
{
	return iWAM_ExplosionState;
}

bool WAMGameExplosion::SetState(int pWAM_TargetState)
{
	iWAM_ExplosionState = pWAM_TargetState;
	return true;
}