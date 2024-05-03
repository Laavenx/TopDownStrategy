// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownGameState.h"

#include "TopDownStrategy/Character/NPC/Data/NPCData.h"


// Sets default values
ATopDownGameState::ATopDownGameState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

bool ATopDownGameState::GetNPCData(FName Name, FNPCData& OutNPCData)
{
	auto NPCData = this->NPCStats->FindRow<FNPCData>(Name, "", true);
	if (NPCData)
	{
		OutNPCData = *NPCData;
		return true;
	}
	UE_LOG(LogTemp, Warning, TEXT("Could not find npc %s"), *Name.ToString());
	return false;
}

// Called when the game starts or when spawned
void ATopDownGameState::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATopDownGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

