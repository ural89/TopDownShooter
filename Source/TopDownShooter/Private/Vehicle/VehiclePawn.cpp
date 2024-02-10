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
   if (IsLeftDoorOpen)
   {
      if (LeftDoorAngle < 45)
         LeftDoorAngle += DeltaSeconds * 100;
   }
   else
   {
      if(LeftDoorAngle > 0)
      {
         LeftDoorAngle -= DeltaSeconds * 100;
      }
   }
}
void AVehiclePawn::Interact(APawn *InteractorPawn)
{
   FTimerHandle CloseDoorTimerHandle;
   GetWorldTimerManager().SetTimer(CloseDoorTimerHandle, this, &AVehiclePawn::CloseDoor, 2.f, false, 2.f);
   IsLeftDoorOpen = true;
   // LeftDoorAngle = 45;
   UE_LOG(LogTemp, Warning, TEXT("Interacted"));
}

void AVehiclePawn::CloseDoor()
{
   IsLeftDoorOpen = false;
   UE_LOG(LogTemp, Warning, TEXT("Door closed"));
}