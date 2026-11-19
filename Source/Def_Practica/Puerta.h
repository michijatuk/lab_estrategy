// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//que variables de otros archivos de c++ se usaran.
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Puerta.generated.h"


UCLASS()
class DEF_PRACTICA_API APuerta : public AActor
{
	GENERATED_BODY()

public:
	// establece valores predeterminados aqui:
	APuerta();



	// Se llama cuando comienza el juego o al aparecer.
protected:
	virtual void BeginPlay() override;


	//creame la variable de la maya
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Malla;

	//codigo de movimiento
private:
	FVector PosicionInicial;
	FVector PosicionFinal;

	float Tiempo;

	UPROPERTY(EditAnywhere)
	float Velocidad = 5.0f;

	UPROPERTY(EditAnywhere)
	float Distancia = 1000.0f;


public:
	// llama en cada frame
	virtual void Tick(float DeltaTime) override;
};