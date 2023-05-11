// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/GameRule.h"

#include "ArkanoidGameModeBase.h"
#include "CubeSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/RocketPlatform.h"

// Sets default values
AGameRule::AGameRule()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameRule::BeginPlay()
{
	Super::BeginPlay();
	if(GetLocalRole() == ROLE_Authority)
	{
		Cast<AArkanoidGameModeBase>(GetWorld()->GetAuthGameMode())->OnFillRoom.AddDynamic(this, &AGameRule::FindPawn);
	}
	TArray<AActor*> resul;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACubeSpawner::StaticClass(), resul);
	if(resul.Num()>0)
	{
		Spawner = Cast<ACubeSpawner>(resul[0]);
		Spawner->OnEndCubeCount.AddDynamic(this, &AGameRule::EndCube);
	}
}

void AGameRule::BallDestroy_Implementation(AActor* ball)
{
	AllBalls.Remove(Cast<ABallActor>(ball));

	if(!RunGame)
	{
		return;
	}
	
	if(AllBalls.Num() > 0)
	{
		return;
	}
	
	for (auto platform : platforms)
	{
		if(platform->CountSpawnBall > 0)
		{
			return;
		}
	}
	RunGame = false;
	ShowLoss();
}

void AGameRule::FindPawn_Implementation()
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARocketPlatform::StaticClass(), actors);
	for (auto actor : actors)
	{
		platforms.Add(Cast<ARocketPlatform>(actor));
	}
	for (auto platform : platforms)
	{
		platform->OnSpawnBall.AddDynamic(this, &AGameRule::AddBallToLevel);
	}
	Restart();
}


void AGameRule::AddBallToLevel_Implementation(ABallActor* ball)
{
	ball->OnBallDestroy.AddDynamic(this, &AGameRule::BallDestroy);
	AllBalls.Add(ball);
}

void AGameRule::EndCube_Implementation()
{
	if(!RunGame)
	{
		return;	
	}	
	for (auto platform :platforms)
	{
		platform->CountSpawnBall = 0;
	}
	for (auto ball :AllBalls)
	{
		ball->Destroy();
	}
	RunGame = false;
	ShowWin();
}

void AGameRule::ShowWin_Implementation()
{
	OnWin.Broadcast();
}

void AGameRule::ShowLoss_Implementation()
{	
	OnLoss.Broadcast();	
}

void AGameRule::ShowRestart_Implementation()
{	
	OnRestart.Broadcast();
}

void AGameRule::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
    if(RunGame)
    {
	    return;
    }
	if(platforms.Num() <= 0)
	{
		return;
	}
	for (auto platform :platforms)
	{
		if(platform->ReadyToGame == false)
		{
			return;
		}
	}
	Restart();
}

void AGameRule::Restart_Implementation()
{
	Spawner->ClearCube();
	Spawner->SpawnCubes();
	for (auto ball :AllBalls)
	{
		ball->Destroy();
	}
	for (auto platform :platforms)
	{
		platform->SetReady(false);
	}
	
	platforms[0]->CountSpawnBall = 1;
	RunGame = true;
	ShowRestart();
}


