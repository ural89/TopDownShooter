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
protected:
	virtual void OnPossess(APawn *InPawn) override;

private:
	bool canMove = true;
	float stoppingRange = 200;
	
	class AFighterBase* OwnerFighter;
	
	void UpdatePath();
	void MoveToDirection();
	void Stop();


};
