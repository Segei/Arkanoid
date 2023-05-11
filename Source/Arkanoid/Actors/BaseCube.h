// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "BaseCube.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCubeAction, AActor*, Sendler, AActor*, HitActor);

UCLASS(Abstract, Blueprintable)
class ARKANOID_API ABaseCube : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintAssignable, BlueprintCallable, Category="CubeEvents")
	FOnCubeAction OnCubeHit;
	UPROPERTY(EditAnywhere, BlueprintAssignable, BlueprintCallable, Category="CubeEvents")
	FOnCubeAction OnCubeDestroy;
	ABaseCube();



protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CubeMesh")
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "CubeMesh")
	UBoxComponent* Collision;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Lifes")
	int CountLife;

	int CurrentLife;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Lifes")
	TArray<UMaterialInterface*> LifeMaterialList;

	UFUNCTION(NetMulticast, Unreliable)
	void SetMaterial(int value);
	virtual void BeginPlay() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& e) override;
public:
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void CubeHit(
		AActor* OtherActor);
};

