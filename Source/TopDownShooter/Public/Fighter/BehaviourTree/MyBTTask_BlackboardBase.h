// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_BlackboardBase.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API UMyBTTask_BlackboardBase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UMyBTTask_BlackboardBase();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
