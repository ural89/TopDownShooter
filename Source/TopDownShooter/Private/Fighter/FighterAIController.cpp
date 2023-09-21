// Fill out your copyright notice in the Description page of Project Settings.

#include "Fighter/FighterAIController.h"
#include "Fighter/FighterBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
AFighterAIController::AFighterAIController()
{
    PrimaryActorTick.bCanEverTick = true;
    SetupPerception();
}
void AFighterAIController::SetupPerception()
{
    AISight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
    SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent")));
    AISight->SightRadius = sightRadius;
    AISight->LoseSightRadius = looseSightRadius;
    AISight->PeripheralVisionAngleDegrees = 180;
    AISight->DetectionByAffiliation.bDetectEnemies = true;
    AISight->DetectionByAffiliation.bDetectFriendlies = true;
    AISight->DetectionByAffiliation.bDetectNeutrals = true;
    AISight->AutoSuccessRangeFromLastSeenLocation = 1500;
    PerceptionComponent->ConfigureSense(*AISight);
    PerceptionComponent->SetDominantSense(AISight->GetSenseImplementation());
    PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AFighterAIController::OnPerceptionUpdated);
}
void AFighterAIController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);
    OwnerFighter = Cast<AFighterBase>(InPawn);

    FTimerHandle CreatePathTimerHandle;
    GetWorld()->GetTimerManager().SetTimer(CreatePathTimerHandle, this, &AFighterAIController::UpdatePath, 0.1f, true);
}
void AFighterAIController::BeginPlay()
{
    Super::BeginPlay();
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
    UE_LOG(LogTemp, Warning, TEXT("MoveDirection %f, %f"), Destination.X, Destination.Y);
}
void AFighterAIController::MoveToDirection()
{
    FVector MoveDirection = GetPathFollowingComponent()->GetCurrentDirection();
    OwnerFighter->MoveForward(MoveDirection.X);
    OwnerFighter->MoveRight(MoveDirection.Y);
}

void AFighterAIController::OnPerceptionUpdated(AActor *Actor, FAIStimulus Stimulus)
{
    if (Actor)
    {
        canMove = true;
        UE_LOG(LogTemp, Warning, TEXT("Percieved Actor"));
    }
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

        Stop();
    }
}