// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTT_MoveZoneDefender.h"
#include "MyAI_Ally.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"

UMyBTT_MoveZoneDefender::UMyBTT_MoveZoneDefender()
{
	
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UMyBTT_MoveZoneDefender::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMyAI_Ally* AIAlly = Cast<AMyAI_Ally>(OwnerComp.GetAIOwner());

	//AIAlly->MoveTo()
	return EBTNodeResult::Succeeded;
}