// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorsPool.h"
#include "Engine/GameEngine.h"

// Sets default values for this component's properties
UActorsPool::UActorsPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AActor* UActorsPool::CheckOut()
{
	if (Pool.Num() == 0) { return nullptr;}
	UE_LOG(LogTemp, Warning, TEXT("[%s] Checkout."), *GetName());
	return Pool.Pop();
}

void UActorsPool::Return(AActor* ActortToReturn)
{
	Add(ActortToReturn);
	//if (ActortToReturn == nullptr)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("[%s] Null actor returned"), *(this->GetName()));
	//	return;
	//}
	//UE_LOG(LogTemp, Warning, TEXT("[%s] Actor returned :[%s]."), *GetName(),*ActortToReturn->GetName());
}

void UActorsPool::Add(AActor* ActorToAdd)
{
	Pool.Push(ActorToAdd);
	//if (ActorToAdd == nullptr)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("[%s] Null actor Added"), *GetName());
	//	return;
	//}
	//UE_LOG(LogTemp, Warning, TEXT(" Actor added : %s"),*ActorToAdd->GetName());
}
