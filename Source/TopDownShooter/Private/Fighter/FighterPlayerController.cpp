// Fill out your copyright notice in the Description page of Project Settings.

#include "Fighter/FighterPlayerController.h"
#include "Fighter/FighterBase.h"
AFighterPlayerController::AFighterPlayerController()
{
}

void AFighterPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    InputComponent->BindAxis(TEXT("MoveForward"), this, &AFighterPlayerController::MoveForward);
    InputComponent->BindAxis(TEXT("MoveRight"), this, &AFighterPlayerController::MoveRight); // TODO: make this controller as default player controller
} // TODO: delete player fighter script make only one type
void AFighterPlayerController::BeginPlay()
{
    Super::BeginPlay();
}
void AFighterPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    OwnerFighter = Cast<AFighterBase>(InPawn);
    if(!OwnerFighter) 
        UE_LOG(LogTemp, Warning, TEXT("Fighter not found!"));
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
