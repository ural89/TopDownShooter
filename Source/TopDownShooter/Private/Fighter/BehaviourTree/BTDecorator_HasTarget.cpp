// Fill out your copyright notice in the Description page of Project Settings.

#include "Fighter/BehaviourTree/BTDecorator_HasTarget.h"
#include "Fighter/FighterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_HasTarget::UBTDecorator_HasTarget()
{
    NodeName = "Has Target?";
    INIT_DECORATOR_NODE_NOTIFY_FLAGS();
}
bool UBTDecorator_HasTarget::CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const
{
    UE_LOG(LogTemp, Warning, TEXT("Evauliating")); //This not evaluating unless something has changed from blackboard!
    return Cast<AFighterAIController>(OwnerComp.GetAIOwner())->GetTargetActor() != nullptr;
}
void UBTDecorator_HasTarget::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) // needs to have abort mode to tick!
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
    // if(Cast<AFighterAIController>(OwnerComp.GetAIOwner())->GetTargetActor() != nullptr)
    // {

    //     OwnerComp.RequestExecution(this); //this will execute like true condition
    // }
}