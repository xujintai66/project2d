// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerController2d.generated.h"

class UCharcterSelect;
class APlayerCharcter;
class UHealthUI;
class URestartUI;
/**
 * 
 */
UCLASS()
class PROJECT2D_API APlayerController2d : public APlayerController
{
	GENERATED_BODY()
public:
	void BeginPlay() override;

	void Hide();
	void Show();
	void ShowHealth();
	void ShowRestart();

	void SpawnCharacter(TSubclassOf<APlayerCharcter> PlayerCharcter);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCharcterSelect> CharcterSelectClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UHealthUI> HealthUIClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URestartUI> RestartClass;

	//0Å®1ÄÐ
	int NowCharacter = 0;

private:
	UPROPERTY()
	TObjectPtr<UCharcterSelect> CharcterSelect;
	UPROPERTY()
	TObjectPtr<UHealthUI> HealthUI;
	UPROPERTY()
	TObjectPtr<URestartUI> Restart;
};
