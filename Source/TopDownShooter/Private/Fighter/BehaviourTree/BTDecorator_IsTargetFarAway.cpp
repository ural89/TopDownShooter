// Fill out your copyright notice in the Description page of Project Settings.


#include "Fighter/BehaviourTree/BTDecorator_IsTargetFarAway.h"


UBTDecorator_IsTargetFarAway::UBTDecorator_IsTargetFarAway()
{
    NodeName = "Is Target Faraway";
   // bNotifyTick = true;

}

bool UBTDecorator_IsTargetFarAway::CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const
{
    //Super::CalculateRawCondition(OwnerComp, NodeMemory);
    return false;
}

void UBTDecorator_IsTargetFarAway::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
