// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameProject1.h"
#include "Trigger.h"
#include "Engine.h"
#include "MyGameProject1Character.h"


// Sets default values
ATrigger::ATrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->bGenerateOverlapEvents = true;
	Box->SetRelativeScale3D(FVector(2.f, 2.f, 5.f));
    RootComponent = Box;
	Box->OnComponentBeginOverlap.AddDynamic(this, &ATrigger::TriggerEnter);
	Box->OnComponentEndOverlap.AddDynamic(this, &ATrigger::TriggerExit);
	
}

// Called when the game starts or when spawned
void ATrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrigger::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ATrigger::TriggerEnter(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	//OtherActor->PlaySoundOnActor(MySound);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Trigger Entered!"));
    Destroy();
	
	/*AMyProjectCharacter* MyCharacter = Cast<AMyProjectCharacter>(GetWorld()->SpawnActor(AMyProjectCharacter::StaticClass()));
	MyCharacter->TriggerEnter();*/
    
}

void ATrigger::TriggerExit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Trigger Exit!"));
}

