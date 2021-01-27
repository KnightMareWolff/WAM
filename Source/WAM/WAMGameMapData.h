// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "WAM.h"
#include "WAMGameMapData.generated.h"

USTRUCT(BlueprintType) struct FWAMGameMapData : public FTableRowBase 
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(BlueprintReadOnly, Category = "WAMGameInterface|WAM Game Structs")
	FString WAM_BlockDescription;

	UPROPERTY(BlueprintReadOnly, Category = "WAMGameInterface|WAM Game Structs")
	int32   WAM_BlockPosX;

	UPROPERTY(BlueprintReadOnly, Category = "WAMGameInterface|WAM Game Structs")
	int32   WAM_BlockPosY;

	UPROPERTY(BlueprintReadOnly, Category = "WAMGameInterface|WAM Game Structs")
	int32   WAM_BlockType;
};
