// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MoveToTarget.generated.h"

/**
 *
 */
UENUM(BlueprintType)
enum class EMoveType : uint8
{
	Enemy,
	Car,
};

UCLASS()
class TOPDOWNSHOOTER_API UBTTask_MoveToTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_MoveToTarget();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
	void OnTaskFinished(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, EBTNodeResult::Type TaskResult);

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	EMoveType MoveType;
};
