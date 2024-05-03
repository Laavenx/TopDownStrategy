// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AutoAttack.h"
#include <AIController.h>
#include "BehaviorTree/BlackboardComponent.h"
#include <AIController.h>
#include "TopDownStrategy/Character/TopDownCharacterBase.h"

EBTNodeResult::Type UBTTask_AutoAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	AActor* TargetActor = Cast<AActor>(BBComp->GetValueAsObject(BBTargetActor.SelectedKeyName));

	if (auto Character = Cast<ATopDownCharacterBase>(TargetActor))
	{
		Character->ReceiveDamage(Character->GetDamage());
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
