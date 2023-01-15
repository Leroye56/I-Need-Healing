// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "item.generated.h"

UCLASS()
class JOURNEY_OF_HEALER_API Aitem : public AActor
{
	GENERATED_BODY()
	
public :	
	// Sets default values for this actor's properties
	Aitem();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", DisplayName = "Mesh")
		class UStaticMeshComponent* mesh;

	UFUNCTION()
		virtual void OnAttackTouch(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void setParentRef(class AEntity* Entity);
	void Reset();
protected:
	virtual void BeginPlay() override;

	bool asTouch;
	class AEntity* refMaster;
};
