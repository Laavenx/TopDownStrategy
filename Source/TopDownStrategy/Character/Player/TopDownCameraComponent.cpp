// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownCameraComponent.h"

#include "InputTriggers.h"
#include "TopDownPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Chaos/CollisionResolutionUtil.h"


// Sets default values for this component's properties
UTopDownCameraComponent::UTopDownCameraComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTopDownCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	SetupInputs();
	auto OwnerLocation = GetOwner()->GetActorLocation();
	SetWorldLocation(FVector(OwnerLocation.X - 300, OwnerLocation.Y, OwnerLocation.Z + 300));
	SetWorldRotation(FRotator(-45,0,0));
	FieldOfView = 90;
}

// Called every frame
void UTopDownCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                    FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector ActualLocation = GetComponentLocation();
	FVector ActualMovement = FVector::ZeroVector;

	ActualMovement += MoveCameraForward(DeltaTime);
	ActualMovement += MoveCameraRight(DeltaTime);
	ActualLocation += ActualMovement;
	SetWorldLocation(ActualLocation);

	auto LookUpRot = FRotator(MouseLookUpValue,0,0);
	auto LookRightRot = FRotator(0,MouseLookRightValue,0);
	auto NewRotation = LookUpRot + LookRightRot;
	SetWorldRotation(GetComponentRotation() + NewRotation);
	
	MoveForwardValue = 0;
	MoveRightValue = 0;
	MouseLookUpValue = 0;
	MouseLookRightValue = 0;
}

void UTopDownCameraComponent::SetupInputs()
{
	//GetOwner()->GetInstigatorController()
	const ATopDownPlayerController* PlayerController = Cast<ATopDownPlayerController>(GetWorld()->GetFirstPlayerController());
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerController->InputComponent))
	{
		EnhancedInputComponent->BindAction(PlayerController->MoveCamera, ETriggerEvent::Triggered, this, &UTopDownCameraComponent::MoveCameraInput);
		EnhancedInputComponent->BindAction(PlayerController->MouseLook, ETriggerEvent::Triggered, this, &UTopDownCameraComponent::MouseLook);
	}
}

void UTopDownCameraComponent::MoveCameraInput(const FInputActionValue& Value)
{
	const FVector2d ArrowKey = Value.Get<FVector2d>();

	MoveForwardValue = ArrowKey.Y;
	MoveRightValue = ArrowKey.X;
}

void UTopDownCameraComponent::MouseLook(const FInputActionValue& Value)
{
	const FVector2d Look = Value.Get<FVector2d>();
	MouseLookUpValue = Look.Y;
	MouseLookRightValue = Look.X;
}

FVector UTopDownCameraComponent::MoveCameraForward(float DeltaTime)
{
	float MovementValue = MoveForwardValue * DeltaTime * CameraMovementSpeed;
	FVector DeltaMovement = MovementValue * GetComponentTransform().Rotator().Vector();
	return DeltaMovement;
}

FVector UTopDownCameraComponent::MoveCameraRight(float DeltaTime)
{
	float MovementValue = MoveRightValue * DeltaTime * CameraMovementSpeed;
	FVector DeltaMovement = MovementValue * (FRotator(0.0f, 90.0f, 0.0f) +
		FRotator(0.0f, GetComponentTransform().Rotator().Yaw, 0.0f)).Vector();
	return DeltaMovement;
}

