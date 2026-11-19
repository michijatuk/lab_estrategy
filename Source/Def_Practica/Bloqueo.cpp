// Fill out your copyright notice in the Description page of Project Settings.


#include "Bloqueo.h"
#include "Components/BoxComponent.h"


// Sets default values
ABloqueo::ABloqueo()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;


    Colision = CreateDefaultSubobject<UBoxComponent>(TEXT("Colision"));

    RootComponent = Colision;

    // Activar colisi¨®n f¨ªsica
    Colision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    // Bloquear todas las colisiones
    Colision->SetCollisionResponseToAllChannels(ECR_Block);


    Malla = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malla"));
    RootComponent = Malla;
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
        TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));
    if (MeshAsset.Succeeded()) {
        Malla->SetStaticMesh(MeshAsset.Object);
    }


}

// Called when the game starts or when spawned
void ABloqueo::BeginPlay()
{



    Super::BeginPlay();

}

// Called every frame
void ABloqueo::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}
