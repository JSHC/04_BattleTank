// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "SprungWheel.generated.h"


UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	void AddDrivingForce(float ForceMagnitude);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetupConstraint();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent *PhysicsConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent *AxleConstraint = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent *Axle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	 USphereComponent *Wheel = nullptr;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void ApplyForce();

	float TotalForceMagnitudeThisFrame = 0;
};
