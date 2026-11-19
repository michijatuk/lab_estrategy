#include "Mina.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/Pawn.h"
#include "UObject/ConstructorHelpers.h"

static bool IsPlayerPawn(const AActor* Actor)
{
	const APawn* Pawn = Cast<APawn>(Actor);
	return Pawn && Pawn->IsPlayerControlled();
}

AMina::AMina()
{
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	Trigger->SetSphereRadius(80.f);
	Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Trigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	Trigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMina::OnMineOverlap);
	RootComponent = Trigger;

	MineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MineMesh"));
	MineMesh->SetupAttachment(Trigger);
	MineMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MineMesh->SetRelativeScale3D(FVector(0.4f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereAsset(
		TEXT("/Engine/BasicShapes/Sphere.Sphere"));

	if (SphereAsset.Succeeded())
	{
		MineMesh->SetStaticMesh(SphereAsset.Object);
	}
}

void AMina::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(ArmTimer, this, &AMina::Arm, ArmingTime, false);
}

void AMina::Arm()
{
	bArmed = true;

	// Si el pawn ya estaba encima cuando se activ¨®, explota de inmediato
	TArray<AActor*> Overlapping;
	Trigger->GetOverlappingActors(Overlapping, APawn::StaticClass());

	for (AActor* Actor : Overlapping)
	{
		if (IsPlayerPawn(Actor))
		{
			Explode(Actor);
			return;
		}
	}
}

void AMina::OnMineOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (bArmed && IsPlayerPawn(OtherActor))
	{
		Explode(OtherActor);
	}
}

void AMina::Explode(AActor* Victim)
{
	UE_LOG(LogTemp, Warning, TEXT("MINA: EXPLOTO"));

	if (Victim)
	{
		Victim->Destroy();
	}

	Destroy();
}