// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyBase.h"
#include "EnemySnail.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT2D_API AEnemySnail : public AEnemyBase
{
	GENERATED_BODY()
public:
	AEnemySnail();
	virtual float DamgePass() override;
};
