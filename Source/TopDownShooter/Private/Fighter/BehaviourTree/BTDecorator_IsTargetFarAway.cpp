// Fill out your copyright notice in the Description page of Project Settings.


#include "Fighter/BehaviourTree/BTDecorator_IsTargetFarAway.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsTargetFarAway::UBTDecorator_IsTargetFarAway()
{
    NodeName = "Is Target Faraway";
   // bNotifyTick = true;

}

bool UBTDecorator_IsTargetFarAway::CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const
{
    //Super::CalculateRawCondition(OwnerComp, NodeMemory);
    UE_LOG(LogTemp, Display, TEXT("Distance is "));

    return OwnerComp.GetBlackboardComponent()->GetValueAsFloat(GetSelectedBlackboardKey()) > FarawayDistance;
}

void UBTDecorator_IsTargetFarAway::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
