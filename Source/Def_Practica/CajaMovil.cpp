// Fill out your copyright notice in the Description page of Project Settings.


#include "CajaMovil.h"
#include "Components/StaticMeshComponent.h"

ACajaMovil::ACajaMovil()
{
    PrimaryActorTick.bCanEverTick = true;

    Malla = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malla"));
    RootComponent = Malla;

    Malla->SetSimulatePhysics(false);
    Malla->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    Malla->SetCollisionProfileName(TEXT("BlockAll"));
    Malla->SetNotifyRigidBodyCollision(true);

    // Usa la malla de cubo del Starter Content.
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaCaja(
        TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube")
    );

    if (MallaCaja.Succeeded())
    {
        Malla->SetStaticMesh(MallaCaja.Object);
    }
}

void ACajaMovil::BeginPlay()
{
    Super::BeginPlay();

    Malla->OnComponentHit.AddDynamic(this, &ACajaMovil::AlColisionar);
}

void ACajaMovil::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AddActorWorldOffset(
        FVector(-Velocidad * DeltaTime, 0.0f, 0.0f),
        true
    );
}

void ACajaMovil::AlColisionar(
    UPrimitiveComponent* ComponenteGolpeado,
    AActor* OtroActor,
    UPrimitiveComponent* ComponenteOtro,
    FVector FuerzaNormal,
    const FHitResult& Impacto
)
{
    Destroy();
}