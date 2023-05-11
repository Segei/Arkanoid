// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CubeSpawner.h"
#include "GameFramework/Actor.h"
#include "GameRule.generated.h"

class ARocketPlatform;
class ABallActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndGame);

UCLASS()
class ARKANOID_API AGameRule : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintAssignable, BlueprintCallable)
	FEndGame OnLoss;
	UPROPERTY(EditAnywhere, BlueprintAssignable, BlueprintCallable)
	FEndGame OnWin;
	UPROPERTY(EditAnywhere, BlueprintAssignable, BlueprintCallable)
	FEndGame OnRestart;
	AGameRule();

protected:
	UPROPERTY()
	bool RunGame = false;
	UPROPERTY()
	TArray<ARocketPlatform*> platforms;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(Server, Reliable)
	void FindPawn();
	UFUNCTION(Server, Reliable)
	void BallDestroy(AActor* ball);
	UPROPERTY()
	TArray<ABallActor*> AllBalls;
	UPROPERTY()
	ACubeSpawner* Spawner;
	UFUNCTION(Server, Reliable)
	void EndCube();
	UFUNCTION(NetMulticast, Reliable)
	void ShowLoss();
	UFUNCTION(NetMulticast, Reliable)
	void ShowWin();
	UFUNCTION(NetMulticast, Reliable)
	void ShowRestart();
	
public:
	UFUNCTION(Server, Reliable)
	void AddBallToLevel(ABallActor* ball);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Restart();

	virtual  void Tick(float DeltaSeconds) override;
};
