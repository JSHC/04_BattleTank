// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/Classes/Components/PrimitiveComponent.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
	this->SetNotifyRigidBodyCollision(true);
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);

	
}

void UTankTrack::ApplysidewaysForce()
{
	//Calculate slippage speed
	auto SlipSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	//Work out required acceleration this frame to correct
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlipSpeed / DeltaTime * GetRightVector();
	//Calculate and apply sideways force
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2;
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplysidewaysForce();
	CurrentThrottle = 0;
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}