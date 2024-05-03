// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TopDownBaseAIController.generated.h"

UCLASS()
class TOPDOWNSTRATEGY_API ATopDownBaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATopDownBaseAIController();

	void OnPossess(APawn* InPawn) override;
	void SetupBlackboard(AActor* Actor);

	UFUNCTION()
	void OnPerceptionUpdate(const TArray<AActor*>& UpdatedActors);

	UFUNCTION()
	void OnTargetPerceptionForgotten(AActor* Actor);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;
	TObjectPtr<class UAISenseConfig_Sight> AISenseSightConfig;

protected:
	virtual void BeginPlay() override;

	// virtual void Tick(float DeltaTime) override;
};
