// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	ATank* AITank = GetControlledTank();
	if (!AITank)
	{
		UE_LOG(LogTemp, Error, TEXT("No AI Tank found for AI controller %s"), *this->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank: %s"), *AITank->GetName());
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
