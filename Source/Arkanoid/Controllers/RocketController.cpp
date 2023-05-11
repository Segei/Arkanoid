// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/RocketController.h"

#include "ArkanoidGameModeBase.h"
#include "GameFramework/PlayerState.h"
#include "Pawns/RocketPlatform.h"

void ARocketController::BeginPlay()
{
	Super::BeginPlay();
	if (IsLocalPlayerController())
	{
		SpawnPlayer();
	}
}

void ARocketController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (IsLocalController())
	{
		InputComponent->BindAxis("MovePlatform", this, &ARocketController::SetInputMove);
		InputComponent->BindAction("AbilityPlatform", EInputEvent::IE_Pressed, this, &ARocketController::UseAbility);
	}
}

void ARocketController::UseAbility()
{
	if (CachedPawn.IsValid())
	{
		CachedPawn->UseAbility();
	}
}


void ARocketController::SetInputMove(float value)
{
	if (CachedPawn.IsValid())
	{
		CachedPawn->SetInputMove(value);
		value;
		//UE_LOG(LogTemp, Warning, TEXT("Value %f"), value);
	}
}

void ARocketController::SetPawn_Implementation(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (IsValid(InPawn))
		CachedPawn = Cast<ARocketPlatform>(InPawn);
}

void ARocketController::SpawnPlayer_Implementation()
{
	Cast<AArkanoidGameModeBase>(GetWorld()->GetAuthGameMode())->SpawnPlayer(this);
}
