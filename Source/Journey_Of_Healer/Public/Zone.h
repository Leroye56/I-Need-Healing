// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Zone.generated.h"

UCLASS()
class JOURNEY_OF_HEALER_API AZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
