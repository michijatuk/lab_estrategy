#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Premio.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class DEF_PRACTICA_API APremio : public AActor
{
	GENERATED_BODY()

public:
	APremio();

	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnPickupOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, Category = "Premio")
	USphereComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Category = "Premio")
	UStaticMeshComponent* PremioMesh;

	UPROPERTY(EditAnywhere, Category = "Premio")
	float RotationSpeed = 120.f;
};