// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Def_PracticaGameMode.generated.h"


class AEnemy;


UCLASS(MinimalAPI)
class ADef_PracticaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADef_PracticaGameMode();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:

	void RegisterEnemy(AEnemy* Enemy);
	void UnregisterEnemy(AEnemy* Enemy);
	bool TryDuplicateEnemy(AEnemy* Source);

private:
	UPROPERTY(EditAnywhere, Category = "Enemigos")
	int32 MaxEnemies = 30;

	int32 EnemyCount = 0;


private:
	void SpawnInitialEnemies();

	// Si lo dejas vac¨ªo usa AEnemy; si tienes un Blueprint hijo, el¨ªgelo aqu¨ª
	UPROPERTY(EditAnywhere, Category = "Enemigos")
	TSubclassOf<AEnemy> EnemyClass;


	//Regalo
	bool bRewardGiven = false;
	FVector LastEnemyLocation = FVector::ZeroVector;

	void OnAllEnemiesDefeated();

};



