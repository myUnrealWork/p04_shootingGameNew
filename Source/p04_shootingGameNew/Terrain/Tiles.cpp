// Fill out your copyright notice in the Description page of Project Settings.


#include "Tiles.h"
#include "Engine/GameEngine.h"
#include "DrawDebugHelpers.h"
#include "ActorsPool.h"
#include "NavigationSystem.h"

// Sets default values
ATiles::ATiles()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MinPosition = FVector(0, -2000, 0);
	MaxPosition = FVector(4000, 2000, 0);

	NavigationBoundsOffset = FVector(2000, 0, 0);

}

// Called when the game starts or when spawned
void ATiles::BeginPlay()
{
	Super::BeginPlay();
	
	CanSpawnAtLocation(GetActorLocation(), 300);
}

void ATiles::EndPlay(const EEndPlayReason::Type EEndPlayReason)
{
	Super::EndPlay(EEndPlayReason);
	if (Pool != nullptr && NavMeshBoundsVolume != nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] EndPlay."), *GetName());
		Pool->Return(NavMeshBoundsVolume);
	}
}

// Called every frame
void ATiles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

template<class T>
void ATiles::RandomlyPlaceActors(TSubclassOf<T> ToSpawn, int MinNumSpawn, int MaxNumSpawn, float Radius, float MinScale, float MaxScale)
//TArray<FSpawnPosition> ATiles::RandomSpawnPositions(int MinNumSpawn, int MaxNumSpawn, float MinScale, float MaxScale, float Radius)
{
	//TArray<FSpawnPosition> SPawnPositionArray;
	int NumberToSpawn = FMath::RandRange(MinNumSpawn, MaxNumSpawn);
	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		//随机生成信息 //存储到结构体
		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(MinScale, MaxScale);
		bool found = FindEmptyLocation(SpawnPosition.Location, Radius * SpawnPosition.Scale);
		//spawn生成
		if (found)
		{
			SpawnPosition.Rotation = FMath::RandRange(-180.f, 180.f);
			//SPawnPositionArray.Add(SpawnPosition);
			PlaceActor(ToSpawn, SpawnPosition);
		}
	}
}

void ATiles::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinNumSpawn, int MaxNumSpawn, float Radius, float MinScale, float MaxScale)
{
	//TArray<FSpawnPosition> SPawnPositionArray = RandomSpawnPositions(MinNumSpawn, MaxNumSpawn, MinScale, MaxScale, Radius);
	//for (FSpawnPosition SpawnPosition : SPawnPositionArray)
	//{
	//	PlaceActor(ToSpawn, SpawnPosition);
	//}
	RandomlyPlaceActors(ToSpawn, MinNumSpawn, MaxNumSpawn, Radius, MinScale, MaxScale);
}

void ATiles::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int MinNumSpawn, int MaxNumSpawn, float Radius)
{
	RandomlyPlaceActors(ToSpawn, MinNumSpawn, MaxNumSpawn, Radius, 1, 1);
}

bool ATiles::FindEmptyLocation(FVector& OutLocation, float Radius)
{
	FBox BoundsOfMap(MinPosition, MaxPosition);
	const int MAX_ATTEMPTS = 100;
	for (size_t i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector CandidatePoint = FMath::RandPointInBox(BoundsOfMap);
		if (CanSpawnAtLocation(CandidatePoint, Radius))
		{
			OutLocation = CandidatePoint;
			return true;
		}
	}
	return false;
}

void ATiles::PlaceActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition& SpawnPosition)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	if (Spawned)
	{
		Spawned->SetActorRelativeLocation(SpawnPosition.Location);
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		Spawned->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
		Spawned->SetActorScale3D(FVector(SpawnPosition.Scale));
	}
}

void ATiles::PlaceActor(TSubclassOf<APawn> ToSpawn,const FSpawnPosition& SpawnPosition)
{
	FRotator Rotation = FRotator(0, SpawnPosition.Rotation, 0);
	APawn* Spawned = GetWorld()->SpawnActor<APawn>(ToSpawn, SpawnPosition.Location,Rotation);
	if (Spawned)
	{
		//Spawned->SetActorRelativeLocation(SpawnPosition.Location);
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		//Spawned->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
		Spawned->SpawnDefaultController();//添加AI控制器
		Spawned->Tags.Add(FName("Enemy"));
	}
}


bool ATiles::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		GlobalLocation,
		GlobalLocation + 0.0001f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius)
	);
	//FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
	//DrawDebugSphere(GetWorld(), GlobalLocation, Radius, 100, ResultColor, true, 100);
	//DrawDebugCapsule(GetWorld(), GlobalLocation, 0, Radius, FQuat::Identity, ResultColor, true, 100);
	//UE_LOG(LogTemp, Warning, TEXT("Gun %s"), HasHit);
	return !HasHit;
}

void ATiles::SetPool(UActorsPool* InPool)
{
	if (!InPool) return;
	UE_LOG(LogTemp, Warning, TEXT("Here!!!! %s "), *(InPool->GetName()));
	Pool = InPool;

	PositionNavMeshBoundsVolume();
}

void ATiles::PositionNavMeshBoundsVolume()
{
	// 从pool中获取
	NavMeshBoundsVolume = Pool->CheckOut();
	if (NavMeshBoundsVolume == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] Not enough actors in pool."),*GetName());
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT(" [%s] Check out: [%s] "), *GetName(),*NavMeshBoundsVolume->GetName());
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavigationBoundsOffset);
	UNavigationSystemV1::GetNavigationSystem(GetWorld())->Build();
}
