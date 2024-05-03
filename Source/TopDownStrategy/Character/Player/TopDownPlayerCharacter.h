// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TopDownStrategy/Character/TopDownCharacterBase.h"
#include "TopDownPlayerCharacter.generated.h"

UCLASS(Blueprintable)
class ATopDownPlayerCharacter : public ATopDownCharacterBase
{
	GENERATED_BODY()

public:
	ATopDownPlayerCharacter();

	// Called every frame.
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UTopDownCameraComponent> CameraComponent;
};

