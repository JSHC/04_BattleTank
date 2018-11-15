// Fill out your copyright notice in the Description page of Project Settings.
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	auto OurTankName = GetOwner()->GetName();
	auto OurTank = GetOwner();
	//Check for nullpointer
	if (!Barrel)
	{
		return;
	}
	//Out parameter for launch velocity
	FVector OutLaunchVelocity;
	//Get the socket location for where we want the projectile to spawn
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileSocket"));

	FCollisionResponseParams OutParams;
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(OurTank);
	//Calculate the OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::TraceFullPath,
		OutParams,
		IgnoredActors,
		true
	);
	if(bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto BarrelLocation = Barrel->GetComponentLocation().ToString();
		//UE_LOG(LogTemp, Warning, TEXT("%s aiming at: %s from %s, firing at %f"), *OurTankName, *AimDirection.ToString(), *BarrelLocation, LaunchSpeed);
		//Move the barrel
		MoveBarrelTowards(AimDirection);
		

	}
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent *BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//Get difference between barrel rotation and the aiming location
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimDirectionRotator = AimDirection.Rotation();
	auto DeltaRotator = AimDirectionRotator - BarrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("AimDirectionRotator: %s"), *AimDirectionRotator.ToString());
	//Start rotating the barrel in the intended direction at a constant speed

}