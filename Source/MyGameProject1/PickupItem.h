// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PickupItem.generated.h"

UCLASS()
class APickupItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupItem();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	bool bIsActive;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pickup")
	USphereComponent* BaseCollisionComponenet;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pickup")
	UStaticMeshComponent* PickupMesh;

	// Function to call when Pickup is collected
	UFUNCTION(BlueprintNativeEvent)
	void OnPickup();
	virtual void OnPickup_Implementation();
	UFUNCTION(BlueprintNativeEvent)
	void OnCollision(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	virtual void OnCollision_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
};
