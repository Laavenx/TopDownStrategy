// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownNPC.h"

#include "AI/TopDownBaseAIController.h"
#include "TopDownStrategy/Character/NPC/Data/TopDownUnitConfig.h"
#include "Data/NPCData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TopDownStrategy/GameObject/TopDownGameState.h"

ATopDownNPC::ATopDownNPC()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATopDownNPC::BeginPlay()
{
	Super::BeginPlay();
	
	auto NPCDataDatabase = Cast<ATopDownGameState>(GetWorld()->GetGameState());
	
	FNPCData NPCData;
	if (UnitConfig && NPCDataDatabase->GetNPCData(UnitConfig->Name, NPCData))
	{
		SetStats(NPCData);
		USkeletalMesh* SKMesh = UnitConfig->SkeletalMesh.LoadSynchronous();
		if (SKMesh)
		{
			GetMesh()->SetSkeletalMesh(SKMesh);
		}
	}

	auto AIController = Cast<ATopDownBaseAIController>(GetController());
	AIController->SetupBlackboard(this);
}

// Called every frame
void ATopDownNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATopDownNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

