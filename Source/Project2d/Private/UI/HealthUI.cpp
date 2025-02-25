// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HealthUI.h"
#include "Player/PlayerCharcter.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHealthUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	APlayerCharcter* OwningCharacter = Cast<APlayerCharcter>(GetOwningPlayerPawn());
	if (OwningCharacter != nullptr) {
		OwningCharacter->OnHealthChanged.AddDynamic(this, &UHealthUI::SetPercent);
		SetPercent(OwningCharacter->GetMaxHealth());
	}
	
}

void UHealthUI::SetPercent(float NewHealth)
{
	APlayerCharcter* OwningCharacter = Cast<APlayerCharcter>(GetOwningPlayerPawn());
	UE_LOG(LogTemp, Warning, TEXT("brodcast"));
	if (OwningCharacter) {
		float Percent = NewHealth / OwningCharacter->GetMaxHealth();
		Health->SetPercent(Percent);
		FText PercentText = FText::AsPercent(Percent);
		HealthText->SetText(PercentText);
	}
	
}
