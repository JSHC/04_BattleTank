// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Projectile.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = GetWorld()->GetTimeSeconds(); //First fire after initial reload
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Check firing state
	if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		CurrentFiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		CurrentFiringState = EFiringState::Aiming;
	}
	else
	{
		CurrentFiringState = EFiringState::Ready;
	}
}

void UTankAimingComponent::Initialise(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	//Get the controlled tank
	auto OurTankName = GetOwner()->GetName();
	auto OurTank = GetOwner();
	//Check for nullpointers in references
	if (!ensure(Barrel && Turret)) { return; }
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		//Move the barrel and/or rotate the turret
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) ||  !ensure(Turret)) { return; }
	//Get difference between barrel rotation and the aiming location
	
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//Start rotating the barrel in the intended direction at a constant speed
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	bool bIsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;
	//UE_LOG(LogTemp, Warning, TEXT("Fire called at %f"), LastFireTime);
	if (bIsReloaded)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		auto SocketLocation = Barrel->GetSocketLocation(FName("ProjectileSocket"));
		//Spawn a projectile at Socket location
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		//Launch the projectile
		Projectile->Launch(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{	
	if (!ensure(Barrel)) { return false; }
	auto BarrelForwardVector = Barrel->GetForwardVector();
	//If the forwardvector differs from the aimdirection the barrel is moving
	return !AimDirection.Equals(BarrelForwardVector, 0.01);
}




