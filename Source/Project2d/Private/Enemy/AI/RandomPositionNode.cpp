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
    // ��ȡ AI �������� Pawn
    AEnemyAiController* AIController = Cast<AEnemyAiController>(OwnerComp.GetAIOwner());
    APawn* AIPawn = AIController->GetPawn();
    if (!AIPawn)
    {
        return EBTNodeResult::Failed;
    }

    // ��ȡ����ϵͳ
    UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(AIPawn->GetWorld());
    if (!NavSystem)
    {
        return EBTNodeResult::Failed;
    }

    // �������λ��
    FNavLocation RandomLocation;
    if (NavSystem->GetRandomReachablePointInRadius(AIPawn->GetActorLocation(), Radius, RandomLocation))
    {
        // �����λ�ô洢���ڰ�
        UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
        if (BlackboardComp)
        {
            FVector CurrentLocation = AIPawn->GetActorLocation();
            FVector NewLocation = RandomLocation.Location;
            NewLocation.Y = CurrentLocation.Y; // ���� Y �᲻��
            BlackboardComp->SetValueAsVector(BlackboardKey.SelectedKeyName, NewLocation);
            return EBTNodeResult::Succeeded;
        }
    }

    // ���δ�ҵ����λ�ã�����ʧ��
    return EBTNodeResult::Failed;
}
