// Copyright Epic Games, Inc. All Rights Reserved.


#include "ArkanoidGameModeBase.h"

#include "Actors/CubeSpawner.h"
#include "Controllers/RocketController.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/RocketPlatform.h"


void AArkanoidGameModeBase::SpawnPlayer_Implementation(ARocketController* PlayerController)
{
	if(PlayerStartPosition.Num() <=0)
	{
		return;
	}
	int32 i = index;
	if (IsValid(PlayerController->GetPawn()))
	{
		PlayerController->GetPawn()->Destroy();
	}

	const int32 indexResult = PlayerStartPosition.IndexOfByPredicate(
		[&i](const APlayerStart* controller)
		{
			return controller->PlayerStartTag.ToString() == FString::FromInt(i);
		});

	FTransform position = PlayerStartPosition[indexResult]->GetTransform();
	ARocketPlatform* pawn = GetWorld()->SpawnActor<ARocketPlatform>(DefaultPawnClass, position);
	
	PlayerController->Possess(pawn);

	index++;
	if(index == 2)
	{
		OnFillRoom.Broadcast();
	}
}

