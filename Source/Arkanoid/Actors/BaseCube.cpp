#include "Actors/BaseCube.h"
#include "BallActor.h"
#include "Net/UnrealNetwork.h"


ABaseCube::ABaseCube()
{
	Collision = CreateDefaultSubobject<UBoxComponent>("CubeCollision");
	RootComponent = Collision;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("CubeMesh");
	Mesh->SetupAttachment(RootComponent);
	PrimaryActorTick.bCanEverTick = true;
	LifeMaterialList.SetNum(CountLife);
}

void ABaseCube::BeginPlay()
{
	Super::BeginPlay();
	CurrentLife = CountLife;
	SetMaterial(CurrentLife);
}

void ABaseCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCube::SetMaterial_Implementation(int value)
{
	Mesh->SetMaterial(0, LifeMaterialList[value-1]);
}

void ABaseCube::CubeHit(AActor* OtherActor)                                                                                               
{
	if(!IsValid(Cast<ABallActor>(OtherActor)) || CurrentLife == 0)
	{
		return;
	}
	CurrentLife--;
	if(CurrentLife > 0)
	{
		SetMaterial(CurrentLife);
		OnCubeHit.Broadcast(this, OtherActor);
	}
	else
	{
		
		OnCubeDestroy.Broadcast(this, OtherActor);
		Destroy();
	}
	
}                                                                                                                                               

void ABaseCube::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	Super::PostEditChangeProperty(e);
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ABaseCube, CountLife)
	|| PropertyName == GET_MEMBER_NAME_CHECKED(ABaseCube, LifeMaterialList)
	)
	{
		LifeMaterialList.SetNum(CountLife);
	}
}


