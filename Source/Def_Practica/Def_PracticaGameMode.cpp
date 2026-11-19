// Copyright Epic Games, Inc. All Rights Reserved.

#include "Def_PracticaGameMode.h"
#include "Def_PracticaPawn.h"
#include "Enemy.h"
#include "Engine/World.h"
#include "premio.h"


class Enemy;
class PatrolStrategy;
class IdleStrategy;
ADef_PracticaGameMode::ADef_PracticaGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ADef_PracticaPawn::StaticClass();
}

void ADef_PracticaGameMode::BeginPlay()
{
	   Super::BeginPlay();
	  
	   	SpawnInitialEnemies();

}

void ADef_PracticaGameMode::Tick( float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADef_PracticaGameMode::RegisterEnemy(AEnemy* Enemy)
{
	++EnemyCount;
	UE_LOG(LogTemp, Warning, TEXT("Enemigos: %d"), EnemyCount);
}

void ADef_PracticaGameMode::UnregisterEnemy(AEnemy* Enemy)
{
	if (Enemy)
	{
		LastEnemyLocation = Enemy->GetActorLocation();
	}

	EnemyCount = FMath::Max(0, EnemyCount - 1);
	UE_LOG(LogTemp, Warning, TEXT("Enemigos: %d"), EnemyCount);

	if (EnemyCount == 0)
	{
		OnAllEnemiesDefeated();
	}
}

bool ADef_PracticaGameMode::TryDuplicateEnemy(AEnemy* Source)
{
	if (!Source || EnemyCount >= MaxEnemies)
	{
		return false;
	}

	// Aparece cerca del original, en una direcci¨®n al azar
	const FVector Offset =
		FRotator(0.f, FMath::FRandRange(0.f, 360.f), 0.f).Vector() * 200.f;

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AEnemy* NewEnemy = GetWorld()->SpawnActor<AEnemy>(
		Source->GetClass(),
		Source->GetActorLocation() + Offset,
		Source->GetActorRotation(),
		Params);

	return NewEnemy != nullptr;
}

void ADef_PracticaGameMode::OnAllEnemiesDefeated()
{
	if (bRewardGiven)
	{
		return;
	}
	bRewardGiven = true;

	UE_LOG(LogTemp, Warning, TEXT("TODOS LOS ENEMIGOS ELIMINADOS"));

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<APremio>(
		APremio::StaticClass(), LastEnemyLocation, FRotator::ZeroRotator, Params);
}

void ADef_PracticaGameMode::SpawnInitialEnemies()
{
	// Pon aqu¨ª tus coordenadas (X, Y, Z)
	const TArray<FVector> SpawnPoints = {
		FVector(-1070.0f, -270.0f, 760.0f),
		FVector(-270.001923f, 450.0f, 760.002747f),
		FVector(-900.009f, 430.000000f, 760.002747f),
		FVector(-220.001923f, -320.000000f, 800.002747f),
		FVector(-590.001953f, -430.000000f, 760.002747f)
	};

	UClass* ClassToSpawn = EnemyClass ? EnemyClass.Get() : AEnemy::StaticClass();

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (const FVector& Point : SpawnPoints)
	{
		GetWorld()->SpawnActor<AEnemy>(ClassToSpawn, Point, FRotator::ZeroRotator, Params);
	}
}