// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CubeSpawner.h"

#include "BallActor.h"
#include "Components/InstancedStaticMeshComponent.h"

// Sets default values
ACubeSpawner::ACubeSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACubeSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void ACubeSpawner::SpawnCubes_Implementation()
{
	FVector ActorPosition = GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("Spawnewd cube count %f, %f, %f"), ActorPosition.X, ActorPosition.Y, ActorPosition.Z);
	for (int32 i = StartX; i < X+1; i++)
	{
		for (int32 j = StartY; j < Y+1 ; j++)
		{
			FVector position = FVector(
				ActorPosition.X - (i * SizeCube.X + i * Padding.X),
				ActorPosition.Y - (j * SizeCube.Y + j * Padding.Y),
				ActorPosition.Z
			);
			LastSpawning = position;
			int32 index = FMath::RandRange(0, TypeCubesToSpawn.Num());
			// int32 index = 1;
			if (index == 0)
			{
				continue;
			}
			SpawnCube(TypeCubesToSpawn[index-1], position, SizeCube);
			
		}
	}
}


void ACubeSpawner::DestroyedCube_Implementation(AActor* cube, AActor* HitActor)
{
	SpawnedCubes.Remove(Cast<ABaseCube>(cube));
	if(SpawnedCubes.Num() <= 0)
	{
		OnEndCubeCount.Broadcast();
	}
}


void ACubeSpawner::SpawnCube_Implementation(TSubclassOf<ABaseCube> actor, FVector position, FVector2D Scale)
{
	ABaseCube* spawnCube = GetWorld()->SpawnActor<ABaseCube>(
				actor,
				position,
				FRotator::ZeroRotator
			);
	spawnCube->SetActorScale3D(FVector(Scale.X / 100, Scale.Y / 100, 1));
	spawnCube->OnCubeDestroy.AddDynamic(this, &ACubeSpawner::DestroyedCube);
	
	SpawnedCubes.Add(spawnCube);
}

void ACubeSpawner::ClearCube_Implementation()
{
	for (auto cube :SpawnedCubes)
	{
		cube->Destroy();
	}
}

// Called every frame
void ACubeSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
