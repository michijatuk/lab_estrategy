// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Templates/UniquePtr.h"
#include "EnemyStrategy.h"
#include "Enemy.generated.h"

class UStaticMeshComponent;	
class USphereComponent;
class AMina;


UCLASS()
class DEF_PRACTICA_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetStrategy(TUniquePtr<IEnemyStrategy> NewStrategy); 
protected:

	UPROPERTY(VisibleAnywhere, Category = "Enemy")
	UStaticMeshComponent* EnemyMesh;
	TUniquePtr<IEnemyStrategy> CurrentStrategy;


	void StartPatrol();
	void StartIdle();
public:
	UFUNCTION()
	void OnDetectionBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnDetectionEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, Category = "Enemy")
	USphereComponent* DetectionSphere;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	float DetectionRadius = 600.f;

	bool bPatrolling = false;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	float TimeToIdle = 10.f;
	FTimerHandle IdleTimer;


	//paso para duplicar
protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void TryDuplicate();

	UPROPERTY(EditAnywhere, Category = "Enemy")
	float DuplicateCooldown = 5.f;

	bool bCanDuplicate = false;
	FTimerHandle DuplicateTimer;

	//paso para recibir da?o
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser) override;

private:
	UPROPERTY(EditAnywhere, Category = "Enemy")
	int32 MaxHealth = 3;

	int32 Health = 3;

public:
	//mina
	void DropMine();

private:
	UPROPERTY(EditAnywhere, Category = "Enemy")
	int32 MaxMines = 5;

	TArray<TWeakObjectPtr<AMina>> Mines;

};
