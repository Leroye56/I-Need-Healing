// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "SetAtkBoolValue.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_OF_HEALER_API USetAtkBoolValue : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	USetAtkBoolValue();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BTT", DisplayName = "Value To Set")
		bool valueToSet;
};
