// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "p04_shootingGameNewGameMode.h"
#include "Navmesh/NavMeshBoundsVolume.h"
#include "InfiniteMapGameMode.generated.h"

class UActorsPool;

/**
 * 
 */
UCLASS()
class P04_SHOOTINGGAMENEW_API AInfiniteMapGameMode : public Ap04_shootingGameNewGameMode
{
	GENERATED_BODY()

public:

	AInfiniteMapGameMode();

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void PopulateBoundsVolumePool();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pool")
		UActorsPool* NavMeshBoundsVolumePool;

private:

	void AddToPool(class ANavMeshBoundsVolume *VolumeToAdd);
	
};
