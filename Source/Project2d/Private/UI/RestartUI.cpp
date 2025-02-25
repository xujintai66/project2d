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
        // ��ȡ��ǰ�ؿ�����
        FString  CurrentLevelName = CurrentWorld->GetMapName();
        // �Ƴ�·��ǰ׺
        FName Name1 = FPackageName::GetShortFName(CurrentLevelName);

        // ���´򿪵�ǰ�ؿ�
        UGameplayStatics::OpenLevel(CurrentWorld, Name1);
    }
}
