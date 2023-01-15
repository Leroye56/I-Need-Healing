// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingProjectile.h"

// Sets default values
AHealingProjectile::AHealingProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if (!CollisionComponent)
	{
		// Use a sphere as a simple collision representation.
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		// Set the sphere's collision radius.
		CollisionComponent->InitSphereRadius(15.f);
		// Set the sphere's collision profile name to "HealingProjectile".
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("HealingProjectile"));
		
		// Set the root component to be the collision component.
		RootComponent = CollisionComponent;
	}

	if (!ProjectileMovementComponent)
	{
		// Use this component to drive this projectile's movement.
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 3000.f;
		ProjectileMovementComponent->MaxSpeed = 3000.f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	if (!ProjectileMeshComponent)
	{
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/Assets/Sphere.Sphere'"));
		if (Mesh.Succeeded())
		{
			ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
		}
	}

	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("'/Game/Assets/SphereMaterial.SphereMaterial'"));
	if (Material.Succeeded())
	{
		ProjectileMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);
	}
	ProjectileMeshComponent->SetMaterial(0, ProjectileMaterialInstance);
	ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
	ProjectileMeshComponent->SetupAttachment(RootComponent);

	// Delete the projectile after x seconds.
	InitialLifeSpan = 3.f;
}

// Called when the game starts or when spawned
void AHealingProjectile::BeginPlay()
{
	Super::BeginPlay();
	// Event called when component hits pawn.
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AHealingProjectile::OnHit);
}

// Called every frame
void AHealingProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function that initializes the projectile's velocity in the shoot direction.
void AHealingProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

// Function that is called when the projectile hits something.
void AHealingProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor->GetClass()->IsChildOf(AAlly::StaticClass()))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, FString::Printf(TEXT("Touch ally")));
		Cast<AEntity>(OtherActor)->AddPV(Cast<AEntity>(OtherActor)->heal);

		Destroy();
	}
}