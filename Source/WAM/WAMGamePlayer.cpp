// Fill out your copyright notice in the Description page of Project Settings.

#include "WAM.h"
#include "WAMGamePlayer.h"

WAMGamePlayer::WAMGamePlayer()
{
}

WAMGamePlayer::WAMGamePlayer(int pWAM_PlayerState, FVector pWAM_PlayerPosition)
{
	iWAM_PlayerState   = pWAM_PlayerState;
	vWAM_PlayerPosition= pWAM_PlayerPosition;
	iWAM_Munition   = 2;
	iWAM_Protection = 2;
}

WAMGamePlayer::~WAMGamePlayer()
{
}

bool WAMGamePlayer::MovePlayer(FVector pWAM_TargetPosition)
{
	//The mask could not be placed in the Target position
	if (!MoveToLocation(pWAM_TargetPosition))
	{
		return false;
	}

	vWAM_PlayerPosition = pWAM_TargetPosition;
	return true;
}

bool WAMGamePlayer::MovePlayer(int pWAM_TargetDirection)
{
	FVector tActualPosition, tNextPosition;

	tActualPosition = vWAM_PlayerPosition;
	tNextPosition   = vWAM_PlayerPosition;
	
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

	vWAM_PlayerPosition = tNextPosition;
	return true;
}

FVector WAMGamePlayer::GetLocation()
{
	return vWAM_PlayerPosition;
}

int WAMGamePlayer::GetState()
{
	return iWAM_PlayerState;
}

int WAMGamePlayer::GetMunition()
{
	return iWAM_Munition;
}

int WAMGamePlayer::GetProtection()
{
	return iWAM_Protection;
}

bool WAMGamePlayer::SetState(int pWAM_TargetState)
{
	iWAM_PlayerState = pWAM_TargetState;
	return true;
}

bool WAMGamePlayer::PushMunition()
{
	iWAM_Munition += 1;
	return true;
}

bool WAMGamePlayer::PushProtection()
{
	iWAM_Protection += 1;
	return true;
}

bool WAMGamePlayer::PopMunition()
{
	if (iWAM_Munition == 0)return false;
	iWAM_Munition -= 1;
	return true;
}

bool WAMGamePlayer::PopProtection()
{
	if (iWAM_Protection == 0)return false;
	iWAM_Protection -= 1;
	return true;
}