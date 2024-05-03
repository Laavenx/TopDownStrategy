﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_IsWithinCombatRange.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSTRATEGY_API UBTDecorator_IsWithinCombatRange : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
public:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BBTargetActor;
};
