// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bloqueo.generated.h"

UCLASS()
class DEF_PRACTICA_API ABloqueo : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABloqueo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Malla;



	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Colision;



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};