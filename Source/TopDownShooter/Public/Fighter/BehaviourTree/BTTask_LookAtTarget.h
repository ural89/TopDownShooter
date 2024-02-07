// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_LookAtTarget.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API UBTTask_LookAtTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_LookAtTarget();
protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
	void OnTaskFinished(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, EBTNodeResult::Type TaskResult);
};
