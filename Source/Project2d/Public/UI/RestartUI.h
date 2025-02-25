// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RestartUI.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class PROJECT2D_API URestartUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	UFUNCTION()
	void RestartGame();
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Restart;
};
