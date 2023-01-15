// Fill out your copyright notice in the Description page of Project Settings.


#include "GetTarget.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Journey_Of_HealerGameMode.h"
#include "Entity.h"
#include "Ally.h"
#include "Zone.h"

UGetTarget::UGetTarget()
{
    bCreateNodeInstance = true;
}

EBTNodeResult::Type UGetTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    //AActor* actorTarget = Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn());
    AEntity* actorTarget = Cast<AEntity>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("SelfActor")));
    if (actorTarget->TargetList.size() > 0)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject("Target", actorTarget->TargetList[0]);
    }
    else
    {
        if(Cast<AAlly>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("SelfActor"))) == nullptr)
            OwnerComp.GetBlackboardComponent()->SetValueAsObject("Target", OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("King")));
        else
        {
            AJourney_Of_HealerGameMode* GameMode = Cast<AJourney_Of_HealerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
            OwnerComp.GetBlackboardComponent()->SetValueAsObject("Target", Cast<UObject>(GameMode->ZoneArray[Cast<AAlly>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("SelfActor")))->NbZoneDefender]));
        }
    }

    return EBTNodeResult::Succeeded;
}