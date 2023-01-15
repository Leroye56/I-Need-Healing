// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTT_Attack.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_OF_HEALER_API UMyBTT_Attack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UMyBTT_Attack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
