// Fill out your copyright notice in the Description page of Project Settings.


#include "SetAtkBoolValue.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Entity.h"

USetAtkBoolValue::USetAtkBoolValue()
{
    bCreateNodeInstance = true;
}

EBTNodeResult::Type USetAtkBoolValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("shouldAttack"), valueToSet);
    return EBTNodeResult::Succeeded;
}