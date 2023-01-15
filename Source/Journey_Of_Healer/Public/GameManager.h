// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Ally.h"
//#include "Enemy.h"
#include "Engine/TargetPoint.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameManager.generated.h"

UCLASS()
class JOURNEY_OF_HEALER_API AGameManager : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGameManager();

	UPROPERTY(EditAnywhere, Category = "ZoneDefender")
		TArray<ATargetPoint*> ListeZoneDefender;

	TArray<AAlly*> ListeAllies;

	//TArray<AEnemy*> ListeEnemies;

	int Score;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
