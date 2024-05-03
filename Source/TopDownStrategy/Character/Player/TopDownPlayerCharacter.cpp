// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownPlayerCharacter.h"

#include "TopDownCameraComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "TopDownStrategy/Character/NPC/Data/NPCData.h"
#include "TopDownStrategy/GameObject/TopDownGameState.h"

ATopDownPlayerCharacter::ATopDownPlayerCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	CameraComponent = CreateDefaultSubobject<UTopDownCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->bUsePawnControlRotation = false;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ATopDownPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	auto NPCDataDatabase = Cast<ATopDownGameState>(GetWorld()->GetGameState());
	
	FNPCData NPCData;
	if (NPCDataDatabase->GetNPCData(FName("Player"), NPCData))
	{
		SetStats(NPCData);
		GetCharacterMovement()->MaxWalkSpeed = NPCData.MoveSpeed;
	}
}

void ATopDownPlayerCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}
