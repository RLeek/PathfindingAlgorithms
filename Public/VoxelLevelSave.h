// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include <FChunk.h>
#include "VoxelLevelSave.generated.h"

/**
 * 
 */
UCLASS()
class AIPATHINGPROJECT_API UVoxelLevelSave : public USaveGame
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	TArray<FChunk> Verticies;
};
