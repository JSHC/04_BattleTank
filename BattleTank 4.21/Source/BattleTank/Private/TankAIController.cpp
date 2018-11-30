// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "AIController.h"
#include "TankAimingComponent.h"




void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	ControlledTank = GetPawn();

	if (ensure(ControlledTank))
	{
		AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	}
	

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	if (!ensure(PlayerTank && AimingComponent && ControlledTank)) { return; }

	MoveToActor(PlayerTank,AcceptanceRadius);
	//Aim at the player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	//Fire if ready
	AimingComponent->Fire();
	
}



