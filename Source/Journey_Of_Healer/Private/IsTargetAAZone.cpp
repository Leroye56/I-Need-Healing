// Fill out your copyright notice in the Description page of Project Settings.


#include "IsTargetAAZone.h"
#include "Zone.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"

UIsTargetAAZone::UIsTargetAAZone()
{
    bCreateNodeInstance = true;
}

EBTNodeResult::Type UIsTargetAAZone::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (Cast<AZone>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target"))) == nullptr)
        return EBTNodeResult::Failed;
    return EBTNodeResult::Succeeded;
}