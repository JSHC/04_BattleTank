// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "AIController.h"
#include "TankAimingComponent.h"
#include "Engine/Public/DrawDebugHelpers.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Tank.h"
#include "Delegates/Delegate.h"




void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn *InPawn)
{
	Super::SetPawn(InPawn);
		if (InPawn)
		{
			auto PossessedTank = Cast<ATank>(InPawn);

			// TODO Subscribe to tank death broadcast event
			PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
		}
}

void ATankAIController::OnPossedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("AI Tank died"))
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugSphere(GetWorld(), GetPawn()->GetActorLocation(), AcceptanceRadius, 32, FColor::Red);
	
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();


	if (!ensure(PlayerTank && ControlledTank)) { return; }

	MoveToActor(PlayerTank,AcceptanceRadius);
	//Aim at the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	//Fire if ready
	if (AimingComponent->GetCurrentFiringState() == EFiringState::Ready)
	{
		AimingComponent->Fire();
	}
	
	
}







