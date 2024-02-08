// Fill out your copyright notice in the Description page of Project Settings.

#include "Vehicle/VehiclePawn.h"
#include "ChaosVehicles/Public/ChaosVehicleMovementComponent.h"
void AVehiclePawn::Tick(float DeltaSeconds)
{
   Super::Tick(DeltaSeconds);


   if (UChaosVehicleMovementComponent *vmc = GetVehicleMovement())
   {
      // vmc->SetSteeringInput(1.f); 
      // vmc->SetThrottleInput(0.4f);
   }
}