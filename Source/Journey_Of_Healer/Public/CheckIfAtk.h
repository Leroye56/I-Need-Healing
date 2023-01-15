// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CheckIfAtk.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_OF_HEALER_API UCheckIfAtk : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UCheckIfAtk();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
