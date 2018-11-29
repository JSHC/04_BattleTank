// Fill out your copyright notice in the Description page of Project Settings.
#include "Tank.h"
#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"
#include "GameFramework/Actor.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	UE_LOG(LogTemp, Warning, TEXT("468de2ed: Constructor called on %s"), *AActor::GetName())
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("468de2ed: BeginPlay C++ called on %s"), *AActor::GetName())
}

void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("No Aiming Component on %s"), *AActor::GetName())
		return;
	}
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	if (!Barrel)
	{
		UE_LOG(LogTemp, Error, TEXT("No barrel reference in ATank::Fire() on %s"), *AActor::GetName())
		return;
	}
	bool bIsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;
	
	//UE_LOG(LogTemp, Warning, TEXT("Fire called at %f"), LastFireTime);
	if (Barrel && bIsReloaded)
	{
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
