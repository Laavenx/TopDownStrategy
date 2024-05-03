// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TopDownGameState.generated.h"

struct FNPCData;

UCLASS()
class TOPDOWNSTRATEGY_API ATopDownGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATopDownGameState();

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> NPCStats;

	bool GetNPCData(FName Name, FNPCData& OutNPCData);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
