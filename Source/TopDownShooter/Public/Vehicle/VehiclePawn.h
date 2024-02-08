// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "VehiclePawn.generated.h"

/**
 *
 */
UCLASS()
class TOPDOWNSHOOTER_API AVehiclePawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;
};
