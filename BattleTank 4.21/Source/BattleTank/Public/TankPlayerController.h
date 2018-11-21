// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BattleTank.h"
#include "CoreMinimal.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	//Start the tank barrel rotation toward the crosshair location
	ATank* GetControlledTank() const;
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	void AimTowardsCrosshair();
	UPROPERTY(EditAnywhere)
	float CrosshairPosX = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrosshairPosY = 0.33333f;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 100000.f;
public:
	bool GetSightRayHitLocation(FVector &HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const;
	
};
