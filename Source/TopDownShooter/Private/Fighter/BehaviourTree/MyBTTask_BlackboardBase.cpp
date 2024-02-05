// Fill out your copyright notice in the Description page of Project Settings.


#include "Fighter/BehaviourTree/MyBTTask_BlackboardBase.h"


EBTNodeResult::Type UMyBTTask_BlackboardBase::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    UE_LOG(LogTemp, Warning, TEXT("TaskExecuted"));
    return EBTNodeResult::Type();
}
UMyBTTask_BlackboardBase::UMyBTTask_BlackboardBase()
{
    NodeName = "MyCustomTask";
}