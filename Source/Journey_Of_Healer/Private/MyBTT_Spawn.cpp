// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTT_Spawn.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTT_Spawn::UMyBTT_Spawn()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UMyBTT_Spawn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMyAI_Spawner* Spawner = Cast<AMyAI_Spawner>(OwnerComp.GetAIOwner());
	Spawner->spawner->Spawn();

	return EBTNodeResult::Succeeded;
}