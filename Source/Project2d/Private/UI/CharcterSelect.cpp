// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CharcterSelect.h"
#include "Components/Button.h"
#include "Game/PlayerController2d.h"
#include "Game/GameMode2d.h"

void UCharcterSelect::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (Woman != nullptr) {
		Woman->OnClicked.AddDynamic(this, &UCharcterSelect::ChooseWoman);
	}
	if (Man != nullptr) {
		Man->OnClicked.AddDynamic(this, &UCharcterSelect::ChooseMan);
	}
}

void UCharcterSelect::ChooseWoman()
{
	APlayerController2d* PlayerController = Cast<APlayerController2d>(GetOwningPlayer());
	if (PlayerController) {
		PlayerController->NowCharacter = 0;
		PlayerController->Hide();
		AGameMode2d* GameMode =Cast<AGameMode2d>(GetWorld()->GetAuthGameMode());
		GameMode->ChangeDefualt(0);
		PlayerController->SpawnCharacter(GameMode->ReturnW());
	}
	
}

void UCharcterSelect::ChooseMan()
{
	APlayerController2d* PlayerController = Cast<APlayerController2d>(GetOwningPlayer());
	if (PlayerController) {
		PlayerController->NowCharacter = 1;
		PlayerController->Hide();
		AGameMode2d* GameMode = Cast<AGameMode2d>(GetWorld()->GetAuthGameMode());
		GameMode->ChangeDefualt(1);
		PlayerController->SpawnCharacter(GameMode->ReturnM());
	}
	
}
