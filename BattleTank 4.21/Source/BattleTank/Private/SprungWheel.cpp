// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Phsyics Constraint"));
	SetRootComponent(PhysicsConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(PhysicsConstraint);

	AxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle Constraint"));
	AxleConstraint->SetupAttachment(Axle);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);
	
}



// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
	SetupConstraint();

	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		TotalForceMagnitudeThisFrame = 0;
	}

}

void ASprungWheel::SetupConstraint()
{
	if (GetAttachParentActor()) {
		UE_LOG(LogTemp, Warning, TEXT("Not null, %s"), *GetAttachParentActor()->GetName())
			if (!GetAttachParentActor()) { return; }
		UPrimitiveComponent *BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		if (!BodyRoot) { return; }
		PhysicsConstraint->SetConstrainedComponents(BodyRoot, FName(NAME_None), Axle, FName(NAME_None));
		AxleConstraint->SetConstrainedComponents(Axle, FName(NAME_None), Wheel, FName(NAME_None));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Null"))
}

void ASprungWheel::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	ApplyForce();
}


void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	TotalForceMagnitudeThisFrame += ForceMagnitude;
}

void ASprungWheel::ApplyForce()
{
	Wheel->AddForce(Axle->GetForwardVector() * TotalForceMagnitudeThisFrame);
}
