// Fill out your copyright notice in the Description page of Project Settings.

#include "Puerta.h"

// dale valores predeterminados
APuerta::APuerta()
{
    PrimaryActorTick.bCanEverTick = true;


    // Crear la malla
    Malla = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malla"));
    RootComponent = Malla;

    // Asignaci¨®n de malla
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
        TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'")
    );

    if (MeshAsset.Succeeded()) {
        Malla->SetStaticMesh(MeshAsset.Object);
    }
}

// Se llama cuando el juego comienza
void APuerta::BeginPlay()
{
    Super::BeginPlay();

    PosicionInicial = GetActorLocation();
    PosicionFinal = PosicionInicial + FVector(Distancia, 0.0f, 0.0f);

    Tiempo = 0.0f;
}

// Called every frame
void APuerta::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Movimiento
    Tiempo += DeltaTime * Velocidad;

    // Va de 0 a 1 y luego vuelve de 1 a 0
    float Alpha = (FMath::Sin(Tiempo) + 1.0f) / 2.0f;

    FVector NuevaPosicion = FMath::Lerp(
        PosicionInicial,
        PosicionFinal,
        Alpha
    );

    SetActorLocation(NuevaPosicion);
}
