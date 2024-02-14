// Fill out your copyright notice in the Description page of Project Settings.

#include "Fighter/BehaviourTree/BTTask_GetInVehicle.h"
#include "Fighter/FighterBase.h"
#include "AIController.h"
EBTNodeResult::Type UBTTask_GetInVehicle::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    if (auto OwnerFighter = Cast<AFighterBase>(OwnerComp.GetAIOwner()->GetPawn()))
    {
      
        OwnerFighter->Interact();

        return EBTNodeResult::Succeeded;
    }
 
    return EBTNodeResult::Failed;
}