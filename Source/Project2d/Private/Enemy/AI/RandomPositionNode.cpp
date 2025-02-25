// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AI/RandomPositionNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "Game/EnemyAiController.h"

URandomPositionNode::URandomPositionNode()
{
}

EBTNodeResult::Type URandomPositionNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // 获取 AI 控制器和 Pawn
    AEnemyAiController* AIController = Cast<AEnemyAiController>(OwnerComp.GetAIOwner());
    APawn* AIPawn = AIController->GetPawn();
    if (!AIPawn)
    {
        return EBTNodeResult::Failed;
    }

    // 获取导航系统
    UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(AIPawn->GetWorld());
    if (!NavSystem)
    {
        return EBTNodeResult::Failed;
    }

    // 生成随机位置
    FNavLocation RandomLocation;
    if (NavSystem->GetRandomReachablePointInRadius(AIPawn->GetActorLocation(), Radius, RandomLocation))
    {
        // 将随机位置存储到黑板
        UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
        if (BlackboardComp)
        {
            FVector CurrentLocation = AIPawn->GetActorLocation();
            FVector NewLocation = RandomLocation.Location;
            NewLocation.Y = CurrentLocation.Y; // 保持 Y 轴不变
            BlackboardComp->SetValueAsVector(BlackboardKey.SelectedKeyName, NewLocation);
            return EBTNodeResult::Succeeded;
        }
    }

    // 如果未找到随机位置，返回失败
    return EBTNodeResult::Failed;
}
