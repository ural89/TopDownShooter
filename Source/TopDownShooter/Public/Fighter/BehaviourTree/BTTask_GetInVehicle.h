// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GetInVehicle.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API UBTTask_GetInVehicle : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
	
};
