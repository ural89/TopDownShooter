// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FighterPlayerController.generated.h"

/**
 *
 */
UCLASS()
class TOPDOWNSHOOTER_API AFighterPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AFighterPlayerController();
	void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	void MoveRight(float AxisValue);
	void MoveForward(float AxisValue);
	void Interact();
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	class AFighterBase* OwnerFighter;
friend class AFighterBase;
};
