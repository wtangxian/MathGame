// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameProject1.h"
#include "PickupItem.h"


// Sets default values
APickupItem::APickupItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// The Pickup is valid when it is created
	bIsActive = true;

	// Create the root SphereComponenet to handle the Pickup's collision
	BaseCollisionComponenet = CreateDefaultSubobject<USphereComponent>(TEXT("BaseSphereComponenet"));
	// Set the SphereCompnenet as the root component
	RootComponent = BaseCollisionComponenet;
	
	// Create the static mesh component as the visitable pickup 
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetSimulatePhysics(true);
	PickupMesh->AttachTo(RootComponent);

	BaseCollisionComponenet->OnComponentBeginOverlap.AddDynamic(this, &APickupItem::OnCollision);

}

void APickupItem::OnCollision_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
   // detailed implantation is in derived class
}


// Called when the game starts or when spawned
void APickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupItem::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


void APickupItem::OnPickup_Implementation()
{
	//Implemented in derived class for different types of Pickup
}

