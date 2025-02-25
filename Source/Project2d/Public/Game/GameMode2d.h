// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode2d.generated.h"

class APlayerCharcter;
/**
 * 
 */
UCLASS()
class PROJECT2D_API AGameMode2d : public AGameModeBase
{
	GENERATED_BODY()
public:
	void BeginPlay() override;
	void ChangeDefualt(int now);

	FORCEINLINE TSubclassOf<APlayerCharcter> ReturnW() { return WomanCharacter; }
	FORCEINLINE TSubclassOf<APlayerCharcter> ReturnM() { return ManCharacter; }
private:
	UPROPERTY(EditDefaultsOnly, Category = Character)
	TSubclassOf<APlayerCharcter> WomanCharacter;
	UPROPERTY(EditDefaultsOnly, Category = Character)
	TSubclassOf<APlayerCharcter> ManCharacter;
};
