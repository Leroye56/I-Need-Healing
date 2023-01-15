// Fill out your copyright notice in the Description page of Project Settings.


#include "Zone.h"
#include "Kismet/GameplayStatics.h"
#include "../Journey_Of_HealerGameMode.h"

// Sets default values
AZone::AZone()
{
}

// Called when the game starts or when spawned
void AZone::BeginPlay()
{
	Super::BeginPlay();
	AJourney_Of_HealerGameMode* GameMode = Cast<AJourney_Of_HealerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->ZoneArray.Add(this);
}
