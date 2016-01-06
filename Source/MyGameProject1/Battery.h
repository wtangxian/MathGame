// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickupItem.h"
#include "Battery.generated.h"

/**
 * 
 */
UCLASS()
class ABattery : public APickupItem
{
	GENERATED_BODY()

public:
	ABattery();
	// Power level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
	float PowerLevel;
	// Override the OnPickup_Implementation base class
	virtual void OnPickup_Implementation() override;
	//Override the OnCollision base class
	virtual void OnCollision_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) override;
	
};
