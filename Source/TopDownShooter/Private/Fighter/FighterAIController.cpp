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
    // GetWorld()->GetTimerManager().SetTimer(CreatePathTimerHandle, this, &AFighterAIController::UpdatePath, 0.1f, true);
}
void AFighterAIController::BeginPlay()
{
    Super::BeginPlay();
}
void AFighterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (TargetActor)
    {
        LookAtTarget();
        //MoveToTarget();
    }
}

void AFighterAIController::UpdatePath()
{
    if (TargetActor)
    {
        FVector Destination = TargetActor->GetActorLocation();
        // UE_LOG(LogTemp, Warning, TEXT("MoveDirection %f, %f"), Destination.X, Destination.Y);
    }
}
void AFighterAIController::MoveToTarget()
{
    if (TargetActor)
    {
        FVector DirectionToTarget = (TargetActor->GetActorLocation() - OwnerFighter->GetActorLocation()).GetSafeNormal();

        FVector MoveDirection = DirectionToTarget;

        OwnerFighter->MoveForward(MoveDirection.X);
        OwnerFighter->MoveRight(MoveDirection.Y);
    }
    else
    {
        Stop();
    }
}
void AFighterAIController::LookAtTarget()
{
    if (TargetActor)
    {
        FVector DirectionToTarget = (TargetActor->GetActorLocation() - OwnerFighter->GetActorLocation()).GetSafeNormal();
       // UE_LOG(LogTemp, Warning, TEXT("%f, %f"), DirectionToTarget.X, DirectionToTarget.Y);
        OwnerFighter->LookDirection(DirectionToTarget);
    }
}
void AFighterAIController::OnPerceptionUpdated(AActor *Actor, FAIStimulus Stimulus) // this is only called once detected
{
    if (Actor)
    {
        TargetActor = Actor;
        canMove = true;
        UE_LOG(LogTemp, Warning, TEXT("Percieved Actor"));
        UpdatePath();
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
        TargetActor = nullptr;
        //   Stop();
    }
}