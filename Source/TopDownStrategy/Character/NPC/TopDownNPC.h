// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TopDownStrategy/Character/TopDownCharacterBase.h"
#include "TopDownNPC.generated.h"

UCLASS()
class TOPDOWNSTRATEGY_API ATopDownNPC : public ATopDownCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATopDownNPC();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<class UTopDownUnitConfig> UnitConfig;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
