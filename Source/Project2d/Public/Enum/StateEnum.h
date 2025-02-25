// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateEnum.generated.h"

/**
 * 
 */


UENUM(BlueprintType)
enum class StateEnum : uint8
{
    Idle UMETA(DisplayName = "Idle"),
    RunLeft UMETA(DisplayName = "RunLeft"),
    RunRight UMETA(DisplayName = "RunRight"),
    Jump UMETA(DisplayName = "Jump"),
    Falling UMETA(DisplayName = "Falling")
};

