// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <vector>
#include "item.h"

#include "Entity.generated.h"

UCLASS()
class JOURNEY_OF_HEALER_API AEntity : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEntity();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Entity", DisplayName = "RightHand", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<Aitem> rightHand;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Entity", DisplayName = "_RightHand", meta = (AllowPrivateAccess = "true"))
		class UChildActorComponent* _rightHand;
	UPROPERTY(VisibleAnywhere, Category = "Entity", meta = (AllowPrivateAccess = "true"))
		class USphereComponent* DetectionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Entity", DisplayName = "Invincible")
		bool invincible;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Entity", DisplayName = "PointLife")
		int pv;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Entity", DisplayName = "Heal")
		int heal;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Entity", DisplayName = "DamagePerSecond")
		float dps;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Entity", DisplayName = "Attack")
		int atk;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Entity", DisplayName = "Attack Montage")
		UAnimMontage* attackAnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Entity", DisplayName = "Damage Montage")
		UAnimMontage* damageAnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Entity", DisplayName = "Death Montage")
		UAnimMontage* deathAnimMontage;
 

	virtual void Attack();
	virtual void OnAttacked();
	virtual void OnDie();

	UFUNCTION(BlueprintCallable, Category = "Entity")
		virtual void TakeDamages(const int& p_damages);
	UFUNCTION(BlueprintCallable, Category = "Entity")
		virtual void AddPV(const int& p_pv);

	UFUNCTION()
		virtual void OnEnterDetectionZone(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		virtual void OnExitDetectionZone(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	std::vector<AEntity*> TargetList;
	bool IsAtacking;
	bool IsAnim;
protected:
	int maxPv;
	virtual void BeginPlay() override;

	bool IsDamage;

	void ResetIsAtacking();
	void ResetDamaging();
	void Die();

	void ResetAnim();
	void Nothig();

private:
	void PlayAnimationMontage(UAnimMontage* p_animMontage, bool& p_notifyBool, void (AEntity::* p_function)(void), void (AEntity::* p_functionR)(void));

};
