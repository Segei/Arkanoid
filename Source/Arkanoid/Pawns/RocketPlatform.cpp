// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/RocketPlatform.h"

#include "Net/UnrealNetwork.h"

// Sets default values
ARocketPlatform::ARocketPlatform()
{
	Collision = CreateDefaultSubobject<UBoxComponent>("PlatformCollision");
	RootComponent = Collision;
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("PlatformMesh");
	Mesh->SetupAttachment(RootComponent);
	PositionBall = CreateDefaultSubobject<UArrowComponent>("PositionBall");
	PositionBall->SetupAttachment(RootComponent);
	}

// Called when the game starts or when spawned
void ARocketPlatform::BeginPlay()
{
	Super::BeginPlay();
	FVector position = GetActorLocation();
	position.Z = 200.f;
	SetActorLocation(position);
}

void ARocketPlatform::SetInputMove_Implementation(float value)
{
	float deltaTime = GetWorld()->DeltaTimeSeconds;
	float result = value * deltaTime * Speed;
	FVector direction = FVector(0, result, 0);
	direction = direction * GetActorRightVector();
	UpdatePosition(direction);
}

void ARocketPlatform::UpdatePosition_Implementation(FVector direction)
{
	FHitResult hit;
	AddActorWorldOffset(direction, true, &hit);
	SetClientPosition(GetActorLocation());
}

void ARocketPlatform::SetClientPosition_Implementation(FVector position)
{
	SetActorLocation(position);
}

void ARocketPlatform::TrySpawnBall_Implementation()
{
	if (CountSpawnBall <= 0)
	{
		return;
	}

	ABallActor* SpawnedBall = GetWorld()->SpawnActor<ABallActor>(Ball, PositionBall->GetComponentLocation(), PositionBall-> GetComponentRotation());
	if (IsValid(SpawnedBall))
	{
		SpawnedBall->Direction = PositionBall->GetForwardVector();
		SpawnedBall->SetBallOwner(this);
		CountSpawnBall --;
		OnSpawnBall.Broadcast(SpawnedBall);
	}
}

void ARocketPlatform::UseAbility_Implementation()
{
	TrySpawnBall();
}

void ARocketPlatform::Destroyed()
{
	Super::Destroyed();
}

// Called every frame
void ARocketPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARocketPlatform::SetReady_Implementation(bool value)
{
	ReadyToGame = value;
}


void ARocketPlatform::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARocketPlatform, Speed);
}
