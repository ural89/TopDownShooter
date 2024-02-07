// Fill out your copyright notice in the Description page of Project Settings.

#include "Fighter/BehaviourTree/BTTask_LookAtTarget.h"
#include "Fighter/FighterAIController.h"

// TODO: create enum for look targets

UBTTask_LookAtTarget::UBTTask_LookAtTarget()
{
    NodeName = "LookAtTarget";
}
EBTNodeResult::Type UBTTask_LookAtTarget::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    if (auto FighterOwner = Cast<AFighterAIController>(OwnerComp.GetAIOwner()))
    {
        FighterOwner->SetLookTargetToEnemy();
        return EBTNodeResult::InProgress;
    }
    return EBTNodeResult::Failed;
}

void UBTTask_LookAtTarget::OnTaskFinished(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, EBTNodeResult::Type TaskResult)
{
    Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

    if (auto FighterOwner = Cast<AFighterAIController>(OwnerComp.GetAIOwner()))
    {
        FighterOwner->ClearLookTarget();
    }
}
