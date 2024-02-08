// Fill out your copyright notice in the Description page of Project Settings.

#include "Fighter/FighterPlayerController.h"
#include "Fighter/FighterBase.h"
#include "Vehicle/VehiclePawn.h"
AFighterPlayerController::AFighterPlayerController()
{
}

void AFighterPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    BindInputs();
}
void AFighterPlayerController::BindInputs()
{
    InputComponent->BindAxis(TEXT("MoveForward"), this, &AFighterPlayerController::MoveForward);
    InputComponent->BindAxis(TEXT("MoveRight"), this, &AFighterPlayerController::MoveRight);
    InputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed, this, &AFighterPlayerController::Interact);
}
void AFighterPlayerController::UnbindInputs()
{
    InputComponent->RemoveAxisBinding(TEXT("MoveForward"));
    InputComponent->RemoveAxisBinding(TEXT("MoveRight"));
    InputComponent->RemoveActionBinding(TEXT("Interact"), EInputEvent::IE_Pressed);
}
void AFighterPlayerController::BeginPlay()
{
    Super::BeginPlay();
}

void AFighterPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (OwnerFighter)
        OwnerFighter->LookMoveDirection();
}
void AFighterPlayerController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);
    OwnerFighter = Cast<AFighterBase>(InPawn);
    OwnerVehicle = Cast<AVehiclePawn>(InPawn);
    if (OwnerFighter)
        UE_LOG(LogTemp, Warning, TEXT("Fighter possessed!"));
    if(OwnerVehicle)
        UE_LOG(LogTemp, Warning, TEXT("Vehicle possessed!"));
}

void AFighterPlayerController::Stop()
{
    OwnerFighter->MoveRight(0);
    OwnerFighter->MoveForward(0);
}
void AFighterPlayerController::MoveRight(float AxisValue)
{

    if (OwnerFighter)
        OwnerFighter->MoveRight(AxisValue);
}
void AFighterPlayerController::MoveForward(float AxisValue)
{
    if (OwnerFighter)
        OwnerFighter->MoveForward(AxisValue);
}

void AFighterPlayerController::Interact()
{
    if (OwnerFighter)
        OwnerFighter->Interact();
}
