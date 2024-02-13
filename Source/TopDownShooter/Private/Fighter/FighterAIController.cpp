// Fill out your copyright notice in the Description page of Project Settings.

#include "Fighter/FighterAIController.h"
#include "Fighter/FighterBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Interact/InteractInterface.h"
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
    if (PedestrianBehavior != nullptr)
    {
        RunBehaviorTree(PedestrianBehavior);
    }
}
void AFighterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    MoveToTarget();
    LookAtTarget();
}

void AFighterAIController::UpdatePath() // TODO: wire this to BT to a service
{
    if (MoveTarget)
    {
        FVector Destination = MoveTarget->GetActorLocation();
        MoveToLocation(Destination, 1, false); // TODO: create your own MoveToLocation with navigationv1 (it is written inside MoveToLocation method)
    }
}
void AFighterAIController::MoveToTarget()
{
    if (MoveTarget)
    {
        FVector DirectionToTarget = GetPathFollowingComponent()->GetCurrentDirection(); // (TargetActor->GetActorLocation() - OwnerFighter->GetActorLocation()).GetSafeNormal();

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
    if (LookTarget)
    {
        FVector DirectionToTarget = (LookTarget->GetActorLocation() - OwnerFighter->GetActorLocation()).GetSafeNormal();
        OwnerFighter->LookDirection(DirectionToTarget);
    }
}
void AFighterAIController::OnPerceptionUpdated(AActor *Actor, FAIStimulus Stimulus) // this is only called once detected
{
    if (Actor) // TODO: add if enemy for this actor
    {
        PercievedEnemy = Actor;
        canMove = true;
        UE_LOG(LogTemp, Warning, TEXT("Percieved Actor"));
        UpdatePath();
    }
    else // TODO: handle forgetting
    {
        UE_LOG(LogTemp, Warning, TEXT("NOT Percieved Actor"));
        PercievedEnemy = nullptr;
    }
}
void AFighterAIController::SetLookTargetToEnemy()
{
    LookTarget = PercievedEnemy;
}
void AFighterAIController::SetMoveTargetToEnemy()
{
    UE_LOG(LogTemp, Warning, TEXT("MoveTarget set to enemy"));
    MoveTarget = PercievedEnemy;
}

void AFighterAIController::SetMoveTargetToCar()
{
    if (OwnerFighter->Vehicle)
        MoveTarget = OwnerFighter->Vehicle->GetPawn();
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AI cant find car!!!"));
    }
}
void AFighterAIController::ClearMoveTarget()
{
    MoveTarget = nullptr;
}
void AFighterAIController::ClearLookTarget()
{
    LookTarget = nullptr;
}
float AFighterAIController::GetDistanceToTarget()
{
    if (MoveTarget)
    {
        return FVector::Dist(OwnerFighter->GetActorLocation(), MoveTarget->GetActorLocation());
    }
    return 100000;
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