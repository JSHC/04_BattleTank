// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"




void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* PlayerTank = GetControlledTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("No Player Tank found for Player Controller %s"), *this->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank: %s"), *PlayerTank->GetName());
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
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		//Aim the controlled tank at the line trace
	}
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	//Cast ray towards crosshair
	FHitResult OutHitResult;
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairPosX, ViewportSizeY * CrosshairPosY);

	//De-project screen position of the crosshair to a world direction
	//Line-trace along that direction, get hit result (Up to max range)

	/*GetWorld()->LineTraceSingleByObjectType(OutHitResult,
		,
		End,
		FCollisionObjectQueryParams()
		)*/
		//If ray intersects with landscape
			//Return true
		//If it doesn't hit landscape
			//Return false
	//OutHitLocation = OutHitResult.Location;
	return false;
}

