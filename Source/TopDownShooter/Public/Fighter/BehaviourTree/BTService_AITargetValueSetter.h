// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_AITargetValueSetter.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API UBTService_AITargetValueSetter : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_AITargetValueSetter();
protected:
	void TickNode(UBehaviorTreeComponent &OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
