// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthUI.generated.h"

class UProgressBar;
class UTextBlock;
/**
 * 
 */

UCLASS()
class PROJECT2D_API UHealthUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	UFUNCTION()
	void SetPercent(float NewHealth);
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> Health;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> HealthText;

};
