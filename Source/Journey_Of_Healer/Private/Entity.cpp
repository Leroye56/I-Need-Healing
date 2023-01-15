// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity.h"
#include "Math/UnrealMathUtility.h"
#include "Components/ChildActorComponent.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
// Sets default values
AEntity::AEntity()
{
	_rightHand = CreateDefaultSubobject<UChildActorComponent>(TEXT("RightHand"));
	
	_rightHand->CreateChildActor();
	
	_rightHand->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "hand_r");

	DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Detetion Sphere Component"));
	DetectionSphere->InitSphereRadius(300.0f);
	DetectionSphere->SetCollisionProfileName(TEXT("Trigger"));
	DetectionSphere->SetupAttachment(RootComponent);

	if(rightHand != nullptr)
		UE_LOG(LogTemp, Warning, TEXT("Working"));
}
void AEntity::PlayAnimationMontage(UAnimMontage* p_animMontage, bool& p_notifyBool, void (AEntity::* p_function)(void), void (AEntity::* p_functionR)(void))
{ 
	if (!p_notifyBool)
	{
		p_notifyBool = true;
		if (p_animMontage != nullptr)
		{
			float montageDuration = GetMesh()->AnimScriptInstance->Montage_Play(p_animMontage); 
			FTimerHandle _;
			FTimerHandle _b;
			GetWorldTimerManager().SetTimer(_, this, p_function, montageDuration, false);
			GetWorldTimerManager().SetTimer(_b, this, p_functionR, montageDuration+dps, false);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Dwarf - Anim Montage is missing (have you filled the blueprint ?) -> Skipping animation"));
		}
	}
}


void AEntity::OnEnterDetectionZone(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//DrawDebugSphere(GetWorld(), GetActorLocation(), 300.f, 50, FColor::Green, true, -1, 0, 2);
}
void AEntity::OnExitDetectionZone(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//DrawDebugSphere(GetWorld(), GetActorLocation(), 300.f, 50, FColor::Green, true, -1, 0, 2);
}

void AEntity::Attack()
{
	//GetMesh()->AnimScriptInstance->Montage_Play(attackAnimMontage);
	IsAtacking = true;
	this->PlayAnimationMontage(attackAnimMontage, IsAnim, &AEntity::ResetIsAtacking, &AEntity::ResetAnim);
}
void AEntity::OnAttacked()
{
	//this->PlayAnimationMontage(damageAnimMontage, IsAtacking, nullptr);
	this->PlayAnimationMontage(damageAnimMontage, IsDamage, &AEntity::Nothig, &AEntity::ResetDamaging);
}
void AEntity::OnDie()
{
	//this->PlayAnimationMontage(deathAnimMontage, IsAtacking, nullptr);
	this->PlayAnimationMontage(deathAnimMontage, IsDamage, &AEntity::Die, &AEntity::Nothig);

}
void AEntity::BeginPlay()
{
	Super::BeginPlay();

	maxPv = pv;

	IsAtacking = false;
	IsAnim = false;
	IsDamage = false;

	_rightHand->SetChildActorClass(rightHand);

	DetectionSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &AEntity::OnEnterDetectionZone);
	DetectionSphere->OnComponentEndOverlap.AddUniqueDynamic(this, &AEntity::OnExitDetectionZone);
	if((Aitem*)_rightHand->GetChildActor() != nullptr)
		((Aitem*)_rightHand->GetChildActor())->setParentRef(this);
}

void AEntity::TakeDamages(const int& p_damages)
{
	pv = FMath::Clamp(pv - p_damages, 0, maxPv);
}
void AEntity::AddPV(const int& p_pv)
{
	pv = FMath::Clamp(pv + p_pv, 0, maxPv);

	auto mat = GetMesh()->GetMaterial(0);

	if (mat)
	{
		auto realMat = Cast<UMaterialInstanceDynamic>(mat->GetMaterial());
		if (!realMat)
		{
			realMat = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
		}
		realMat->SetScalarParameterValue("Damaged", 1);
	}

	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([&]
		{
			auto mat = GetMesh()->GetMaterial(0);

			if (mat)
			{
				auto realMat = Cast<UMaterialInstanceDynamic>(mat->GetMaterial());
				if (!realMat)
				{
					realMat = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
				}
				realMat->SetScalarParameterValue("Damaged", 0);
			}
		});

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.5, false);
}

void AEntity::ResetIsAtacking()
{
	IsAtacking = false;
	if ((Aitem*)_rightHand->GetChildActor() != nullptr)
		((Aitem*)_rightHand->GetChildActor())->Reset();
}
void AEntity::ResetDamaging()
{
	IsDamage = false;
}
void AEntity::Die()
{
	Destroy();
}

void AEntity::ResetAnim()
{
	IsAnim = false;
}
void AEntity::Nothig(){}