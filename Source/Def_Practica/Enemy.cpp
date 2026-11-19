// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "IdleStrategy.h"
#include "Components/SphereComponent.h"
#include "PatrolStrategy.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Def_PracticaGameMode.h"	
#include "Engine/World.h"
#include "Mina.h"

static bool IsPlayerPawn(const AActor* Actor)
{
    const APawn* Pawn = Cast<APawn>(Actor);
    return Pawn && Pawn->IsPlayerControlled();
}
// Sets default values
AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
    // Crear el componente de malla y colgarlo de la c¨¢psula
    EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
    EnemyMesh->SetupAttachment(GetCapsuleComponent());
 EnemyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

 //componente de deteccion 
 DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
 DetectionSphere->SetupAttachment(GetCapsuleComponent());
 DetectionSphere->SetSphereRadius(DetectionRadius);
 DetectionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
 DetectionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
 DetectionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
 DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnDetectionBeginOverlap);
 DetectionSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemy::OnDetectionEndOverlap);

  
 static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
     TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));

 if (MeshAsset.Succeeded())
 {
     EnemyMesh->SetStaticMesh(MeshAsset.Object);
 }
   
 AIControllerClass = AAIController::StaticClass();
 AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
  
 GetCharacterMovement()->MaxWalkSpeed = 200.f;
 GetCharacterMovement()->bOrientRotationToMovement = true;
 bUseControllerRotationYaw = false;

}

void AEnemy::BeginPlay()
{
    Super::BeginPlay();

	//salud
	Health = MaxHealth;

    StartIdle();


    TArray<AActor*> Overlapping;
    DetectionSphere->GetOverlappingActors(Overlapping, APawn::StaticClass());

    for (AActor* Actor : Overlapping)
    {
        if (IsPlayerPawn(Actor))
        {
            StartPatrol();
            break;
        }
    }

	// Registrar el enemigo en el GameMode
	if (ADef_PracticaGameMode* GM = GetWorld()->GetAuthGameMode<ADef_PracticaGameMode>())
	{
		GM->RegisterEnemy(this);
	}

	// Los reci¨¦n nacidos esperan antes de poder duplicarse
	GetWorldTimerManager().SetTimer(
		DuplicateTimer, [this]() { bCanDuplicate = true; }, DuplicateCooldown, false);

	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (CurrentStrategy)
    {
        CurrentStrategy->Execute(this, DeltaTime);
    }
}


void AEnemy::StartIdle()
{
	GetWorldTimerManager().ClearTimer(IdleTimer);
	bPatrolling = false;

	SetStrategy(MakeUnique<FIdleStrategy>());
	UE_LOG(LogTemp, Warning, TEXT("ENEMIGO: IDLE"));
}



void AEnemy::StartPatrol()
{
	GetWorldTimerManager().ClearTimer(IdleTimer);
	bPatrolling = true;

	TArray<FVector> Points;
	const FVector Origin = GetActorLocation();
	SetStrategy(MakeUnique<FPatrolStrategy>());
	
	UE_LOG(LogTemp, Warning, TEXT("ENEMIGO: PATRULLA"));
	TryDuplicate();
}

void AEnemy::OnDetectionBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (!IsPlayerPawn(OtherActor))
	{
		return;
	}

	// Detect¨® al pawn: cancela la cuenta regresiva a idle
	GetWorldTimerManager().ClearTimer(IdleTimer);

	if (!bPatrolling)
	{
		StartPatrol();
	}
}

void AEnemy::OnDetectionEndOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (!IsPlayerPawn(OtherActor) || !bPatrolling)
	{
		return;
	}

	// El pawn sali¨®: si en 10 s no vuelve, pasa a idle
	GetWorldTimerManager().SetTimer(
		IdleTimer, this, &AEnemy::StartIdle, TimeToIdle, false);
}
void AEnemy::SetStrategy(TUniquePtr<IEnemyStrategy> NewStrategy)
{
	CurrentStrategy = MoveTemp(NewStrategy);
}

void AEnemy::TryDuplicate()
{
	if (!bCanDuplicate)
	{
		return;
	}

	ADef_PracticaGameMode* GM = GetWorld()->GetAuthGameMode<ADef_PracticaGameMode>();

	if (GM && GM->TryDuplicateEnemy(this))
	{
		bCanDuplicate = false;
		GetWorldTimerManager().SetTimer(
			DuplicateTimer, [this]() { bCanDuplicate = true; }, DuplicateCooldown, false);
	}
}

void AEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(DuplicateTimer);
	GetWorldTimerManager().ClearTimer(IdleTimer);

	// Solo cuenta como baja si el enemigo fue destruido (no al cerrar el nivel)
	if (EndPlayReason == EEndPlayReason::Destroyed)
	{
		if (ADef_PracticaGameMode* GM = GetWorld()->GetAuthGameMode<ADef_PracticaGameMode>())
		{
			
			GM->UnregisterEnemy(this);

			// Destruye todas las minas que haya dejado el enemigo
			for (TWeakObjectPtr<AMina>& Mine : Mines)
			{
				if (Mine.IsValid())
				{
					Mine->Destroy();
				}
			}
			Mines.Empty();
		}
	}

	Super::EndPlay(EndPlayReason);
}

float AEnemy::TakeDamage(
	float DamageAmount,
	FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser)
{
	if (Health <= 0)
	{
		return 0.f;
	}

	Health -= FMath::CeilToInt(DamageAmount);

	UE_LOG(LogTemp, Warning, TEXT("ENEMIGO: vida restante %d"), Health);

	if (Health <= 0)
	{
		Destroy();
	}

	return DamageAmount;
}

void AEnemy::DropMine()
{
	// Quita de la lista las minas que ya explotaron
	Mines.RemoveAll([](const TWeakObjectPtr<AMina>& Mine)
		{
			return !Mine.IsValid();
		});

	if (Mines.Num() >= MaxMines)
	{
		return;
	}

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AMina* Mine = GetWorld()->SpawnActor<AMina>(
		AMina::StaticClass(),
		GetActorLocation(),
		FRotator::ZeroRotator,
		Params);

	if (Mine)
	{
		Mines.Add(Mine);
	}
}