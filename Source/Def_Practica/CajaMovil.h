// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CajaMovil.generated.h"

UCLASS()
class DEF_PRACTICA_API ACajaMovil : public AActor
{
    GENERATED_BODY()

public:
    ACajaMovil();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere, Category = "Componentes")
    class UStaticMeshComponent* Malla;

    UPROPERTY(EditAnywhere, Category = "Movimiento")
    float Velocidad = 300.0f;

    UFUNCTION()
    void AlColisionar(
        UPrimitiveComponent* ComponenteGolpeado,
        AActor* OtroActor,
        UPrimitiveComponent* ComponenteOtro,
        FVector FuerzaNormal,
        const FHitResult& Impacto
    );
};
