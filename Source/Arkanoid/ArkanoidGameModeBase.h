// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArkanoidGameModeBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFillRoom);
class ARocketController;
class ARocketPlatform;
class APlayerStart;
/**
 * 
 */
UCLASS()
class ARKANOID_API AArkanoidGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintAssignable, BlueprintCallable)
	FFillRoom OnFillRoom;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<APlayerStart*> PlayerStartPosition;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SpawnPlayer(ARocketController* PlayerController);

protected:
	int32 index = 0;
};
