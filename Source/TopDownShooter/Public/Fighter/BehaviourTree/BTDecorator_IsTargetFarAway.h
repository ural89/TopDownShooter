// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_IsTargetFarAway.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API UBTDecorator_IsTargetFarAway : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTDecorator_IsTargetFarAway();
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const override;
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float FarawayDistance = 500;

};
