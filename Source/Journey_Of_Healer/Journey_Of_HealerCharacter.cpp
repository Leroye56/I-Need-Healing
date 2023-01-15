// Copyright Epic Games, Inc. All Rights Reserved.

#include "Journey_Of_HealerCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AJourney_Of_HealerCharacter

AJourney_Of_HealerCharacter::AJourney_Of_HealerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	heal = 5;
	hps = 10;
	buff = true;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AJourney_Of_HealerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AJourney_Of_HealerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("HealingProjectile", IE_Pressed, this, &AJourney_Of_HealerCharacter::StartHealingProjectile);
	PlayerInputComponent->BindAction("BuffZone", IE_Pressed, this, &AJourney_Of_HealerCharacter::SpawnBuffZoneClass);

	PlayerInputComponent->BindAxis("MoveForward", this, &AJourney_Of_HealerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AJourney_Of_HealerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AJourney_Of_HealerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AJourney_Of_HealerCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AJourney_Of_HealerCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AJourney_Of_HealerCharacter::TouchStopped);
}

void AJourney_Of_HealerCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AJourney_Of_HealerCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AJourney_Of_HealerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AJourney_Of_HealerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AJourney_Of_HealerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AJourney_Of_HealerCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AJourney_Of_HealerCharacter::StartHealingProjectile()
{
	if (!armUp)
	{
		AnimationHealing();
	}
	// Attempt to fire a projectile.
	if (ProjectileClass)
	{
		// Reset timer here
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AJourney_Of_HealerCharacter::StopHealingProjectile, timerForArm, false);
		// Get the camera transform.
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		// Set MuzzleOffset to spawn projectiles slightly in front of the camera.
		MuzzleOffset.Set(100.0f, 0.0f, 100.0f);

		// Transform MuzzleOffset from camera space to world space.
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

		// Skew the aim to be slightly upwards.
		FRotator MuzzleRotation = CameraRotation;
		MuzzleRotation.Pitch += 10.0f;

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// Spawn the projectile at the muzzle.
			AHealingProjectile* Projectile = World->SpawnActor<AHealingProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				// Set the projectile's initial trajectory.
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
	
}

void AJourney_Of_HealerCharacter::AnimationHealing()
{
	// Begin timer here
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AJourney_Of_HealerCharacter::StopHealingProjectile, timerForArm, false);

	armUp = true;
	GetMesh()->AnimScriptInstance->Montage_Play(startHealingMontage);
}

void AJourney_Of_HealerCharacter::StopHealingProjectile()
{
	armUp = false;
	GetMesh()->AnimScriptInstance->Montage_Play(endHealingMontage);
}

void AJourney_Of_HealerCharacter::SpawnBuffZoneClass()
{
	if (buff)
	{
		//If the usefulactorbp is valid
		if (buffZoneClass)
		{
			//Spawn parameters for the current spawn.
			//We can use this for a number of options like disable collision or adjust the spawn position
			//if a collision is happening in the spawn point etc..
			FActorSpawnParameters SpawnParams;

			//Actual Spawn. The following function returns a reference to the spawned actor
			ACollisionBuffZone* ActorRef = GetWorld()->SpawnActor<ACollisionBuffZone>(buffZoneClass, GetTransform(), SpawnParams);
			firstbuffZone = ActorRef;
		}
		buff = false;
		// Wait 50s  to put back ult to true
		GetWorldTimerManager().SetTimer(coolDownBuff, this, &AJourney_Of_HealerCharacter::CoolDownBuff, timerCoolDownBuff, false);
	}
	
}

void AJourney_Of_HealerCharacter::CoolDownBuff()
{
	firstbuffZone->Destroy();
	buff = true;
}