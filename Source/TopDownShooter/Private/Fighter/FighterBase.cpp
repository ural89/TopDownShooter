// Fill out your copyright notice in the Description page of Project Settings.

#include "Fighter/FighterBase.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Fighter/FighterMovement.h"
// Sets default values
AFighterBase::AFighterBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetCapsuleHalfHeight(95);
	CapsuleComponent->SetCapsuleRadius(22);
	CapsuleComponent->SetSimulatePhysics(true);
	CapsuleComponent->SetLinearDamping(3);
	CapsuleComponent->SetAngularDamping(3);
	CapsuleComponent->BodyInstance.bLockXRotation = true;
	CapsuleComponent->BodyInstance.bLockYRotation = true;
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleComponent->SetCollisionResponseToChannels(ECollisionResponse::ECR_Block);
	SetRootComponent(CapsuleComponent);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);

	MovementComponent = CreateDefaultSubobject<UFighterMovement>(TEXT("MovementComponent")); //NavMesh doesnt work if you dont have ufloatmovementcomponent
	MovementComponent->UpdatedComponent = RootComponent;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 800;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
	SpringArm->SetRelativeRotation(FRotator(-45, 0, 0)); // careful to use this after you attach to root component

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void AFighterBase::BeginPlay()
{
	Super::BeginPlay();
	MovementComponent->SetMaxSpeed(0);
}

// Called every frame
void AFighterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateMovement();
	LookMoveDirection(DeltaTime);

}

void AFighterBase::UpdateMovement()
{
	MoveDirection.Normalize();
	CapsuleComponent->AddForce(MoveDirection * MovePower);
}
void AFighterBase::LookMoveDirection(float DeltaTime)
{
	FRotator LookRotation = MoveDirection.Rotation();
	LookRotation = FMath::Lerp(CapsuleComponent->GetComponentRotation(), LookRotation, DeltaTime * 5);
	if (MoveDirection != FVector::Zero())
		CapsuleComponent->SetWorldRotation(LookRotation);
}
void AFighterBase::MoveForward(float axisValue)
{
	MoveDirection.X = axisValue;
}

void AFighterBase::MoveRight(float axisValue)
{
	MoveDirection.Y = axisValue;
}
