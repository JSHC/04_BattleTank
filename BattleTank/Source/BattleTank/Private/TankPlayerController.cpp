// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"



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
	//AimTowardsCrosshair

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
	else
	{
		//Get world location through crosshair (Line trace)
		//If linetrace hits landscape
			//Aim the controlled tank at the line trace
	}
}

