// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RestartUI.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void URestartUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (Restart) {
		Restart->OnClicked.AddDynamic(this, &URestartUI::RestartGame);
	}
}

void URestartUI::RestartGame()
{
    UWorld* CurrentWorld = GetWorld();
    if (CurrentWorld)
    {
        // 获取当前关卡名称
        FString  CurrentLevelName = CurrentWorld->GetMapName();
        // 移除路径前缀
        FName Name1 = FPackageName::GetShortFName(CurrentLevelName);

        // 重新打开当前关卡
        UGameplayStatics::OpenLevel(CurrentWorld, Name1);
    }
}
