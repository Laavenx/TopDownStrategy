// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AutoAttackRanged.h"
#include <AIController.h>
#include "TopDownStrategy/Character/NPC/Data/TopDownUnitConfig.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TopDownStrategy/Character/TopDownCharacterBase.h"
#include "TopDownStrategy/Character/NPC/TopDownNPC.h"
#include "TopDownStrategy/Character/Weapons/Projectile.h"

EBTNodeResult::Type UBTTask_AutoAttackRanged::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
		const FTransform SpawnLocAndRotation = ControlledPawn->GetActorTransform();
	
		AProjectile* MyActor = GetWorld()->SpawnActorDeferred<AProjectile>(AProjectile::StaticClass(), SpawnLocAndRotation);
		MyActor->DamageToDo = ControlledPawn->GetDamage();
		MyActor->TargetActor = TargetActor;
		MyActor->StaticMesh = ControlledPawn->UnitConfig->ProjectileMesh;
		MyActor->ProjectileSpeed = ControlledPawn->GetProjectileSpeed();
		MyActor->FinishSpawning(SpawnLocAndRotation);
		
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
