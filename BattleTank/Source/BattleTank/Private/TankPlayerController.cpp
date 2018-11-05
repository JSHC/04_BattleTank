// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* PlayerTank = GetControlledTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Player tank: %s"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank: %s"), *PlayerTank->GetName());
	}
	
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

