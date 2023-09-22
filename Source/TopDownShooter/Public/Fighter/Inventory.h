// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

class AWeapon;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNSHOOTER_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventory();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:


	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> CurrentWeapon;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AWeapon>> Weapons;

		
};
