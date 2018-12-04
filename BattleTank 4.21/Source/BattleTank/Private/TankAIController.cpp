// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "AIController.h"
#include "TankAimingComponent.h"
#include "Engine/Public/DrawDebugHelpers.h"




void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	ControlledTank = GetPawn();

	if (ensure(ControlledTank))
	{
		AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	}
	UE_LOG(LogTemp, Warning, TEXT("AcceptanceRadius: %f"), AcceptanceRadius);
	

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugSphere(GetWorld(), GetPawn()->GetActorLocation(), AcceptanceRadius, 32, FColor::Red);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetPawn()->GetActorLocation().ToCompactString())
	

	if (!ensure(PlayerTank && AimingComponent && ControlledTank)) { return; }

	MoveToActor(PlayerTank,AcceptanceRadius);
	//Aim at the player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	//Fire if ready
	if (AimingComponent->GetCurrentFiringState() == EFiringState::Ready)
	{
		AimingComponent->Fire();
	}
	
	
}



