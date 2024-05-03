// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "TopDownCameraComponent.generated.h"


struct FInputActionValue;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOPDOWNSTRATEGY_API UTopDownCameraComponent : public UCameraComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTopDownCameraComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
						   FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CameraMovementSpeed = 900;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CameraRotationSpeed = 0.5f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	
	void SetupInputs();
	void MoveCameraInput(const FInputActionValue& Value);
	void MouseLook(const FInputActionValue& Value);
	
	float MoveForwardValue = 0;
	float MoveRightValue = 0;
	float MouseLookUpValue = 0;
	float MouseLookRightValue = 0;

	FVector MoveCameraForward(float DeltaTime);
	FVector MoveCameraRight(float DeltaTime);
};
