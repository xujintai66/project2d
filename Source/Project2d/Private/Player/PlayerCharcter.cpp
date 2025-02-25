// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharcter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "Sound/SoundBase.h"
#include "Enviroment/ClimbSprite.h"
#include "Enemy/EnemyBase.h"
#include "Materials/MaterialInterface.h"
#include "Game/PlayerController2d.h"
#include <EnhancedInputComponent.h>
#include <Kismet/GameplayStatics.h>



APlayerCharcter::APlayerCharcter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.f;
	FRotator CameraRotatation(0.f, 90.f, 0.f);
	CameraBoom->SetWorldRotation(CameraRotatation);
	CameraBoom->bDoCollisionTest = false;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("Player Camera");
	PlayerCamera->SetupAttachment(CameraBoom);

	UCapsuleComponent* Capsule = GetCapsuleComponent();
	Capsule->SetCapsuleHalfHeight(35.f);
	Capsule->SetCapsuleRadius(30.f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	GetCharacterMovement()->MaxFlySpeed = 200.f;
	GetSprite()->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);

	FlyingFrictionCoefficient = 1000.f;

	AttackDamge = 10.f;

	Health = 100.f;
	MaxHealth = 100.f;
	GodTime = 1.5f;
}

void APlayerCharcter::BeginPlay()
{
	Super::BeginPlay();
	const ULocalPlayer* Player = GetWorld() && GEngine ? GEngine->GetFirstGamePlayer(GetWorld()) : nullptr;
	if (Player) {
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player);
		if (DefaultMapping) {
			Subsystem->AddMappingContext(DefaultMapping, 0);
		}
	}
}

void APlayerCharcter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsDeath)return;
	ChangeMovement();
	CheckBoundary();
	AddForceWhenFlying(DeltaTime);
	Timer += DeltaTime;
	if (Timer > 10) {
		Timer = 0;
	}
}

void APlayerCharcter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharcter::Jump);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharcter::Move);
		EnhancedInputComponent->BindAction(ClimbAction, ETriggerEvent::Triggered, this, &APlayerCharcter::Climb);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &APlayerCharcter::Attack);
	}
}

void APlayerCharcter::Move(const FInputActionValue& Value)
{
	if (IsClimbing || IsAttack ) {
		return;
	}
	float MoveFloat = Value.Get<float>();
	if (Controller) {
		
		FRotator CharcterRotation = Controller->GetControlRotation();
		FVector Direction = FRotationMatrix(CharcterRotation).GetScaledAxis(EAxis::X);
		FVector Movement = Direction * MoveFloat;
		AddMovementInput(Movement);
	}
}

void APlayerCharcter::Jump()
{
	if (IsClimbing || IsAttack || IsDeath) {
		return;
	}
	if (Controller) {
		UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
		if (MovementComponent)
		{
			if (MovementComponent->IsMovingOnGround())
			{
				Super::Jump();
				if (JumpSound != nullptr) {
					UGameplayStatics::PlaySound2D(this, JumpSound);
				}
			}
		}
	}
}

void APlayerCharcter::Climb(const FInputActionValue& Value)
{
	float MoveFloat = Value.Get<float>();
	if (!CanClimb) {
		return;
	}
	FVector CurrentLocation = GetActorLocation();
	if ((CurrentLocation.Z < -1357 && MoveFloat < 0) || (CurrentLocation.Z > -1150 && MoveFloat > 0)) {
		return;
	}
	FVector Direction(0.f, 0.f, 1.f);
	FVector Movement = Direction * MoveFloat;
	if (CurrentLocation.Z > -1160 && MoveFloat > 0) {
		FVector right(-50.f, 0.f, 100.f);
		GetCharacterMovement()->Velocity = right;
		//StopClimbing();
		return;
	}
	AddMovementInput(Movement);
	
}

