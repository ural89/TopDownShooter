// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "Interact/InteractInterface.h"
#include "VehiclePawn.generated.h"
/**
 *
 */
UCLASS()
class TOPDOWNSHOOTER_API AVehiclePawn : public AWheeledVehiclePawn, public IInteractInterface
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;
	void Interact(APawn* InteractorPawn) override;

	APawn* GetPawn() override
	{
		return this;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsDoorOpen = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float LeftDoorAngle = 0;
};
