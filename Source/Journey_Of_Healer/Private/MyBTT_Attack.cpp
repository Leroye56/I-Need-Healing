// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTT_Attack.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Entity.h"

UMyBTT_Attack::UMyBTT_Attack()
{
    bCreateNodeInstance = true;
}

EBTNodeResult::Type UMyBTT_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AEntity* actorTarget = Cast<AEntity>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("SelfActor")));
    actorTarget->Attack();
    return EBTNodeResult::Succeeded;
}