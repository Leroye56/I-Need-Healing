// Fill out your copyright notice in the Description page of Project Settings.


#include "Ally.h"
#include "Enemy.h"

AAlly::AAlly() : AEntity::AEntity()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called every frame
void AAlly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (invincible)
	{
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AAlly::NotInvincible, timeInvincible, false);
	}
}

void AAlly::NotInvincible()
{
	invincible = false;
}

void AAlly::OnEnterDetectionZone(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnEnterDetectionZone(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (OtherActor->GetClass()->IsChildOf(AEnemy::StaticClass()))
		TargetList.push_back(Cast<AEntity>(OtherActor));

}
void AAlly::OnExitDetectionZone(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnExitDetectionZone(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);

	if (OtherActor->GetClass()->IsChildOf(AEnemy::StaticClass()))
	{
		for (int i = 0; i < TargetList.size(); i++)
			if (TargetList[i] == OtherActor)
			{
				TargetList.erase(TargetList.begin() + i);
				break;
			}
	}
}