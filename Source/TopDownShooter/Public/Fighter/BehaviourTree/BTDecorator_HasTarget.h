// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_HasTarget.generated.h"

/**
 *
 */
UCLASS()
class TOPDOWNSHOOTER_API UBTDecorator_HasTarget : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTDecorator_HasTarget();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const override;
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
};
