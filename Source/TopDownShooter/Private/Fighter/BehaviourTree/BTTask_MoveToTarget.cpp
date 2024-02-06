// Fill out your copyright notice in the Description page of Project Settings.

#include "Fighter/BehaviourTree/BTTask_MoveToTarget.h"
#include "Fighter/FighterAIController.h"

UBTTask_MoveToTarget::UBTTask_MoveToTarget()
{
    NodeName = "Move to Target";
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    if (auto FighterOwner = Cast<AFighterAIController>(OwnerComp.GetAIOwner()))
    {
        // FighterOwner->MoveToTarget();
        return EBTNodeResult::InProgress;
    }
    return EBTNodeResult::Failed;
}

void UBTTask_MoveToTarget::TickTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    if (auto FighterOwner = Cast<AFighterAIController>(OwnerComp.GetAIOwner()))
    {
        FighterOwner->MoveToTarget();
    }
}
