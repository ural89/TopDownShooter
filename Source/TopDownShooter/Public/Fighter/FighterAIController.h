// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FighterAIController.generated.h"

/**
 *
 */
UCLASS()
class TOPDOWNSHOOTER_API AFighterAIController : public AAIController
{
	GENERATED_BODY()

public:
	AFighterAIController();
	void Tick(float DeltaTime) override;
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult &Result) override;
	virtual void BeginPlay() override;

	AActor *GetTargetActor() const
	{
		return TargetActor;
	}
	void MoveToTarget();
	void LookAtTarget();

protected:
	virtual void OnPossess(APawn *InPawn) override;

private:
	bool canMove = false;
	float stoppingRange = 200;

	// Perception variables
	float sightRadius = 600;
	float looseSightRadius = 200;

	class AFighterBase *OwnerFighter;
	class UAISenseConfig_Sight *AISight;
	AActor *TargetActor;

	void SetupPerception();
	void UpdatePath();

	void Stop();

	UFUNCTION()
	void OnPerceptionUpdated(AActor *Actor, FAIStimulus Stimulus);

	UPROPERTY(EditAnywhere)
	class UBehaviorTree *PedestrianBehavior;
};
