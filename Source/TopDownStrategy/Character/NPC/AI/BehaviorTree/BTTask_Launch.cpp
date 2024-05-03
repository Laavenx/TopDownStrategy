// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Launch.h"
#include <AIController.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TopDownStrategy/Character/TopDownCharacterBase.h"
#include "TopDownStrategy/Character/NPC/TopDownNPC.h"

EBTNodeResult::Type UBTTask_Launch::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (AIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	APawn* OwnerPawn = AIController->GetPawn();

	if (!OwnerPawn)
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BBComp = AIController->GetBlackboardComponent();
	if (!BBComp)
	{
		return EBTNodeResult::Failed;
	}
	
	if (auto TargetActor = Cast<ATopDownCharacterBase>(BBComp->GetValueAsObject(BBTargetActor.SelectedKeyName)))
	{
		auto ControlledPawn = Cast<ATopDownNPC>(OwnerPawn);
	
		FVector VectorTowards = (TargetActor->GetActorLocation() - ControlledPawn->GetActorLocation());
		VectorTowards.Normalize();
		auto Velocity = VectorTowards * 1450;
		ControlledPawn->GetCharacterMovement()->Launch(Velocity);
		
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
