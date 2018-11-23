// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"
#include "BattleTank.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	//Make sure relativespeed isn't too high/low
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	//Move the barrel the right amount per frame
	//Given a max speed and max elevation
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	
	auto ClampedNewElevation = FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(ClampedNewElevation, 0, 0));
}




