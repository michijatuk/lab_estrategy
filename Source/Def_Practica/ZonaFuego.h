// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZonaFuego.generated.h"

class UBoxComponent;
class UAudioComponent;
class USoundBase;

UCLASS()
class DEF_PRACTICA_API AZonaFuego : public AActor
{
    GENERATED_BODY()

public:
    AZonaFuego();

protected:

    // Zona que detectar¨¢ al jugador
    UPROPERTY(VisibleAnywhere)
    UBoxComponent* Zona;

    // Componente encargado de reproducir el sonido
    UPROPERTY(VisibleAnywhere)
    UAudioComponent* SonidoFuego;

    // Archivo de sonido que utilizaremos
    UPROPERTY(EditAnywhere)
    USoundBase* Sonido;

    // Se ejecuta cuando algo entra en la zona
    UFUNCTION()
    void AlEntrar(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

    // Se ejecuta cuando algo sale de la zona
    UFUNCTION()
    void AlSalir(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex
    );
};