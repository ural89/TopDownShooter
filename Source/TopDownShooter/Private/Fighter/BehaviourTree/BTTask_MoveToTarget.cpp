// Fill out your copyright notice in the Description page of Project Settings.

#include "Fighter/BehaviourTree/BTTask_MoveToTarget.h"
#include "Fighter/FighterAIController.h"
//TODO: create enum for look targets

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
        FighterOwner->SetMoveTargetToEnemy();
        return EBTNodeResult::InProgress;
    }
    return EBTNodeResult::Failed;
}

void UBTTask_MoveToTarget::OnTaskFinished(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, EBTNodeResult::Type TaskResult)
{
    Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
    UE_LOG(LogTemp, Warning, TEXT("TaskFinished"));
    //TODO: clear move target
}