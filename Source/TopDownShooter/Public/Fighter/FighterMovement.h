// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "FighterMovement.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API UFighterMovement : public UFloatingPawnMovement
{
	GENERATED_BODY()
public:
	void SetMaxSpeed(float speed) { MaxSpeed = speed;}
	virtual void ApplyControlInputToVelocity(float DeltaTime) override;
};
