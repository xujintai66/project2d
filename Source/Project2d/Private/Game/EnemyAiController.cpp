// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/EnemyAiController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Enemy/EnemyBase.h"

AEnemyAiController::AEnemyAiController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackBoardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	
}

void AEnemyAiController::BeginPlay()
{
	Super::BeginPlay();
	AEnemyBase* e1 = Cast<AEnemyBase>(GetPawn());
	if (e1) {
		UE_LOG(LogTemp, Warning, TEXT("end1111"));
		Enemy = e1;
	}
	if (BehaviorTree)
	{
		if (BehaviorTree->BlackboardAsset)
		{
			BlackBoardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		}
		RunBehaviorTree(BehaviorTree);
	}
}

void AEnemyAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Enemy) {
		if (Enemy->IsHit || Enemy->IsDeath) {
			BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
		}
		else {
			RunBehaviorTree(BehaviorTree);
		}
	}
}
