// Fill out your copyright notice in the Description page of Project Settings.


#include "GetPlayer.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"

UGetPlayer::UGetPlayer()
{
    bCreateNodeInstance = true;
}

EBTNodeResult::Type UGetPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AActor* actorPlayer = Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn());
    OwnerComp.GetBlackboardComponent()->SetValueAsObject("Target", actorPlayer);
    return EBTNodeResult::Succeeded;
}