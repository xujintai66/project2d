// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Game/EnemyAiController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "Player/PlayerCharcter.h"

AEnemyBase::AEnemyBase()
{
	EnemyCapsule = GetCapsuleComponent();
	EnemyCapsule->SetCapsuleHalfHeight(30.f);
	EnemyCapsule->SetCapsuleRadius(30.f);
	EnemyCapsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	EnemyCapsule->SetCollisionResponseToChannel(ECC_Camera, ECR_Overlap);
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Health = 40.f;
	MaxHealth = 40.f;

	
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	if (EnemyCapsule) {
		EnemyCapsule->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnOverlapBegin);
		EnemyCapsule->OnComponentEndOverlap.AddDynamic(this, &AEnemyBase::OnOverlapEnd);
	}
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ChangeFilpBook();
	Timer += DeltaTime;
	if (Timer > 10) {
		Timer = 0;
	}
}

void AEnemyBase::ChangeFilpBook()
{
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	FVector NowVelocity = MovementComponent->GetLastUpdateVelocity();
	UPaperFlipbookComponent* Sprit = GetSprite();
	if (IsDeath) {
		Sprit->SetFlipbook(DeathFilpBook);
		return;
	}
	if (IsHit) {
		if (IsSet) {
			Timer = 0;
			IsSet = false;
		}
		Sprit->SetFlipbook(HitedFilpBook);
		if (Timer >= 0.3) {
			IsHit = false;
		}
		return;
	}
	if (NowVelocity.X != 0) {
		Sprit->SetFlipbook(RunFilpBook);
	}
	else {
		Sprit->SetFlipbook(IdleFilpBook);
	}
}

//overlap
void AEnemyBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsDeath||IsHit) {
		return;
	}
	APlayerCharcter* Player = Cast<APlayerCharcter>(OtherActor);
	FVector Forward = GetActorForwardVector();
	if (Player) {
		Player->BeAttacked(DamgePass(), Forward);
	}
}

void AEnemyBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharcter* Player = Cast<APlayerCharcter>(OtherActor);
	if (Player) {
		//UE_LOG(LogTemp, Warning, TEXT("SADDAS"));
	}
}

float AEnemyBase::DamgePass()
{
	UE_LOG(LogTemp, Warning, TEXT("Base"));
	return AttackDamge;
}


void AEnemyBase::BeAttacked(float Damge)
{
	Health -= Damge;
	IsHit = true;
	IsSet = true;
	if (GetWorldTimerManager().IsTimerActive(TimerHandle))
	{
		return;
	}
	if (Health <= 0) {
		IsDeath = true;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyBase::TimerCallback, 2.0f);
	}
}

void AEnemyBase::TimerCallback()
{
	Destroy();
}
