// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAiController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;
class AEnemyBase;
/**
 * 
 */
UCLASS()
class PROJECT2D_API AEnemyAiController : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyAiController();
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
	UBehaviorTreeComponent* BehaviorTreeComponent;
	UPROPERTY(EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
	UBlackboardComponent* BlackBoardComponent;
	UPROPERTY(EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviorTree;

	TObjectPtr<AEnemyBase> Enemy;
};
