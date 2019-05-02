// Fill out your copyright notice in the Description page of Project Settings.


#include "InfiniteMapGameMode.h"
#include "Navmesh/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "Engine/GameEngine.h"
#include "ActorsPool.h"
#include "Classes/Kismet/GameplayStatics.h"

AInfiniteMapGameMode::AInfiniteMapGameMode()
{
	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorsPool>(FName(TEXT("NMBV Pool")));
}

void AInfiniteMapGameMode::PopulateBoundsVolumePool()
{
	//-- 第一种遍历方法
	// -- TActorIterator<ANavMeshBoundsVolume> VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	// -- auto VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	TActorIterator<ANavMeshBoundsVolume> VolumeIterator(GetWorld());
	while (VolumeIterator)
	{
		AddToPool(*VolumeIterator);
		++VolumeIterator;
	}


	//-- 第二种遍历方法
	//TArray<AActor*> FoundActors;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);

	//for (AActor* TActor : FoundActors)
	//{
	//	ANavMeshBoundsVolume* MyActor = Cast<ANavMeshBoundsVolume>(TActor);

	//	if (MyActor != nullptr)
	//		AddToPool(MyActor);
	//}
}

void AInfiniteMapGameMode::AddToPool(ANavMeshBoundsVolume* VolumeToAdd)
{
	FString str = "Found Actors :" + VolumeToAdd->GetName();
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, str);

	NavMeshBoundsVolumePool->Add(VolumeToAdd);
}