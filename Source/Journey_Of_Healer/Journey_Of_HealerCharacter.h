// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Public/Entity.h"
#include "Components/ChildActorComponent.h"
#include "Public/CollisionBuffZone.h"
#include "Public/HealingProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Journey_Of_HealerCharacter.generated.h"

UCLASS(config=Game)
class AJourney_Of_HealerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "TimerHandle")
		FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, Category = "Player", DisplayName = "CoolDownBuff")
		FTimerHandle coolDownBuff;
public:
	AJourney_Of_HealerCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
		//UParticleSystem* HealingEmitter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UAnimMontage* startHealingMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UAnimMontage* endHealingMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player", DisplayName = "Heal")
		int heal;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player", DisplayName = "HealPerSecond")
		int hps;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player", DisplayName = "Big Buff")
		bool buff;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", DisplayName = "armUp")
		bool armUp = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", DisplayName = "timerForArm")
		float timerForArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", DisplayName = "timerCoolDownBuff")
		float timerCoolDownBuff;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ACollisionBuffZone* firstbuffZone;
	// Gun muzzle offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AHealingProjectile> ProjectileClass;

	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
		TSubclassOf<class ACollisionBuffZone> buffZoneClass;

	UPROPERTY(EditDefaultsOnly, Category = buffZone)
		UChildActorComponent* buffZone;

	/*Spawns the UsefulActor Blueprint*/
	UFUNCTION()
		void SpawnBuffZoneClass();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void CoolDownBuff();

	// Function that handles firing healing projectiles.
	void StartHealingProjectile();

	void AnimationHealing();

	void StopHealingProjectile();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

