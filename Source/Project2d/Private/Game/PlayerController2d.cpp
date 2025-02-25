// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PlayerController2d.h"
#include "UI/CharcterSelect.h"
#include "Player/PlayerCharcter.h"
#include "UI/HealthUI.h"
#include "UI/RestartUI.h"

void APlayerController2d::BeginPlay()
{
	Super::BeginPlay();
	if (CharcterSelectClass != nullptr) {
		SetPause(true);
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		CharcterSelect = CreateWidget<UCharcterSelect>(this, CharcterSelectClass); 
		CharcterSelect->AddToViewport();
	}
}

void APlayerController2d::Hide()
{
	CharcterSelect->RemoveFromParent();
	CharcterSelect->Destruct();
	SetPause(false);
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
	
}

void APlayerController2d::Show()
{
	if (CharcterSelect != nullptr) {
		SetPause(true);
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		CharcterSelect = CreateWidget<UCharcterSelect>(this, CharcterSelectClass);
		CharcterSelect->AddToViewport();
	}
}

void APlayerController2d::ShowHealth()
{
	if (HealthUIClass != nullptr) {
		HealthUI = CreateWidget<UHealthUI>(this, HealthUIClass);
		HealthUI->AddToViewport();
	}
}

void APlayerController2d::ShowRestart()
{
	SetPause(true);
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
	if (RestartClass != nullptr) {
		Restart = CreateWidget<URestartUI>(this, RestartClass);
		Restart->AddToViewport();
	}
}

void APlayerController2d::SpawnCharacter(TSubclassOf<APlayerCharcter> PlayerCharcter)
{
	APlayerCharcter* CurrentCharacter = Cast<APlayerCharcter>(GetPawn());
	UWorld* World = GetWorld();
	if (CurrentCharacter) {
		FVector ALocation = CurrentCharacter->GetActorLocation();
		FRotator ARotation = CurrentCharacter->GetActorRotation();
		CurrentCharacter->Destroy();
		APlayerCharcter* NowCharacter1 = World->SpawnActor<APlayerCharcter>(PlayerCharcter, ALocation, ARotation);
		if (NowCharacter1) {
			Possess(NowCharacter1);
		}
	}
	ShowHealth();
}
