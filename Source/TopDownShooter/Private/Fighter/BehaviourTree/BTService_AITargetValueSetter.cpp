// Fill out your copyright notice in the Description page of Project Settings.


#include "Fighter/BehaviourTree/BTService_AITargetValueSetter.h"
#include "Fighter/FighterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_AITargetValueSetter::UBTService_AITargetValueSetter()
{
    NodeName = "TargetActorSetter";
}
void UBTService_AITargetValueSetter::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
     if (auto TargetActor = Cast<AFighterAIController>(OwnerComp.GetAIOwner())->GetTargetActor())
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), TargetActor);
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}
