// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "VoxelLevelArray.generated.h"

/**
 * 
 */
UCLASS()
class AIPATHINGPROJECT_API UVoxelLevelArray : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TArray<FVector> Blocks;
};
