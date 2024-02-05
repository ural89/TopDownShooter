// Fill out your copyright notice in the Description page of Project Settings.

#include "Fighter/BehaviourTree/BTTask_TestTask.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TestTask::UBTTask_TestTask()

{
    NodeName = "MyCustomTestTask";
}
EBTNodeResult::Type UBTTask_TestTask::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    return EBTNodeResult::Failed;
}