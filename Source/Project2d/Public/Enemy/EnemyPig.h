// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyBase.h"
#include "EnemyPig.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT2D_API AEnemyPig : public AEnemyBase
{
	GENERATED_BODY()
public:
	AEnemyPig();
	virtual float DamgePass() override;
};
