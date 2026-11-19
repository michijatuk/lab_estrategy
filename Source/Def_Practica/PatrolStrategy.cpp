#include "PatrolStrategy.h"
#include "Enemy.h"

FPatrolStrategy::FPatrolStrategy()
	: Direction(FVector::ZeroVector)
	, TimeToChange(0.f)
	, TimeToMine(2.f)
	, MineInterval(2.f)
{
}
void FPatrolStrategy::PickNewDirection()
{
	// Direcci¨®n aleatoria en el plano horizontal
	const float Angle = FMath::FRandRange(0.f, 360.f);
	Direction = FRotator(0.f, Angle, 0.f).Vector();

	// Mantiene esa direcci¨®n entre 1 y 3 segundos
	TimeToChange = FMath::FRandRange(1.f, 3.f);
}

void FPatrolStrategy::Execute(AEnemy* Enemy, float DeltaTime)
{
	if (!Enemy)
	{
		return;
	}

	TimeToChange -= DeltaTime;

	if (TimeToChange <= 0.f || Direction.IsNearlyZero())
	{
		PickNewDirection();
	}


	TimeToMine -= DeltaTime;

	if (TimeToMine <= 0.f)
	{
		Enemy->DropMine();
		TimeToMine = MineInterval;
	}

	Enemy->AddMovementInput(Direction, 1.f);
}