// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameProject1.h"
#include "MathQuestions.h"
#include "Battery.h"
#include "Engine.h"


ABattery::ABattery()
{

	// Base power level of the battery
	PowerLevel = 50.0f;

}

void ABattery::OnPickup_Implementation()
{
	Super::OnPickup_Implementation();
	// Destroy the battery
	Destroy();
   
}

void ABattery::OnCollision_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Press E Key"));
		/*AMathQuestions* Question = Cast<AMathQuestions>(GetWorld()->SpawnActor(AMathQuestions::StaticClass()));
		Question->DisplayQuestion();*/

	}
}




