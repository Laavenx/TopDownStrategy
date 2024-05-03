// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TopDownPlayerCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/KismetMathLibrary.h"
#include "TopDownStrategy/Character/NPC/TopDownNPC.h"
#include "TopDownStrategy/Character/Weapons/Projectile.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ATopDownPlayerController::ATopDownPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void ATopDownPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	
	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ATopDownPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ATopDownPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ATopDownPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ATopDownPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ATopDownPlayerController::OnSetDestinationReleased);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATopDownPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void ATopDownPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ATopDownPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// look for enemy pawn hit
		FHitResult PawnHit;
		bool bPawnHitSuccessful = false;
		bPawnHitSuccessful = GetHitResultUnderCursor(ECC_Pawn, true, PawnHit);
		
		if (bPawnHitSuccessful)
		{
			auto HitNPC = Cast<ATopDownCharacterBase>(PawnHit.GetActor());

			if (HitNPC)
			{
				AttackTargetedNPC(HitNPC);
				return;
			}
		}
		
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}
	
	FollowTime = 0.f;
}

void ATopDownPlayerController::AttackTargetedNPC(ATopDownCharacterBase* Actor)
{
	FVector ActorLocation = Actor->GetActorLocation();

	auto ControlledPawn = Cast<ATopDownPlayerCharacter>(GetPawn());
	FVector OwnerLocation = ControlledPawn->GetActorLocation();
	float DistanceFromActor = UKismetMathLibrary::VSizeXY(OwnerLocation - ActorLocation);

	if (DistanceFromActor <= ControlledPawn->GetCombatRange())
	{
		StopMovement();
		ShootProjectileAtEnemy(Actor);
	}
}

void ATopDownPlayerController::ShootProjectileAtEnemy(ATopDownCharacterBase* Target)
{
	auto ControlledPawn = Cast<ATopDownPlayerCharacter>(GetPawn());
	const FTransform SpawnLocAndRotation = GetPawn()->GetActorTransform();
	
	AProjectile* MyActor = GetWorld()->SpawnActorDeferred<AProjectile>(AProjectile::StaticClass(), SpawnLocAndRotation);
	MyActor->DamageToDo = ControlledPawn->GetDamage();
	MyActor->TargetActor = Target;
	MyActor->StaticMesh = ProjectileMesh;
	MyActor->ProjectileSpeed = ControlledPawn->GetProjectileSpeed();
	MyActor->FinishSpawning(SpawnLocAndRotation);
}
