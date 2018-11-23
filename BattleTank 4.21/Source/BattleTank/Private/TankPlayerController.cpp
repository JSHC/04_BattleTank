// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "Tank.h"




void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("No Player Tank found for Player Controller %s"), *this->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank: %s"), *ControlledTank->GetName());
	}
	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}




ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}
	FVector HitLocation; //Out parameter
	//Get world location through crosshair (Line trace)
	if (GetSightRayHitLocation(HitLocation))
	{
		//Aim the controlled tank at the line trace
		GetControlledTank()->AimAt(HitLocation);
	}
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	
	//De-project screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//Line-trace along that direction, get hit result (Up to max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
	FVector CameraWorldLocation; //To be discarded, not used
	return  DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
	FHitResult OutHitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (
		GetWorld()->LineTraceSingleByChannel(
			OutHitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = OutHitResult.Location;
		return true;
	}
	else
	{
		HitLocation = FVector(0);
		return false;
	}
	
}

