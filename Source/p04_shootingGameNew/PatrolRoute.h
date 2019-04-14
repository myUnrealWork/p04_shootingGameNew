// Fill out your copyright notice in the Description page of Project Settings.

/*
* Accessing blueprint variables through C++
* https://answers.unrealengine.com/questions/161741/accessing-blueprint-variables-through-c.html
*/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRoute.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class P04_SHOOTINGGAMENEW_API UPatrolRoute : public UActorComponent
{
	GENERATED_BODY()

public:
	TArray<AActor*> GetPatrolPoints() const;

protected:

private:
	UPROPERTY(EditInstanceOnly, Category = "Patrol Route")
		TArray<AActor*> PatrolPoints;
		
};
