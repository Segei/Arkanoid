// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BallActor.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "RocketPlatform.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpawnBall, ABallActor*, Ball);

UCLASS()
class ARKANOID_API ARocketPlatform : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintAssignable, BlueprintCallable)
	FSpawnBall OnSpawnBall;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CountSpawnBall;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SettingsPlatform", Replicated)
	float Speed;

	bool ReadyToGame = false;
	ARocketPlatform();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "PlatformMesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "PlatformMesh")
	UBoxComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "SpawnBall")
	UArrowComponent* PositionBall;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "SpawnBall")
	TSubclassOf<ABallActor> Ball;
	virtual void BeginPlay() override;


	UFUNCTION(Server, Reliable)
	void UpdatePosition(FVector direction);

	UFUNCTION(NetMulticast, Unreliable)
	void SetClientPosition(FVector position);

	UFUNCTION(Server, Reliable)
	void TrySpawnBall();

	virtual void Destroyed() override;

public:
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(Client, Unreliable)
	void UseAbility();
	UFUNCTION(Client, Unreliable)
	void SetInputMove(float value);
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SetReady(bool value);
};
