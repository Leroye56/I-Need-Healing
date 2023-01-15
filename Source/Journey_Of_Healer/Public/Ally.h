// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/CapsuleComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "CoreMinimal.h"
#include "Entity.h"
#include "Ally.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_OF_HEALER_API AAlly : public AEntity
{
	GENERATED_BODY()
public:
	AAlly();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void NotInvincible();

	virtual void OnEnterDetectionZone(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnExitDetectionZone(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	int NbZoneDefender;

	UPROPERTY(EditAnywhere, Category = "Ally", DisplayName = "timeInvincible")
		float timeInvincible;
};