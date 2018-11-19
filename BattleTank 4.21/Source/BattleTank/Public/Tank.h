// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/ActorComponent.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class ATank;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 100000.f; //TODO find 
public:	
	void AimAt(FVector HitLocation);	

	UFUNCTION(BlueprintCallable)
	void Fire();
	UFUNCTION(BlueprintCallable)
	void SetBarrelReference(UTankBarrel *BarrelToSet);
	UFUNCTION(BlueprintCallable)
	void SetTurretReference(UTankTurret *TurretToSet);

	
};
