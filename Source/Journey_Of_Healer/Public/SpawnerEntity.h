// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BehaviorTree.h"
#include "GameManager.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpawnerEntity.generated.h"

UCLASS()
class JOURNEY_OF_HEALER_API ASpawnerEntity : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpawnerEntity();

	UPROPERTY(EditAnywhere, Category = "Spawner")
		TSubclassOf<AActor> Entity;
	UPROPERTY(EditAnywhere, Category = "Spawner")
		int nbEntitySpawnPerWave;
	UPROPERTY(EditAnywhere, Category = "Spawner")
		float timeBetweenWave;

	UPROPERTY(EditAnywhere, Category = "GameManager")
		AGameManager* gameManager;

	UPROPERTY(EditAnywhere, Category = "AI")
		UBehaviorTree* BehaviorTree;

	FVector Location = GetActorLocation();
	FRotator Rotation = GetActorRotation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Spawn();

};
