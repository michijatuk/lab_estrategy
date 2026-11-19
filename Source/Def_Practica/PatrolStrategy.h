// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyStrategy.h"

class AEnemy;

class FPatrolStrategy : public IEnemyStrategy
{
public:
	FPatrolStrategy();

	virtual void Execute(AEnemy* Enemy, float DeltaTime) override;

	float TimeToMine;
	float MineInterval;

private:
	void PickNewDirection();

	FVector Direction;
	float TimeToChange;


};