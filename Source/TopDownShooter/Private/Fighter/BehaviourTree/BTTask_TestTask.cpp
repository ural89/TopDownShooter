// Fill out your copyright notice in the Description page of Project Settings.

#include "Fighter/BehaviourTree/BTTask_TestTask.h"

UBTTask_TestTask::UBTTask_TestTask()

{
    NodeName = "MyCustomTestTask";
}
EBTNodeResult::Type UBTTask_TestTask::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    UE_LOG(LogTemp, Warning, TEXT("My test task is executed"));
    return EBTNodeResult::Type();
}