// Fill out your copyright notice in the Description page of Project Settings.
#include "WAMGameBlock.h"
#include "WAM.h"


WAMGameBlock::WAMGameBlock()
{
	iWAM_BlockType = WAM_BLOCK_TYPE_BLOCK;
	iWAM_HidenItem = 0;
	iWAM_Impacted  = false;
}

WAMGameBlock::~WAMGameBlock()
{
}
