// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;
class ATank;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 4000; //TODO find 

	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	//Local barrel reference for projectile spawning
	UTankBarrel* Barrel = nullptr;

	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;
protected:
	UTankAimingComponent* TankAimingComponent = nullptr;
public:	
	void AimAt(FVector HitLocation);	

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel *BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret *TurretToSet);

	

	
};
