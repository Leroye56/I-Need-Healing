// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAI_Ally.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"


AMyAI_Ally::AMyAI_Ally()
{
	m_BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Component"));
}

void AMyAI_Ally::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UseBlackboard(BehaviorTree->BlackboardAsset, m_BlackboardComponent);

	m_BehaviorTreeComponent->StartTree(*BehaviorTree);

}
void AMyAI_Ally::BeginPlay()
{
	Super::BeginPlay();

	//TODO OR DELETE
}