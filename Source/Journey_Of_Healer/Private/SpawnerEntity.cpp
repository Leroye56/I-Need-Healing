// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerEntity.h"

// Sets default values
ASpawnerEntity::ASpawnerEntity()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnerEntity::BeginPlay()
{
	Super::BeginPlay();
	Location = GetActorLocation();
	Rotation = GetActorRotation();
	
}

// Called every frame
void ASpawnerEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASpawnerEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASpawnerEntity::Spawn()
{
	for (int i=0; i < nbEntitySpawnPerWave; i++)
	{
		FActorSpawnParameters parameters;
		AActor* SpawnActorRef = GetWorld()->SpawnActor<AActor>(Entity, Location, Rotation, parameters);
		if (Cast<AAlly>(SpawnActorRef))
		{
			gameManager->ListeAllies.Add(Cast<AAlly>(SpawnActorRef));
			gameManager->ListeAllies.Last()->NbZoneDefender = i;
		}
		//else if(Cast<AEnemy>(SpawnActorRef))
		//{
		//	gameManager->ListeEnemies.Add(Cast<AEnemy>(SpawnActorRef));
		//	gameManager->ListeEnemies.Last()->gameManager = gameManager;
		//}
		
	}
}