void APlayerCharcter::Attack()
{
	if (IsClimbing || IsAttack || IsDeath) {
		return;
	}
	if (NowEnum == StateEnum::Jump) {
		return;
	}
	IsAttack = true;
	Timer = 0;
	UPaperFlipbookComponent* Sprit = GetSprite();
	Sprit->SetFlipbook(AttackFilpBook);
	TArray<FHitResult> Hits;
	FCollisionQueryParams Query;
	ECollisionChannel Channel = ECC_Visibility;
	AActor* IgnoreActor = this;
	Query.AddIgnoredActor(IgnoreActor);
	FVector Start = GetActorLocation();
	Start.Z -= 20;
	FVector ForwardV = GetActorForwardVector();
	FRotator r1 = Sprit->GetComponentRotation();
	int IsRight = 1;
	if (r1.Yaw == 180) {
		IsRight = -1;
	}
	FVector End = Start + 100 * ForwardV * IsRight;
	GetWorld()->LineTraceMultiByChannel(Hits, Start, End, Channel, Query);
	DrawDebugLine(GetWorld(), Start, End, FColor::Cyan,true);
	if (HitSound != nullptr) {
		UGameplayStatics::PlaySound2D(this, HitSound);
	}
	for (const FHitResult& Hit : Hits)
	{
		AEnemyBase* HitActor =Cast<AEnemyBase>(Hit.GetActor());
		if (HitActor)
		{
			HitActor->BeAttacked(AttackDamge);
		}
	}
}

void APlayerCharcter::ChangeMovement()
{
	if (IsAttack) {
		if (Timer >= 0.5) {
			IsAttack = false;
		}
		return;
	}
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	UPaperFlipbookComponent* Sprit = GetSprite();
	if (IsClimbing) {
		if (GetCharacterMovement()->Velocity.Z != 0) {
			Sprit->SetFlipbook(ClimbFilpBook);
		}
		else {
			Sprit->SetFlipbook(ClimbIdleFilpBook);
		}
		if (IsSet) {
			return;
		}
		FVector CurrentLocation = GetActorLocation();
		FVector ChangeLocation(ClimbPosition.X, CurrentLocation.Y, CurrentLocation.Z);
		SetActorLocation(ChangeLocation); 
		FVector Zero(0.f, 0.f, 0.f);
		MovementComponent->Velocity = Zero;
		IsSet = true;
		return;
	}
	FVector Speed = MovementComponent->GetLastUpdateVelocity();
	if (Speed.Z != 0 || Speed.Y != 0) {
		NowEnum = StateEnum::Jump;
		Sprit->SetFlipbook(JumpFilpBook);
		
	}
	else {
		if (Speed.X > 0) {
			NowEnum = StateEnum::RunLeft;
			Sprit->SetFlipbook(RunFilpBook);
			FRotator Right(0.f, 0.f, 0.f);
			Sprit->SetWorldRotation(Right);
		}
		else if (Speed.X == 0) {
			NowEnum = StateEnum::Idle;
			Sprit->SetFlipbook(IdleFilpBook);
		}
		else {
			NowEnum = StateEnum::RunRight;
			FRotator Right(0.f, 180.f, 0.f);
			Sprit->SetWorldRotation(Right);
			Sprit->SetFlipbook(RunFilpBook);
		}
	}
}

void APlayerCharcter::CheckBoundary()
{
	FVector NowLocation = GetActorLocation();
	FVector CameraLocation = CameraBoom->GetComponentLocation();
	if (NowLocation.X > LeftBoundary) {
		FVector Left(LeftBoundary, CameraLocation.Y, CameraLocation.Z);
		CameraBoom->SetWorldLocation(Left);
	}
	else if(NowLocation.X < RightBoundary){
		FVector Right(RightBoundary, CameraLocation.Y, CameraLocation.Z);
		CameraBoom->SetWorldLocation(Right);
	}
}

void APlayerCharcter::StartClimbing()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
}

void APlayerCharcter::StopClimbing()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void APlayerCharcter::ChangeCollisionBlock()
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
}

