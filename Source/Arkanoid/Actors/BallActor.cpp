// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BallActor.h"
#include "Net/UnrealNetwork.h"
#include "Pawns/RocketPlatform.h"

ABallActor::ABallActor()
{
	Collision = CreateDefaultSubobject<USphereComponent>("BallCollision");
	RootComponent = Collision;
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("BallMesh");
	Mesh->SetupAttachment(Collision);
	
}

void ABallActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABallActor::HitTrigger_Implementation(FHitResult hit)
{
	Direction = FMath::GetReflectionVector(Direction, hit.Normal);
	if(hit.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor %s"),*hit.GetActor()->GetName());
	}
	if(hit.GetActor())
	{
		ARocketPlatform* actor =  Cast<ARocketPlatform>(hit.GetActor());
		if(IsValid(actor))
		{
			SetBallOwner(actor);
		}
	}
}


void ABallActor::UpdatePosition_Implementation(float DeltaTime)
{
	float resultMultiply = DeltaTime * Speed;
	FVector resultDirection = Direction * resultMultiply;
	resultDirection.Z = 0;
	FHitResult hit;
	AddActorWorldOffset(resultDirection, true, &hit);
	SetClientPosition(GetActorLocation());
}



void ABallActor::SetClientPosition_Implementation(FVector position)
{
	SetActorLocation(position);
}

void ABallActor::Destroyed()
{
	OnBallDestroy.Broadcast(this);
	Super::Destroyed();
}

void ABallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdatePosition(DeltaTime);
}

void ABallActor::SetBallOwner_Implementation(ARocketPlatform* value)
{
	SetOwner(value);
}