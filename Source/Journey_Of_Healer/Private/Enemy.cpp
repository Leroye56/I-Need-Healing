// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Ally.h"

AEnemy::AEnemy() : AEntity::AEntity()
{
}
void AEnemy::OnEnterDetectionZone(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnEnterDetectionZone( OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

 	if (OtherActor->GetClass()->IsChildOf(AAlly::StaticClass()))
		TargetList.push_back(Cast<AEntity>(OtherActor));
	
}
void AEnemy::OnExitDetectionZone(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnExitDetectionZone(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);

	if (OtherActor->GetClass()->IsChildOf(AAlly::StaticClass()))
	{
		for(int i = 0; i < TargetList.size(); i++)
			if(TargetList[i] == OtherActor)
			{
				TargetList.erase(TargetList.begin()+i);
				break;
			}
	}
}

//void AEnemy::Die()
//{
//	Destroy();
//	gameManager->Score += 100;
//}