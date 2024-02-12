// Fill out your copyright notice in the Description page of Project Settings.

#include "Fighter/FighterBase.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Fighter/FighterMovement.h"
#include "Fighter/Inventory.h"
#include "Interact/InteractInterface.h"
#include "Fighter/FighterPlayerController.h"
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

	MovementComponent = CreateDefaultSubobject<UFighterMovement>(TEXT("MovementComponent")); // NavMesh doesnt work if you dont have ufloatmovementcomponent
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

	TriggerCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("TriggerCollider"));
	TriggerCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	TriggerCollider->SetupAttachment(RootComponent);

	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
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
	// if (!isInCar) //attaching to car
	// {
	// 	if (Car)
	// 	{
	//
	// 	}
	// }
	LookMoveDirection();
	UpdateAnimationVariables();
}
void AFighterBase::NotifyActorBeginOverlap(AActor *OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (IInteractInterface *OverlappedVehicle = Cast<IInteractInterface>(OtherActor))
	{
		Car = OverlappedVehicle;
	}
}

void AFighterBase::NotifyActorEndOverlap(AActor *OtherActor)
{
	if (IInteractInterface *OverlapVehicle = Cast<IInteractInterface>(OtherActor))
	{

		Car = nullptr;
	}
}
void AFighterBase::UpdateMovement()
{
	MoveDirection.Normalize();
	CapsuleComponent->AddForce(MoveDirection * MovePower);
}

void AFighterBase::LookMoveDirection()
{
	// if (!IsDriving)
	LookDirection(MoveDirection);
}

void AFighterBase::LookDirection(FVector LookDirection)
{
	if (LookDirection == FVector::Zero() || CapsuleComponent == nullptr)
		return;
	FRotator LookRotation = LookDirection.Rotation();
	LookRotation = FMath::Lerp(CapsuleComponent->GetComponentRotation(), LookRotation, GetWorld()->GetDeltaSeconds() * 5);
	CapsuleComponent->SetWorldRotation(LookRotation);
}
void AFighterBase::UpdateAnimationVariables()
{
	FVector Velocity = GetVelocity();
	FRotator Rotation = GetActorRotation();
	Velocity = Rotation.UnrotateVector(Velocity);
	FRotator Rotator = Velocity.Rotation();
	float MaxAnimationSpeed = 100;
	float MaxPawnSpeed = 1000;
	CurrentDirection = Rotator.Yaw;
	CurrentMoveSpeed = FMath::Lerp(0, MaxAnimationSpeed, GetVelocity().Length() / MaxPawnSpeed);
}

void AFighterBase::MoveForward(float axisValue)
{
	MoveDirection.X = axisValue;
}

void AFighterBase::MoveRight(float axisValue)
{
	MoveDirection.Y = axisValue;
}
void AFighterBase::Interact()
{
	if (IsDriving)
		return;

	if (Car)
	{
		if (auto controller = Cast<AFighterPlayerController>(GetController()))
		{
			IsDriving = true;
			
			FTimerDelegate GetInVehicleDelegate = FTimerDelegate::CreateUObject(this, &AFighterBase::GetInVehicle, Car);
			FTimerHandle GetInCarTimerHandle;
			GetWorldTimerManager().SetTimer(GetInCarTimerHandle, GetInVehicleDelegate, 1.5f, false);

			CapsuleComponent->SetSimulatePhysics(false);
			CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			MoveDirection = FVector::Zero();
			controller->UnbindInputs();
			Car->Interact(this);
			AttachToActor(Car->GetPawn(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("EnterCarSocket"));
			SetActorRelativeLocation(FVector(0, 0, 0));
			SetActorRelativeRotation(FRotator::ZeroRotator);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Player controller not found!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Car is not attached!"));
	}
}
void AFighterBase::GetInVehicle(IInteractInterface *Vehicle)
{
	// if (Car)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("Car is there"));
	// 	if (Car->GetPawn())
	// 		UE_LOG(LogTemp, Warning, TEXT("Pawn is there in car"));
	// }
	// if (GetController())
	// 	UE_LOG(LogTemp, Warning, TEXT("Controller is there"));
	GetController()->Possess(Vehicle->GetPawn());
	// AttachToActor(Car->GetPawn(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("InCarPawnSocket"));

	// SetActorRelativeLocation(FVector(0, 0, 0));
	// SetActorRelativeRotation(FRotator::ZeroRotator);
}
