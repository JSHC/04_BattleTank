// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	//How close the AI can get to the player

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnPossedTankDeath();

protected:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 6000;
};
