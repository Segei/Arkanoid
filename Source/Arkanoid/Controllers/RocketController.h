// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RocketController.generated.h"


class ARocketPlatform;
/**
 * 
 */
UCLASS()
class ARKANOID_API ARocketController : public APlayerController
{
	GENERATED_BODY()

protected:
	TSoftObjectPtr<ARocketPlatform> CachedPawn;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void SetInputMove(float value);

	UFUNCTION()
	void UseAbility();

	UFUNCTION(Server, Reliable)
	virtual void SpawnPlayer();

public:
	UFUNCTION(NetMulticast, Reliable)
	virtual void SetPawn(APawn* InPawn) override;
};
