// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Ally.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h" 

/**
 * 
 */

#include "MyAI_Ally.generated.h"
UCLASS()
class JOURNEY_OF_HEALER_API AMyAI_Ally : public AAIController
{
	GENERATED_BODY()
public:
	AMyAI_Ally();
	virtual void OnPossess(APawn* InPawn) override;

	UBehaviorTreeComponent* m_BehaviorTreeComponent;
	UBlackboardComponent* m_BlackboardComponent;

	UPROPERTY(EditAnywhere, Category = AI)
		class UBehaviorTree* BehaviorTree;

	AAlly* ally;

	uint8 AllyKeyId;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
