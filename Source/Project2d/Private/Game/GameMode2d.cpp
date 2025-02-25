// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameMode2d.h"
#include "Game/PlayerController2d.h"
#include "Player/PlayerCharcter.h"

void AGameMode2d::BeginPlay()
{
	Super::BeginPlay();
}

void AGameMode2d::ChangeDefualt(int now)
{
	if (now == 0) {
		UE_LOG(LogTemp, Warning, TEXT("0"));
		DefaultPawnClass = WomanCharacter;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("1"));
		DefaultPawnClass = ManCharacter;
	}
}
