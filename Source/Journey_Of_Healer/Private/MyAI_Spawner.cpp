// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAI_Spawner.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"


AMyAI_Spawner::AMyAI_Spawner(const FObjectInitializer& ObjectInitializer)
{
	BBC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoard Component"));
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree Component"));
}

void AMyAI_Spawner::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	spawner = Cast<ASpawnerEntity>(InPawn);

	BBC->InitializeBlackboard(*spawner->BehaviorTree->BlackboardAsset);

	BTC->StartTree(*spawner->BehaviorTree);

	EnemyKeyId = BBC->GetKeyID("SelfActor");
	BBC->SetValueAsClass("Spawner", spawner->GetClass());
	BBC->SetValueAsFloat("TimeBetweenToWave", spawner->timeBetweenWave);

}