void APlayerCharcter::ChangeCollisionIgnore()
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Ignore);
}

void APlayerCharcter::BeAttacked(float Damge, FVector EnemyForwardVector)
{
	if (!CanBeHit) {
		return;
	}
	CanBeHit = false;
	Hit_Blink();
	GetWorldTimerManager().SetTimer(TimerHandleOfHit, this, &APlayerCharcter::TimerCallbackOfHit, GodTime);
	if (BeHitedSound != nullptr) {
		UGameplayStatics::PlaySound2D(this, BeHitedSound);
	}
	Health -= Damge;
	SetHitedVelocity(EnemyForwardVector);
	OnHealthChanged.Broadcast(Health);
	UE_LOG(LogTemp, Warning, TEXT("%f"), Health);
	if (Health <= 0) {
		UPaperFlipbookComponent* Sprit = GetSprite();
		Sprit->SetFlipbook(DeathFilpBook);
		Health = 0;
		IsDeath = true;
		GetWorldTimerManager().SetTimer(TimerHandleOfDeath, this, &APlayerCharcter::TimerCallbackeOfDeath, 1.5);
	}
}

void APlayerCharcter::SetHitedVelocity(FVector EnemyForwardVector)
{
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	FVector Vec = EnemyForwardVector;
	Vec.Z += 1;
	MovementComponent->Velocity = FVector::ZeroVector;
	MovementComponent->AddImpulse(Vec * 300,true);
}

void APlayerCharcter::Hit_Blink()
{
	TimerCallbackOfShine();
	GetWorldTimerManager().SetTimer(TimerHandleOfShine, this, &APlayerCharcter::TimerCallbackOfShine, GodTime/16,true);
}

void APlayerCharcter::AddForceWhenFlying(float DeltaTime)
{
	if (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Flying)
	{
		FVector CurrentVelocity = GetCharacterMovement()->Velocity;
		if (!CurrentVelocity.IsNearlyZero())
		{
			// 计算摩擦力影响后的速度
			FVector FrictionVector = -CurrentVelocity.GetSafeNormal() * FlyingFrictionCoefficient * DeltaTime;
			CurrentVelocity += FrictionVector;

			// 防止速度反向
			if (FVector::DotProduct(CurrentVelocity, GetCharacterMovement()->Velocity) < 0.f)
			{
				CurrentVelocity = FVector::ZeroVector;
			}

			// 更新角色速度
			GetCharacterMovement()->Velocity = CurrentVelocity;
		}
	}
}

void APlayerCharcter::TimerCallbackOfHit()
{
	CanBeHit = true;
	RemoveTimer();
}

void APlayerCharcter::TimerCallbackOfShine()
{
	UPaperFlipbookComponent* Sprit = GetSprite();
	if (IsShine) {
		IsShine = !IsShine;
		Sprit->SetMaterial(0, StartMaterial);
		FLinearColor ShineColor(1.f, 1.f, 1.f, 1.f);
		Sprit->SetSpriteColor(ShineColor);
	}
	else {
		IsShine = !IsShine;
		Sprit->SetMaterial(0, ShineMaterial);
		FLinearColor ShineColor(1.f, 1.f, 1.f, 0.5f);
		Sprit->SetSpriteColor(ShineColor);
	}
}

void APlayerCharcter::TimerCallbackeOfDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("death"));
	APlayerController2d* Control = Cast<APlayerController2d>(GetController());
	if (Control) {
		Control->ShowRestart();
	}
}

void APlayerCharcter::RemoveTimer()
{
	GetWorldTimerManager().ClearTimer(TimerHandleOfShine);
	UPaperFlipbookComponent* Sprit = GetSprite();
	Sprit->SetMaterial(0, StartMaterial);
	FLinearColor ShineColor(1.f, 1.f, 1.f, 1.f);
	Sprit->SetSpriteColor(ShineColor);
}

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealth)
//{
//}
