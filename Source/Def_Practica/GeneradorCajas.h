// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeneradorCajas.generated.h"

UCLASS()
class DEF_PRACTICA_API AGeneradorCajas : public AActor
{
    GENERATED_BODY()

public:
    AGeneradorCajas();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Generador")
    float SeparacionY = 300.0f;

    UPROPERTY(EditAnywhere, Category = "Generador")
    float IntervaloDeSpawn = 2.0f;

    FTimerHandle TemporizadorSpawn;

    void GenerarCajas();
};
