// Fill out your copyright notice in the Description page of Project Settings.

#include "Fighter/FighterAIController.h"
#include "Fighter/FighterBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Interact/InteractInterface.h"
#include "Vehicle/VehiclePawn.h"
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
    AISight->DetectionByAffiliation.bDetectFriendlies = false;
    AISight->DetectionByAffiliation.bDetectNeutrals = false;
    AISight->AutoSuccessRangeFromLastSeenLocation = 1500;
    PerceptionComponent->ConfigureSense(*AISight);
    PerceptionComponent->SetDominantSense(AISight->GetSenseImplementation());
    PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AFighterAIController::OnPerceptionUpdated);
}
void AFighterAIController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);
    OwnerFighter = Cast<AFighterBase>(InPawn);
    OwnerVehicle = Cast<AVehiclePawn>(InPawn);
    if (OwnerFighter)
    {
        if (PedestrianBehavior != nullptr)
        {
            RunBehaviorTree(PedestrianBehavior);
        }
    }
    if (OwnerVehicle)
    {
        if (CarDriveBehaviour != nullptr)
        {
            RunBehaviorTree(CarDriveBehaviour);
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("InPawn name %s"), *(InPawn->GetName()));

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
        FVector DirectionToTarget = GetPathFollowingComponent()->GetCurrentDirection();

        FVector MoveDirection = DirectionToTarget;
        if (OwnerFighter)
        {

            OwnerFighter->MoveForward(MoveDirection.Y);
            OwnerFighter->MoveRight(MoveDirection.X);
        }
        if (OwnerVehicle)
        {
            FVector LocalDirection = OwnerVehicle->GetTransform().InverseTransformVectorNoScale(DirectionToTarget);
            FVector RotatedDirection = FVector(LocalDirection.Y, -LocalDirection.X, LocalDirection.Z);
            OwnerVehicle->MoveForward(1);
            OwnerVehicle->MoveRight(RotatedDirection.X);
        }
    }
    else
    {
        // UE_LOG(LogTemp, Warning, TEXT("No move target"));
        Stop();
    }
}
void AFighterAIController::LookAtTarget()
{
    if (OwnerFighter && LookTarget)
    {
        FVector DirectionToTarget = (LookTarget->GetActorLocation() - OwnerFighter->GetActorLocation()).GetSafeNormal();
        OwnerFighter->LookDirection(DirectionToTarget);
    }
}
void AFighterAIController::OnPerceptionUpdated(AActor *Actor, FAIStimulus Stimulus) // this is only called once detected
{
    if (Actor)
    {
        if (const APawn *OtherPawn = Cast<APawn>(Actor))
        {
            if (IGenericTeamAgentInterface *OtherTeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
            {
                if (OtherTeamAgent->GetGenericTeamId() == 1)
                {
                    PercievedEnemy = Actor;
                    canMove = true;
                    UE_LOG(LogTemp, Warning, TEXT("Percieved Actor %s"), *(Actor->GetName()));
                    UpdatePath();
                }
            }
        }
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
    if (OwnerFighter)
    {
        if (OwnerFighter->Vehicle)
            MoveTarget = OwnerFighter->Vehicle->GetPawn();
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("AI cant find car!!!"));
        }
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
    if (OwnerFighter && MoveTarget)
    {
        return FVector::Dist(OwnerFighter->GetActorLocation(), MoveTarget->GetActorLocation());
    }
    return 100000;
}
void AFighterAIController::Stop()
{
    if (OwnerFighter)
    {
        OwnerFighter->MoveForward(0);
        OwnerFighter->MoveRight(0);
        canMove = false;
    }
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

ETeamAttitude::Type AFighterAIController::GetTeamAttitudeTowards(const AActor &Other) const
{
    if (const APawn *OtherPawn = Cast<APawn>(&Other))
    {
        if (IGenericTeamAgentInterface *OtherTeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
        {
            UE_LOG(LogTemp, Warning, TEXT("Percieved actir id: %i"), OtherTeamAgent->GetGenericTeamId());
            if (OtherTeamAgent->GetGenericTeamId() == 1)
                return ETeamAttitude::Hostile;
            else
            {
                return ETeamAttitude::Neutral;
            }
        }
    }

    return ETeamAttitude::Neutral;
}