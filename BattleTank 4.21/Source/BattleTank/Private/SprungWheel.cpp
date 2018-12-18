// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Phsyics Constraint"));
	SetRootComponent(PhysicsConstraint);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(PhysicsConstraint);
	
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	SetupConstraint();

	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASprungWheel::SetupConstraint()
{
	if (GetAttachParentActor()) {
		UE_LOG(LogTemp, Warning, TEXT("Not null, %s"), *GetAttachParentActor()->GetName())
			if (!GetAttachParentActor()) { return; }
		UPrimitiveComponent *BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		if (!BodyRoot) { return; }
		PhysicsConstraint->SetConstrainedComponents(BodyRoot, FName(NAME_None), Cast<UPrimitiveComponent>(Wheel), FName(NAME_None));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Null"))
}
