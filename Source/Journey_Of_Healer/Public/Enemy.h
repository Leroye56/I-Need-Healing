// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameManager.h"
#include "CoreMinimal.h"
#include "Entity.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class JOURNEY_OF_HEALER_API AEnemy : public AEntity
{
	GENERATED_BODY()
public:
	AEnemy();

	virtual void OnEnterDetectionZone(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnExitDetectionZone(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	//UPROPERTY(EditAnywhere)
	//	AGameManager* gameManager;

/*protected:
	virtual void Die() override;*/

};
