// Fill out your copyright notice in the Description page of Project Settings.

#include "Fighter/FighterAIController.h"
#include "Fighter/FighterBase.h"

AFighterAIController::AFighterAIController()
{
    PrimaryActorTick.bCanEverTick = true;
}
void AFighterAIController::OnPossess(APawn *InPawn)
{

    Super::OnPossess(InPawn);
    OwnerFighter = Cast<AFighterBase>(InPawn);
    FTimerHandle CreatePathTimerHandle;
    GetWorld()->GetTimerManager().SetTimer(CreatePathTimerHandle, this, &AFighterAIController::UpdatePath, 0.1f, true);
}

void AFighterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (canMove)
    {
        MoveToDirection();
    }
}

void AFighterAIController::UpdatePath()
{
    FVector Destination = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
    MoveToLocation(Destination, stoppingRange, true, true);
}
void AFighterAIController::MoveToDirection()
{
    FVector MoveDirection = GetPathFollowingComponent()->GetCurrentDirection();
    OwnerFighter->MoveForward(MoveDirection.X);
    OwnerFighter->MoveRight(MoveDirection.Y);
}
void AFighterAIController::Stop()
{
    OwnerFighter->MoveForward(0);
    OwnerFighter->MoveRight(0);
    canMove = false;
}
void AFighterAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult &Result)
{
    Super::OnMoveCompleted(RequestID, Result);
    if (Result.IsSuccess())
    {
        UE_LOG(LogTemp, Warning, TEXT("Path completed"));
        Stop();
    }
}