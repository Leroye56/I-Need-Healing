// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAI_Enemy.h"

#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "../Journey_Of_HealerGameMode.h"


AMyAI_Enemy::AMyAI_Enemy()
{
	m_BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Component"));
}

void AMyAI_Enemy::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UseBlackboard(BehaviorTree->BlackboardAsset, m_BlackboardComponent);

	m_BehaviorTreeComponent->StartTree(*BehaviorTree);

	this->GetBlackboardComponent()->SetValueAsObject(TEXT("King"), king);
}
void AMyAI_Enemy::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> actorGM;
	TSubclassOf<AKing> classToFind = AKing::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, actorGM);

	if (actorGM.Num() != 0)
	{
		king = Cast<AKing>(actorGM.Last());
	}
	
	
}