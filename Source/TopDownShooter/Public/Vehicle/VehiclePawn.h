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
	AVehiclePawn();
	virtual void Tick(float DeltaTime) override;
	void Interact(APawn *InteractorPawn) override;

	void MoveForward(float axisValue);
	void MoveRight(float axisValue);
	APawn *GetPawn() override
	{
		return this;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsLeftDoorOpen = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float LeftDoorAngle = 0;

private:
	UFUNCTION()
	void CloseDoor();

	UFUNCTION()
	void OpenDoor();

	class UChaosVehicleMovementComponent* VehicleMovementComponent;
};
