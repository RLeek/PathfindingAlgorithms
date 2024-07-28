// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <EBlocks.h>
#include "FChunk.generated.h"

/**
 * 
 */
USTRUCT()
struct FChunk
{
	GENERATED_BODY()

	// position of chunk
	FVector pos;

	// Blocks in chunk
	TArray<EBlocks> blocks;
};
