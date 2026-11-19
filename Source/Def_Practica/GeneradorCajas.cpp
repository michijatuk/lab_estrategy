// Fill out your copyright notice in the Description page of Project Settings.

#include "GeneradorCajas.h"
#include "CajaMovil.h"
#include "Engine/World.h"
#include "TimerManager.h"
AGeneradorCajas::AGeneradorCajas() {
    PrimaryActorTick.bCanEverTick = false;
}
void AGeneradorCajas::BeginPlay() {
    Super::BeginPlay();
    GenerarCajas();
    GetWorldTimerManager().SetTimer(
        TemporizadorSpawn,
        this,
        &AGeneradorCajas::GenerarCajas,
        IntervaloDeSpawn,
        true,
        IntervaloDeSpawn);
}
void AGeneradorCajas::GenerarCajas() {
    const FVector Base = GetActorLocation();
    // Los tres puntos quedan en Y = -SeparacionY, 0 y +SeparacionY.
    for (int32 i = 0; i < 3; i++) {
        const float DesplazamientoY = (i - 1) * SeparacionY;
        const FVector Posicion = Base + FVector(0.0f, DesplazamientoY, 0.0f);
        GetWorld()->SpawnActor<ACajaMovil>(
            ACajaMovil::StaticClass(),
            Posicion,
            GetActorRotation()
        );
    }
}

