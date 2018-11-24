// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Components/ActorComponent.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	//Get the controlled tank
	auto OurTankName = GetOwner()->GetName();
	auto OurTank = GetOwner();
	//Check for nullpointers in references
	if (!Barrel)
	{
		return;
	}
	if (!Turret)
	{
		return;
	}
	//Out parameter for launch velocity
	FVector OutLaunchVelocity;
	//Get the socket location for where we want the projectile to spawn
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileSocket"));
	//Calculate the OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace // Paramater must be present to prevent bug
	);

	if(bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//Move the barrel and/or rotate the turret
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel *BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret *TurretToSet)
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//Get difference between barrel rotation and the aiming location
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//Start rotating the barrel in the intended direction at a constant speed
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}
