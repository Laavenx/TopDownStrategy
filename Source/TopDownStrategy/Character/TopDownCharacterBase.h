// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TopDownCharacterBase.generated.h"

UCLASS()
class TOPDOWNSTRATEGY_API ATopDownCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATopDownCharacterBase();
	
	void ReceiveDamage(float Damage);
	void SetStats(struct FNPCData& NPCData);
	float GetDamage() { return Damage; }
	float GetCombatRange() { return CombatRange; }
	float GetProjectileSpeed() { return ProjectileSpeed; }
	float GetDetectionRange() { return DetectionRange; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float MaxHealth;
	float Health;
	float Damage;
	float CombatRange;
	float ProjectileSpeed;
	float DetectionRange;
};
