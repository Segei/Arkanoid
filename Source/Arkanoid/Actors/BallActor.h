// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "BallActor.generated.h"

class ARocketPlatform;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBallActions, AActor*, Ball);

UCLASS()
class ARKANOID_API ABallActor : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintAssignable, BlueprintCallable)
	FBallActions OnBallDestroy;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "BallMoveSetiings")
	FVector Direction;
	ABallActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "BallMesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "BallMesh")
	USphereComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "BallMoveSetiings")
	float Speed;
	
	virtual void BeginPlay() override;

	UFUNCTION(Server, Unreliable)
	void UpdatePosition(float DeltaTime);

	UFUNCTION(Server, Unreliable, BlueprintCallable)
	void HitTrigger(FHitResult hit);

	UFUNCTION(NetMulticast, Unreliable)
	void SetClientPosition(FVector position);

	virtual  void Destroyed() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Server, Reliable)
	void SetBallOwner(ARocketPlatform* value);
};
