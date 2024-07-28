// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameFramework/Actor.h"
#include <VoxelLevelArray.h>
#include <FChunk.h>
#include <RealtimeMeshComponent.h>
#include "VoxelLevelStreamer.generated.h"


// Class that creates chunks
UCLASS()
class AIPATHINGPROJECT_API AVoxelLevelStreamer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVoxelLevelStreamer();

	// For generating and using voxel worlds within 
	// editor or during play.
	UFUNCTION(BlueprintCallable)
	void LoadVoxelWorldData();

	UFUNCTION(BlueprintCallable)
	void GenerateVoxelWorldData();

	UFUNCTION(BlueprintCallable)
	void SaveVoxelWorldData();

	UFUNCTION(BlueprintCallable)
	void CreateVoxelWorld();

	// Defines layout and size of data within chunks
	UPROPERTY(EditAnywhere);
	int chunkWidth = 64;

	UPROPERTY(EditAnywhere);
	int chunkHeight = 64;

	UPROPERTY(EditAnywhere);
	int chunkLength = 64;

	UPROPERTY(EditAnywhere);
	int noChunkWidth = 1;

	UPROPERTY(EditAnywhere);
	int noChunkHeight = 1;

	UPROPERTY(EditAnywhere);
	int noChunkLength = 1;


	// Chunk class to spawn
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UClass* chunkClass;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

	TArray<FChunk> Verticies;

	FChunk GenerateChunk(FVector pos);

	int32 getBlockAtPos(int32 x, int32 y, int32 z);

	// Delegates for saves
	void saveGameDelegate(const FString& SlotName, const int32 UserIndex, bool bSuccess);
	void loadGameDelegate(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData);

};
