// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RandomPositionNode.generated.h"

struct FBlackboardKeySelector;
/**
 * 
 */
UCLASS()
class PROJECT2D_API URandomPositionNode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	URandomPositionNode();
protected:
    // 执行任务
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    // 随机位置的搜索半径
    UPROPERTY(EditAnywhere, Category = "AI")
    float Radius = 600.f;

    UPROPERTY(EditAnywhere, Category = "AI")
    FBlackboardKeySelector BlackboardKey;
};
