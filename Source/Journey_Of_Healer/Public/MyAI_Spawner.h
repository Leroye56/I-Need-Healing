// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpawnerEntity.h"
#include "CoreMinimal.h"
#include "AIController.h"

#include "MyAI_Spawner.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_OF_HEALER_API AMyAI_Spawner : public AAIController
{
	GENERATED_BODY()

public:
	AMyAI_Spawner(const FObjectInitializer& ObjectInitializer);

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(transient)
		class UBehaviorTreeComponent* BTC;

	UPROPERTY(transient)
		class UBlackboardComponent* BBC;

	ASpawnerEntity* spawner;

	uint8 EnemyKeyId;
};
