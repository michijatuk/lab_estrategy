#include "Premio.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/Pawn.h"
#include "UObject/ConstructorHelpers.h"

APremio::APremio()
{
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	Trigger->SetSphereRadius(100.f);
	Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Trigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	Trigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &APremio::OnPickupOverlap);
	RootComponent = Trigger;

	PremioMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PremioMesh"));
	PremioMesh->SetupAttachment(Trigger);
	PremioMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PremioMesh->SetRelativeScale3D(FVector(0.5f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeAsset(
		TEXT("/Engine/BasicShapes/Cube.Cube"));

	if (CubeAsset.Succeeded())
	{
		PremioMesh->SetStaticMesh(CubeAsset.Object);
	}
}

void APremio::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Gira para que se note que es especial
	PremioMesh->AddLocalRotation(FRotator(0.f, RotationSpeed * DeltaTime, 0.f));
}

void APremio::OnPickupOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	const APawn* Pawn = Cast<APawn>(OtherActor);

	if (!Pawn || !Pawn->IsPlayerControlled())
	{
		return;
	}

	if (GEngine)
	{
		// Clave 1: si se repite, reemplaza el mensaje anterior
		GEngine->AddOnScreenDebugMessage(
			1, 60.f, FColor::Green, TEXT("HASTA QUE AL FIN MATAS A TODOS XD!!!"), true, FVector2D(4.f, 4.f));
	}

	Destroy();
}