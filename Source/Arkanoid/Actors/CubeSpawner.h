// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCube.h"
#include "GameFramework/Actor.h"
#include "CubeSpawner.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndCube);

UCLASS()
class ARKANOID_API ACubeSpawner : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintAssignable, BlueprintCallable)
	FEndCube OnEndCubeCount;
	ACubeSpawner();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SpawnParametr")
	int32 X;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SpawnParametr")
	int32 Y;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SpawnParametr")
	int32 StartX;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SpawnParametr")
	int32 StartY;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SpawnParametr")
	FVector2D SizeCube;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SpawnParametr")
	FVector2D Padding;
	
	FVector LastSpawning;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="SpawnParametr")
	TArray<TSubclassOf<ABaseCube>> TypeCubesToSpawn;

	UPROPERTY()
	TArray<ABaseCube*> SpawnedCubes;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	UFUNCTION(Server, Reliable)
	void DestroyedCube(AActor* cube, AActor* HitActor);

	UFUNCTION(Server, Reliable)
	void SpawnCube(TSubclassOf<ABaseCube> actor, FVector position, FVector2D Scale);

public:
	UFUNCTION(Server, Reliable)
	void SpawnCubes();

	UFUNCTION(Server, Reliable)
	void ClearCube();
	
	virtual void Tick(float DeltaTime) override;
};

