// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameManager.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTT_MoveZoneDefender.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_OF_HEALER_API UMyBTT_MoveZoneDefender : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UMyBTT_MoveZoneDefender();

	AGameManager* gameManager;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
