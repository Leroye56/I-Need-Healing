// Fill out your copyright notice in the Description page of Project Settings.


#include "item.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Entity.h"
#include "Ally.h"
#include "Enemy.h"

// Sets default values
Aitem::Aitem()
{
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("itemMesh"));
	mesh->SetCollisionProfileName(TEXT("Trigger"));
	mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

void Aitem::OnAttackTouch(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (refMaster != nullptr)
	{
		if (refMaster->IsAtacking && !asTouch)
		{
			AEntity* actorTarget = Cast<AEntity>(OtherActor);
			AAlly* IfTargetIsAlly = Cast<AAlly>(OtherActor);
			AEnemy* IfTargetIsEnemy = Cast<AEnemy>(OtherActor);
			AAlly* IfMasterIsAlly = Cast<AAlly>(refMaster);
			AEnemy* IfMasterIsEnemy = Cast<AEnemy>(refMaster);
			if ((IfTargetIsAlly != nullptr || IfTargetIsEnemy != nullptr) && !((IfTargetIsAlly != nullptr && IfMasterIsAlly != nullptr) || (IfTargetIsEnemy != nullptr && IfMasterIsEnemy != nullptr)))
			{
				if (!actorTarget->invincible)
				{
					actorTarget->TakeDamages(refMaster->atk);
					if (actorTarget->pv > 0)
						actorTarget->OnAttacked();
					else
						actorTarget->OnDie();
					asTouch = true;
				}
			}
		}
	}
}
void Aitem::BeginPlay()
{
	Super::BeginPlay();
	asTouch = false;
	mesh->OnComponentBeginOverlap.AddUniqueDynamic(this, &Aitem::OnAttackTouch);
}

void Aitem::setParentRef(AEntity* Entity)
{
	refMaster = Entity;
}
void Aitem::Reset()
{
	asTouch = false;
}