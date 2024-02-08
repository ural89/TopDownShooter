// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FighterBase.generated.h"

UCLASS()
class TOPDOWNSHOOTER_API AFighterBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFighterBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveForward(float axisValue);
	void MoveRight(float axisValue);
	void LookMoveDirection();
	void LookDirection(FVector LookDirection);
	void Interact();
	// Animation variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentMoveSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsDriving = false;

	UPROPERTY(EditAnywhere)
	APawn *Car; // TODO: delete
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool isInCar = false;
	void UpdateMovement();
	void UpdateAnimationVariables();

	void GetInVehicle(class AVehiclePawn &Vehicle);

	UPROPERTY(EditAnywhere)
	class UCapsuleComponent *CapsuleComponent;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent *MeshComponent;

	UPROPERTY()
	class UFighterMovement *MovementComponent;

	UPROPERTY(EditAnywhere)
	class UInventory *Inventory;

	UPROPERTY(EditAnywhere)
	float MovePower = 250000.f;

	UPROPERTY()
	FVector MoveDirection = FVector::Zero();

	UPROPERTY(EditAnywhere)
	class UCameraComponent *Camera;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent *SpringArm;
};
