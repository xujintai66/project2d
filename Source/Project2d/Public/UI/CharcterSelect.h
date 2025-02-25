// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharcterSelect.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class PROJECT2D_API UCharcterSelect : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Woman;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Man;

protected:
	UFUNCTION()
	void ChooseWoman();
	UFUNCTION()
	void ChooseMan();
};
