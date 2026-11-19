// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



class AEnemy;
class IEnemyStrategy
{
public:

	virtual ~IEnemyStrategy() = default;

	virtual void Execute(
		AEnemy* Enemy,
		float DeltaTime) = 0;

};