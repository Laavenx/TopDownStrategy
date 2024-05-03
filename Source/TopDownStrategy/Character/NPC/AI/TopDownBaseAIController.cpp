// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownBaseAIController.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "TopDownStrategy/Character/NPC/TopDownNPC.h"
#include "TopDownStrategy/Character/NPC/Data/TopDownUnitConfig.h"
#include "TopDownStrategy/Character/Player/TopDownPlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
ATopDownBaseAIController::ATopDownBaseAIController()
{
	PrimaryActorTick.bCanEverTick = true;
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	AISenseSightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightSense");
	AISenseSightConfig->Implementation = UAISense_Sight::StaticClass();
	AISenseSightConfig->SightRadius = 900.0f;
	AISenseSightConfig->LoseSightRadius = 1000.0f;
	AISenseSightConfig->PeripheralVisionAngleDegrees = 90.0f;
	AISenseSightConfig->DetectionByAffiliation.bDetectEnemies = true;
	AISenseSightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	AISenseSightConfig->DetectionByAffiliation.bDetectNeutrals = false;
	AISenseSightConfig->AutoSuccessRangeFromLastSeenLocation = -1.0;
	AISenseSightConfig->PointOfViewBackwardOffset = 0.0f;
	AISenseSightConfig->NearClippingRadius = 0.0f;
	AISenseSightConfig->SetMaxAge(15.0);
	PerceptionComponent->ConfigureSense(*AISenseSightConfig);
	PerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());
}

void ATopDownBaseAIController::BeginPlay()
{
	Super::BeginPlay();

	if (PerceptionComponent)
	{
		PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &ATopDownBaseAIController::OnPerceptionUpdate);
		PerceptionComponent->OnTargetPerceptionForgotten.AddDynamic(this, &ATopDownBaseAIController::OnTargetPerceptionForgotten);
	}
}

void ATopDownBaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ATopDownNPC* NPCCharacter = Cast<ATopDownNPC>(InPawn);

	if (NPCCharacter)
	{
		if (NPCCharacter->UnitConfig)
		{
			RunBehaviorTree(NPCCharacter->UnitConfig->BehaviourTree);
		}
	}
}

void ATopDownBaseAIController::SetupBlackboard(AActor* Actor)
{
	ATopDownNPC* NPCCharacter = Cast<ATopDownNPC>(Actor);

	if (NPCCharacter)
	{
		if (NPCCharacter->UnitConfig)
		{
			AISenseSightConfig->SightRadius = NPCCharacter->GetDetectionRange();
			AISenseSightConfig->LoseSightRadius = NPCCharacter->GetDetectionRange() + 100;
		}
	}
}

void ATopDownBaseAIController::OnPerceptionUpdate(const TArray<AActor*>& UpdatedActors)
{
	for (AActor* Actor : UpdatedActors)
	{
		if (Actor)
		{
			ATopDownPlayerCharacter* Target = Cast<ATopDownPlayerCharacter>(Actor);
			if (Target)
			{
				GetBlackboardComponent()->SetValueAsObject("TargetActor", Target);
				break;
			}
		}
	}
}

void ATopDownBaseAIController::OnTargetPerceptionForgotten(AActor* Actor)
{
	UE_LOG(LogTemp, Log, TEXT("Forgot player"))
}
