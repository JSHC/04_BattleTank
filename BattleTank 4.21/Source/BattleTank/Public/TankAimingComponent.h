// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Ready
};

class UTankBarrel; ///Forward declaration
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	//void SetBarrelReference(UTankBarrel *BarrelToSet);
	//void SetTurretReference(UTankTurret *TurretToSet);
	void AimAt(FVector HitLocation, float LaunchSpeed);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet);


protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState CurrentFiringState = EFiringState::Aiming;


private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	//TODO add SetTurretComponent
	void MoveBarrelTowards(FVector AimDirection);

};
