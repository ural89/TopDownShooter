// Fill out your copyright notice in the Description page of Project Settings.

#include "Vehicle/VehiclePawn.h"
#include "ChaosVehicles/Public/ChaosVehicleMovementComponent.h"
void AVehiclePawn::Tick(float DeltaSeconds)
{
   Super::Tick(DeltaSeconds);


   if (UChaosVehicleMovementComponent *VehicleMovementComponent = GetVehicleMovement())
   {
      VehicleMovementComponent->SetSteeringInput(34.0f); 
      VehicleMovementComponent->SetThrottleInput(0.4f);
   }
}