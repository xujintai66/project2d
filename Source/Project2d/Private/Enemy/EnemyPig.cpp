// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyPig.h"
#include "Player/PlayerCharcter.h"
#include "Components/CapsuleComponent.h"

AEnemyPig::AEnemyPig()
{
	AttackDamge = 10.f;
}

float AEnemyPig::DamgePass()
{
	return AttackDamge;
}


