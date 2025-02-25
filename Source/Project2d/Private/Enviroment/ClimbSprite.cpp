// Fill out your copyright notice in the Description page of Project Settings.


#include "Enviroment/ClimbSprite.h"
#include "PaperSpriteComponent.h"
#include "Engine/CollisionProfile.h"
#include "Components/BoxComponent.h"
#include "Player/PlayerCharcter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

AClimbSprite::AClimbSprite()
{
	UPaperSpriteComponent* body = GetRenderComponent();
	body->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	body->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>("CollisonBox"); 
	CollisionBox->SetupAttachment(RootComponent);
	FVector Extent(5.f, 5.f, 60.f);
	CollisionBox->SetBoxExtent(Extent);
	CollisionBox->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	CanClimbCollisionBox = CreateDefaultSubobject<UBoxComponent>("ClimbCollisonBox");
	CanClimbCollisionBox->SetupAttachment(RootComponent);
	FVector Extent1(5.f, 5.f, 80.f);
	CanClimbCollisionBox->SetBoxExtent(Extent1);
	CanClimbCollisionBox->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
}

void AClimbSprite::BeginPlay()
{
	Super::BeginPlay();
	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AClimbSprite::OnOverlapBegin);
		CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AClimbSprite::OnOverlapEnd);
	}
	if (CanClimbCollisionBox) {
		CanClimbCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AClimbSprite::OnOverlapBeginOfClimb);
		CanClimbCollisionBox->OnComponentEndOverlap.AddDynamic(this, &AClimbSprite::OnOverlapEndOfClimb);
	}
}

void AClimbSprite::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharcter* Player = Cast<APlayerCharcter>(OtherActor);
	if (Player) {
		Player->IsClimbing = true;
		Player->ClimbPosition = GetActorLocation();
		Player->ChangeCollisionIgnore();
		Player->CanStop = true;
	}
}

void AClimbSprite::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharcter* Player = Cast<APlayerCharcter>(OtherActor);
	if (Player) {
		Player->IsClimbing = false;
		FVector clearVector(0.f, 0.f, 0.f);
		Player->ClimbPosition = clearVector;
		Player->IsSet = false;
		Player->ChangeCollisionBlock();
	}
}

void AClimbSprite::OnOverlapBeginOfClimb(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharcter* Player = Cast<APlayerCharcter>(OtherActor);
	if (Player) {
		Player->CanClimb = true;
		Player->ClimbPosition = GetActorLocation();
		Player->StartClimbing();
	}
}

void AClimbSprite::OnOverlapEndOfClimb(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharcter* Player = Cast<APlayerCharcter>(OtherActor);
	if (Player) {
		Player->CanClimb = false;
		FVector clearVector(0.f, 0.f, 0.f);
		Player->ClimbPosition = clearVector;
		Player->StopClimbing();
	}
}
