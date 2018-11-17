// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Tank.h"




void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	ATank* AITank = GetControlledTank();
	ATank* PlayerTank = GetPlayerTank();

	if (!AITank)
	{
		UE_LOG(LogTemp, Error, TEXT("No AI Tank found for AI controller %s"), *this->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank: %s"), *AITank->GetName());
	}

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("AI Controller %s couldn't find Player Tank"), *this->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller %s found Player tank: %s"),*this->GetName(), *PlayerTank->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		//TODO Move towards player

		//Aim at the player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
		//Fire if ready
	}
	
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)
	{
		return nullptr;
	}
	else
	{
		return Cast<ATank>(PlayerPawn);
	}
}
