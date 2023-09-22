// Fill out your copyright notice in the Description page of Project Settings.

#include "Fighter/Inventory.h"
#include "Fighter/Weapon.h"
// Sets default values for this component's properties
UInventory::UInventory()
{

	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();
	USkeletalMeshComponent *SkeletalMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	AWeapon *Weapon = GetWorld()->SpawnActor<AWeapon>(CurrentWeapon);
	if (SkeletalMesh)
	{
		Weapon->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	}
}

// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
