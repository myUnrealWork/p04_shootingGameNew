// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tiles.generated.h"

USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()
	FVector Location;
	float Rotation;
	float Scale;
};

class UActorsPool;

UCLASS()
class P04_SHOOTINGGAMENEW_API ATiles : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATiles();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
		void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinNumSpawn = 1, int MaxNumSpawn = 1, float Radius = 300, float MinScale = 1, float MaxScale = 1);
	
	UFUNCTION(BlueprintCallable, Category = "Spawning")
		void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int MinNumSpawn = 1, int MaxNumSpawn = 1, float Radius = 300);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EEndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		FVector MinPosition;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		FVector MaxPosition;
	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
		FVector NavigationBoundsOffset;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// TODO visible
	UFUNCTION(BlueprintCallable, Category = "Pool")
		void SetPool(UActorsPool* Pool);

private:

	TArray<FSpawnPosition> RandomSpawnPositions(int MinNumSpawn, int MaxNumSpawn, float MinScale, float MaxScale, float Radius);

	void PositionNavMeshBoundsVolume();

	bool FindEmptyLocation(FVector& OutLocation, float Radius);

	template<class T>
	void RandomlyPlaceActors(TSubclassOf<T> ToSpawn, int MinNumSpawn = 1, int MaxNumSpawn = 1, float Radius = 300, float MinScale = 1, float MaxScale = 1);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition& SpawnPosition);

	void PlaceActor(TSubclassOf<APawn> ToSpawn, const FSpawnPosition& SpawnPosition);

	bool CanSpawnAtLocation(FVector Location, float Radius);

	UActorsPool* Pool;

	AActor* NavMeshBoundsVolume;
};
