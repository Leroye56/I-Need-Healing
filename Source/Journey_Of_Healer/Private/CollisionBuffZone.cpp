// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionBuffZone.h"

// Sets default values
ACollisionBuffZone::ACollisionBuffZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!CollisionComponent)
	{
		// Use a sphere as a simple collision representation.
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		// Set the sphere's collision radius.
		CollisionComponent->InitSphereRadius(320.0f);

		// Set the root component to be the collision component.
		RootComponent = CollisionComponent;
	}
}

// Called when the game starts or when spawned
void ACollisionBuffZone::BeginPlay()
{
	Super::BeginPlay();
	// Event called when component hits pawn.
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ACollisionBuffZone::OnHit);
}

// Called every frame
void ACollisionBuffZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function that is called when the projectile hits something.
void ACollisionBuffZone::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor->GetClass()->IsChildOf(AAlly::StaticClass()))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, FString::Printf(TEXT("Touch ally")));
		Cast<AEntity>(OtherActor)->invincible = true;
	}
}