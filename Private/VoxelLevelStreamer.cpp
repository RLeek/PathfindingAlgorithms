// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelLevelStreamer.h"
#include <RealtimeMeshSimple.h>
#include <Kismet/GameplayStatics.h>
#include <VoxelLevelSave.h>
#include "GameFramework/SaveGame.h"
#include <VoxelChunk.h>

// Sets default values
AVoxelLevelStreamer::AVoxelLevelStreamer()
{	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AVoxelLevelStreamer::LoadVoxelWorldData()
{
	UE_LOG(LogTemp, Warning, TEXT("LoadVoxelWorld"));
	// Set up the delegate.
	FAsyncLoadGameFromSlotDelegate LoadedDelegate;
	// USomeUObjectClass::LoadGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData
	LoadedDelegate.BindUObject(this, &AVoxelLevelStreamer::loadGameDelegate);
	UGameplayStatics::AsyncLoadGameFromSlot("TestSaveSlot", 0, LoadedDelegate);
}

void AVoxelLevelStreamer::GenerateVoxelWorldData()
{
	// This should generate a struct of the terrain
	// Then the chunk object should receive a readonly (can't really ensure this)
		// But it should be readOnly

	Verticies.SetNum(noChunkLength * noChunkWidth);
	UE_LOG(LogTemp, Warning, TEXT("GenerateVoxelWorld"));
	for (float x = 0; x < noChunkLength; x++) {
		for (float y = 0; y < noChunkWidth; y++) {
			 FVector pos = FVector(x * 10 * 50, y * 10 * 50, 0); //  Note specify that 50 is the block size
			// When we spawn it we need to make sure it actually generates properly
			// AActor* newChunk = GetWorld()->SpawnActor(chunkClass, new FTransform(pos));
			// So chunk is y first then x so, it is  
			Verticies[x + (y*noChunkLength)] = GenerateChunk(pos);
		}
	}
}

void AVoxelLevelStreamer::SaveVoxelWorldData()
{
	UE_LOG(LogTemp, Warning, TEXT("SaveVoxelWorld"));

	if (UVoxelLevelSave* SaveGameInstance = Cast<UVoxelLevelSave>(UGameplayStatics::CreateSaveGameObject(UVoxelLevelSave::StaticClass())))
	{
		// Set up the (optional) delegate.
		FAsyncSaveGameToSlotDelegate SavedDelegate;
		// USomeUObjectClass::SaveGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, bool bSuccess
		SavedDelegate.BindUObject(this, &AVoxelLevelStreamer::saveGameDelegate);

		// Set data on the savegame object.
		SaveGameInstance->Verticies = Verticies;

		// Start async save process.
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, "TestSaveSlot", 0, SavedDelegate);
	}
}

// Called when the game starts or when spawned
void AVoxelLevelStreamer::BeginPlay()
{
	Super::BeginPlay();
	
}

FChunk AVoxelLevelStreamer::GenerateChunk(FVector pos)
{
	FChunk chunkData = FChunk();
	chunkData.pos = pos;
	// We should replace this with a TStaticArray when we can.
	chunkData.blocks = TArray<EBlocks>();
	chunkData.blocks.SetNum(chunkHeight * chunkLength *chunkWidth);

	int32 resolution = 1;
	// For every point we want to generate a block
	for (int x = 0; x < chunkLength; x++) {
		for (int y = 0; y < chunkWidth; y++) {
			// Use noise to generate a random value between 1-height
			// then fill that number of z with stone blocks, followed by air blocks
			int groundHeight = FMath::Clamp(FMath::Abs(FMath::PerlinNoise2D(FVector2D((1.0f / (resolution * chunkWidth)) * (pos.X + x), 1.0f / (resolution * chunkLength) * (pos.Y + y)))) * chunkHeight, 0, chunkHeight);

			for (int z = 0; z < chunkHeight; z++) {
				if (z <= groundHeight) {
					if (z >= groundHeight - 3) {
						chunkData.blocks[getBlockAtPos(x, y, z)] = EBlocks::Dirt;
					}
					else {
						chunkData.blocks[getBlockAtPos(x, y, z)] = EBlocks::Stone;
					}
				}
				else {
					chunkData.blocks[getBlockAtPos(x, y, z)] = EBlocks::Air;
				}
			}
		}
	}

	return chunkData;
}

int32 AVoxelLevelStreamer::getBlockAtPos(int32 x, int32 y, int32 z)
{
	return x + y * chunkWidth + z * (chunkWidth * chunkLength);
}

void AVoxelLevelStreamer::saveGameDelegate(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	UE_LOG(LogTemp, Warning, TEXT("Goose step"));
}

void AVoxelLevelStreamer::loadGameDelegate(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData)
{
	UE_LOG(LogTemp, Warning, TEXT("Groose step"));
}


void AVoxelLevelStreamer::CreateVoxelWorld()
{
	UE_LOG(LogTemp, Warning, TEXT("CreateVoxelWorld"));
	for (float x = 0; x < noChunkLength; x++) {
		for (float y = 0; y < noChunkWidth; y++) {
			AVoxelChunk* newChunk = (AVoxelChunk*)GetWorld()->SpawnActor(chunkClass, new FTransform(Verticies[x + (y * noChunkLength)].pos));
			newChunk->initialize(Verticies[x + (y * noChunkLength)]);
		}
	}
}

// Called every frame
void AVoxelLevelStreamer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
