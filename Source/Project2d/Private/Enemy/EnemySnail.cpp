// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemySnail.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemySnail::AEnemySnail()
{
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	Capsule->SetCapsuleHalfHeight(15.f);
	Capsule->SetCapsuleRadius(15.f);
	GetCharacterMovement()->MaxWalkSpeed = 100.f;

	AttackDamge = 5.f;
}

float AEnemySnail::DamgePass()
{
	return AttackDamge;
}
