// Fill out your copyright notice in the Description page of Project Settings.

#include "Fighter/BehaviourTree/BTTask_MoveToTarget.h"
#include "Fighter/FighterAIController.h"

UBTTask_MoveToTarget::UBTTask_MoveToTarget()
{
    NodeName = "Move to Target";
    bNotifyTick = true;
    bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    if (auto FighterOwner = Cast<AFighterAIController>(OwnerComp.GetAIOwner()))
    {
        switch (MoveType)
        {
        case EMoveType::Enemy:
            FighterOwner->SetMoveTargetToEnemy();
            UE_LOG(LogTemp, Warning, TEXT("SettoEnemy"));
            break;

        case EMoveType::Car:
            FighterOwner->SetMoveTargetToCar();
            UE_LOG(LogTemp, Warning, TEXT("SettoCar"));
            break;
        }
        return EBTNodeResult::InProgress;
    }
    UE_LOG(LogTemp, Warning, TEXT("Failed"));
    return EBTNodeResult::Failed;
}

void UBTTask_MoveToTarget::OnTaskFinished(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, EBTNodeResult::Type TaskResult)
{
    Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
    //UE_LOG(LogTemp, Warning, TEXT("TaskFinished"));
    if (auto FighterOwner = Cast<AFighterAIController>(OwnerComp.GetAIOwner()))
    {
        FighterOwner->ClearMoveTarget();
    }
}