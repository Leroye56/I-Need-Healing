// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyAI_Spawner.h"
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTT_Spawn.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_OF_HEALER_API UMyBTT_Spawn : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UMyBTT_Spawn();

	//AMyAI_Spawner* AISpawner;

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
};
