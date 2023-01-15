// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "King.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h" 

/**
 * 
 */

#include "MyAI_Enemy.generated.h"
UCLASS()
class JOURNEY_OF_HEALER_API AMyAI_Enemy : public AAIController
{
	GENERATED_BODY()
public:
	AMyAI_Enemy();
	virtual void OnPossess(APawn* InPawn) override;
	UPROPERTY(EditAnywhere, Category = AI)
	UBehaviorTreeComponent* m_BehaviorTreeComponent;
	UPROPERTY(EditAnywhere, Category = AI)
	UBlackboardComponent* m_BlackboardComponent;

	AKing* king;

	UPROPERTY(EditAnywhere, Category = AI)
	class UBehaviorTree* BehaviorTree;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
