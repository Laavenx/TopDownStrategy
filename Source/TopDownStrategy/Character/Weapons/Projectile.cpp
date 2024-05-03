// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "TopDownStrategy/Character/TopDownCharacterBase.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));\
	StaticMeshComponent->SetCollisionProfileName(FName("OverlapOnlyPawn"));
	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComponent->SetStaticMesh(StaticMesh);
	StaticMeshComponent->SetWorldScale3D(FVector(0.3,0.3,0.3));
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(TargetActor))
	{
		FVector VectorTowards = (TargetActor->GetActorLocation() - GetActorLocation());
		VectorTowards.Normalize();
		auto DistToTravel = VectorTowards * DeltaTime * ProjectileSpeed;
		SetActorLocation(GetActorLocation() + DistToTravel);
	}
	else
	{
		Destroy();
	}
}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == TargetActor)
	{
		TargetActor->ReceiveDamage(DamageToDo);
		Destroy();
	}
}

