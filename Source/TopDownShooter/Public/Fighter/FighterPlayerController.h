// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "FighterPlayerController.generated.h"

/**
 *
 */
UCLASS()
class TOPDOWNSHOOTER_API AFighterPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	AFighterPlayerController();
	void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	void MoveRight(float AxisValue);
	void MoveForward(float AxisValue);
	void BindInputs();
	void UnbindInputs();
	void Interact();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn *InPawn) override;

private:
	void Stop();

	class AFighterBase *OwnerFighter;
	class AVehiclePawn *OwnerVehicle;

	FGenericTeamId TeamId;
	FGenericTeamId GetGenericTeamId() const;
	
	friend class AFighterBase;
};
