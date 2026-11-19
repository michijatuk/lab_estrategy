#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mina.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class DEF_PRACTICA_API AMina : public AActor
{
	GENERATED_BODY()

public:
	AMina();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnMineOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	void Arm();
	void Explode(AActor* Victim);

	UPROPERTY(VisibleAnywhere, Category = "Mina")
	USphereComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Category = "Mina")
	UStaticMeshComponent* MineMesh;

	// Segundos antes de que la mina se active
	UPROPERTY(EditAnywhere, Category = "Mina")
	float ArmingTime = 1.f;

	bool bArmed = false;
	FTimerHandle ArmTimer;
};