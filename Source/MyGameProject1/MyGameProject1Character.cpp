// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "MyGameProject1.h"
#include "MyGameProject1Character.h"
#include "Battery.h"
#include "MathQuestions.h"
#include "MyGameProject1GameMode.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"


//////////////////////////////////////////////////////////////////////////
// AMyGameProject1Character

AMyGameProject1Character::AMyGameProject1Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	// Create the battery collection volume
	CollectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionSphere"));
	CollectionSphere->AttachTo(RootComponent);
	CollectionSphere->SetSphereRadius(200.f);

	// Set a base power level for the character
	InitialPower = 20000.f;
	PowerLevel = InitialPower;
	// Set the dependency of speed on the power level
	SpeedFactor = 1.5f;
	BaseSpeed = 10.f;
}

void AMyGameProject1Character::BeginPlay()
{
	// do something
}
void AMyGameProject1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Character Entered Tick !"));

	//CollectBatteries();
}
//////////////////////////////////////////////////////////////////////////
// Input

void AMyGameProject1Character::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Set up gameplay key bindings
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Player item interaction bindings
	InputComponent->BindAction("CollectBattery", IE_Pressed, this, &AMyGameProject1Character::CollectBatteries);
	//InputComponent->BindAction("CollectAnswer", IE_Pressed, this, &AMyGameProject1Character::CollectAnswers);

	InputComponent->BindAxis("MoveForward", this, &AMyGameProject1Character::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyGameProject1Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AMyGameProject1Character::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AMyGameProject1Character::LookUpAtRate);

	// handle touch devices
	InputComponent->BindTouch(IE_Pressed, this, &AMyGameProject1Character::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &AMyGameProject1Character::TouchStopped);
}


void AMyGameProject1Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	// jump, but only on the first touch
	if (FingerIndex == ETouchIndex::Touch1)
	{
		Jump();
	}
}

void AMyGameProject1Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		StopJumping();
	}
}

void AMyGameProject1Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMyGameProject1Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMyGameProject1Character::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMyGameProject1Character::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AMyGameProject1Character::CollectBatteries()
{
	float BatteryPower = 0.0f;

	AMyGameProject1GameMode* MyGameMode = Cast<AMyGameProject1GameMode>(UGameplayStatics::GetGameMode(this));
	if (MyGameMode->GetCurrentState() == EGamePlayState::EPlaying)
	{
		// Get all overlapping Actors and store them in a CollectedActors array
		TArray<AActor*> CollectedActors;
		CollectionSphere->GetOverlappingActors(CollectedActors);
		// Fore each Actor collected
		for (int32 iCollected = 0; iCollected < CollectedActors.Num(); ++iCollected)
		{
			// Cast the collected Actor to ABatteryPickup
			ABattery* const TestBattery = Cast<ABattery>(CollectedActors[iCollected]);
			if (TestBattery && !TestBattery->IsPendingKill() && TestBattery->bIsActive)
			{
				//Call Math question function
				bool Answer = CollectAnswers();

				if(Answer)
				{	
					// Store the Battery power
					BatteryPower += TestBattery->PowerLevel;
					TestBattery->OnPickup();
					//Deactivate the battery
					TestBattery->bIsActive = false;	
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Have another go!"));
				}
			}
	}
	if (BatteryPower > 0.f)
	{
		PowerUp(BatteryPower);
	}
  }
}

void AMyGameProject1Character::PowerUp_Implementation(float BatterPower)
{
	// Vehicle speed depending on the power level
	GetCharacterMovement()->MaxWalkSpeed = SpeedFactor*PowerLevel + BaseSpeed;

}

bool AMyGameProject1Character::CollectAnswers()
{
	AMathQuestions* Question = Cast<AMathQuestions>(GetWorld()->SpawnActor(AMathQuestions::StaticClass()));
	Question->DisplayQuestion();
	bool Answer = Question->CollectAnswer(2);
	return Answer;
}

float AMyGameProject1Character::GetInitialPower()
{
	return InitialPower;
}

float AMyGameProject1Character::GetCurrentPower()
{
	return PowerLevel;
}

void AMyGameProject1Character::UpdatePower(float PowerChange)
{
	PowerLevel = PowerLevel + PowerChange;
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed + SpeedFactor*PowerLevel;
}