// Fill out your copyright notice in the Description page of Project Settings.

#include "Fighter/BehaviourTree/BTService_CalcDistantanceTarget.h"
#include "Fighter/FighterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
UBTService_CalcDistantanceTarget::UBTService_CalcDistantanceTarget()
{
    NodeName = "Calculate distance to target";
}

void UBTService_CalcDistantanceTarget::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    if (auto OwnerFighter = Cast<AFighterAIController>(OwnerComp.GetAIOwner()))
        OwnerComp.GetBlackboardComponent()->SetValueAsFloat(GetSelectedBlackboardKey(), OwnerFighter->GetDistanceToTarget());
}