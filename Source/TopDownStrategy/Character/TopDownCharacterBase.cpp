// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownCharacterBase.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "TopDownStrategy/GameObject/TopDownGameState.h"
#include "TopDownStrategy/Character/NPC/Data/NPCData.h"


// Sets default values
ATopDownCharacterBase::ATopDownCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATopDownCharacterBase::ReceiveDamage(float DamageToTake)
{
	Health -= DamageToTake;
	if (Health < 0)
	{
		Destroy();
	}
}

void ATopDownCharacterBase::SetStats(FNPCData& NPCData)
{
	MaxHealth = NPCData.MaxHealth;
	Health = NPCData.MaxHealth;
	Damage = NPCData.Damage;
	CombatRange = NPCData.CombatRange;
	ProjectileSpeed = NPCData.ProjectileSpeed;
	DetectionRange = NPCData.DetectionRange;
	GetCharacterMovement()->MaxWalkSpeed = NPCData.MoveSpeed;
}

// Called when the game starts or when spawned
void ATopDownCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATopDownCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATopDownCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

