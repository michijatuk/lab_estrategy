// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "EnemyStrategy.h"

class FIdleStrategy : public IEnemyStrategy
{
public:

    virtual void Execute(AEnemy* Enemy,float DeltaTime) override;
};
