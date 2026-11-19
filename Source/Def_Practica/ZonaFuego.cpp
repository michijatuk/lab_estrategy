// Fill out your copyright notice in the Description page of Project Settings.


#include "ZonaFuego.h"

#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "UObject/ConstructorHelpers.h"

AZonaFuego::AZonaFuego()
{
    PrimaryActorTick.bCanEverTick = false;

    Zona = CreateDefaultSubobject<UBoxComponent>(TEXT("Zona"));
    RootComponent = Zona;

    Zona->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Zona->SetCollisionResponseToAllChannels(ECR_Overlap);

    SonidoFuego = CreateDefaultSubobject<UAudioComponent>(TEXT("SonidoFuego"));
    SonidoFuego->SetupAttachment(RootComponent);
    SonidoFuego->bAutoActivate = false;

    ConstructorHelpers::FObjectFinder<USoundBase> SonidoAsset(
        TEXT("/Game/StarterContent/Audio/Fire01.Fire01")
    );

    if (SonidoAsset.Succeeded())
    {
        Sonido = SonidoAsset.Object;
    }

    Zona->OnComponentBeginOverlap.AddDynamic(
        this,
        &AZonaFuego::AlEntrar
    );

    Zona->OnComponentEndOverlap.AddDynamic(
        this,
        &AZonaFuego::AlSalir
    );
}


void AZonaFuego::AlEntrar(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (OtherActor)
    {
        if (Sonido)
        {
            SonidoFuego->SetSound(Sonido);
            SonidoFuego->Play();
        }

        UE_LOG(
            LogTemp,
            Warning,
            TEXT("El jugador entro en la zona de fuego")
        );
    }
}


void AZonaFuego::AlSalir(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex)
{
    if (OtherActor)
    {
        if (SonidoFuego)
        {
            SonidoFuego->Stop();
        }

        UE_LOG(
            LogTemp,
            Warning,
            TEXT("El jugador salio de la zona de fuego")
        );
    }
}