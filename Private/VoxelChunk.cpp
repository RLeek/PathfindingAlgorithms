// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelChunk.h"
#include <FChunk.h>

// Sets default values
AVoxelChunk::AVoxelChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AVoxelChunk::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVoxelChunk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVoxelChunk::initialize(FChunk chunk)
{
	chunkData = chunk;
	// do the other initialization steps here;
	// Note: The chunk should be readonly!! (It should never change)
}

