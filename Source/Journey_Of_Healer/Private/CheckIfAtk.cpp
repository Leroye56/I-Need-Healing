// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckIfAtk.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"

UCheckIfAtk::UCheckIfAtk()
{
    bCreateNodeInstance = true;
}

EBTNodeResult::Type UCheckIfAtk::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("shouldAttack")))
        return EBTNodeResult::Succeeded;
    return EBTNodeResult::Failed;
}