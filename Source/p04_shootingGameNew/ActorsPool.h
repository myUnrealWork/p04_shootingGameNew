// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorsPool.generated.h"


UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class P04_SHOOTINGGAMENEW_API UActorsPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorsPool();

	AActor* CheckOut();

	void Return(AActor* ActortToReturn);

	void Add(AActor* ActorToAdd);

private:
	TArray<AActor*> Pool;
};
