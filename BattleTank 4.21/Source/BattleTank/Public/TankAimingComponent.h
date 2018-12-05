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

UENUM()
enum class EAmmoState : uint8
{
	Empty,
	Has_ammo
};

class UTankBarrel; ///Forward declaration
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	void MoveBarrelTowards(FVector AimDirection);

	UPROPERTY(EditAnywhere, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;

	FVector AimDirection;

	int32 CurrentAmmo = 0;

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	//void SetBarrelReference(UTankBarrel *BarrelToSet);
	//void SetTurretReference(UTankTurret *TurretToSet);
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	bool IsBarrelMoving();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void BeginPlay() override;
	EFiringState GetCurrentFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	int32 GetCurrentAmmo() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState CurrentFiringState = EFiringState::Aiming;
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EAmmoState CurrentAmmoState = EAmmoState::Has_ammo;
	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	uint32 MaxAmmo = 10;




};
