// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BattleTank.h"
#include "CoreMinimal.h"
#include "TankPlayerController.generated.h"

/**
 *  Responsible for helping the player aim.
 */
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	//Start the tank barrel rotation toward the crosshair location

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	void AimTowardsCrosshair();

	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.3333;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;

	bool GetSightRayHitLocation(FVector &HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const;

	virtual void SetPawn(APawn *InPawn) override;

	UFUNCTION()
	void OnPlayerTankDeath();
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent *AimingCompRef);
};
