// Fill out your copyright notice in the Description page of Project Settings.

#include "Vehicle/VehiclePawn.h"
#include "ChaosVehicles/Public/ChaosVehicleMovementComponent.h"

AVehiclePawn::AVehiclePawn()
{
   VehicleMovementComponent = GetVehicleMovement();
}
void AVehiclePawn::Tick(float DeltaSeconds)
{
   Super::Tick(DeltaSeconds);

   if (IsLeftDoorOpen)
   {
      if (LeftDoorAngle < 45)
         LeftDoorAngle += DeltaSeconds * 100;
   }
   else
   {
      if (LeftDoorAngle > 0)
      {
         LeftDoorAngle -= DeltaSeconds * 100;
      }
   }
}
void AVehiclePawn::Interact(APawn *InteractorPawn)
{
   FTimerHandle OpenDoorTimerHandle;
   GetWorldTimerManager().SetTimer(OpenDoorTimerHandle, this, &AVehiclePawn::OpenDoor, 0.9f, false);

   FTimerHandle CloseDoorTimerHandle;
   GetWorldTimerManager().SetTimer(CloseDoorTimerHandle, this, &AVehiclePawn::CloseDoor, 4.f, false);
}
void AVehiclePawn::MoveForward(float axisValue)
{
   if (VehicleMovementComponent)
   {
      VehicleMovementComponent->SetThrottleInput(axisValue);
   }
}
void AVehiclePawn::MoveRight(float axisValue)
{
   if (VehicleMovementComponent)
   {
      // UE_LOG(LogTemp, Warning, TEXT("Right %f"), axisValue);
      VehicleMovementComponent->SetSteeringInput(axisValue);
      // vmc->SetSteeringInput(1.f);
      // vmc->SetThrottleInput(0.4f);
   }
}
void AVehiclePawn::OpenDoor()
{
   IsLeftDoorOpen = true;
}
void AVehiclePawn::CloseDoor()
{
   IsLeftDoorOpen = false;
}