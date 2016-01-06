// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "MyGameProject1.h"
#include "MyGameProject1GameMode.h"
#include "MyGameProject1Character.h"
#include "MyGameProject1Character.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"


AMyGameProject1GameMode::AMyGameProject1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	
	// Base decay rate
	DecayRate = 1.f;
	PowerToWin = 1000.0f;

}

void AMyGameProject1GameMode::BeginPlay()
{
	Super::BeginPlay();

	ChangeMenuWidget(StartWidgetClass);

	// Set the gameplay
	SetCurrentState(EGamePlayState::EPlaying);
	// Do initialization 
	// Set the score to beat
	AMyGameProject1Character* MyCharacter = Cast<AMyGameProject1Character>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		PowerToWin = (MyCharacter->GetCurrentPower())*1.25f;
	}

	//if (HUDWidgetClass != nullptr)
	//{
	//	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
	//	if (CurrentWidget !=nullptr)
	//	{
	//		CurrentWidget->AddToViewport();
	//	}
	//}
	
}

void AMyGameProject1GameMode::Tick(float DelatTime)
{
	Super::Tick(DelatTime);

	AMyGameProject1Character* MyCharacter = Cast<AMyGameProject1Character>(UGameplayStatics::GetPlayerPawn(this, 0));
	//If the character still has power
	if (MyCharacter->PowerLevel > 0.05)
	{
		//decrease the character's power
		MyCharacter->PowerLevel = FMath::FInterpTo(MyCharacter->PowerLevel, 0.f, DelatTime, DecayRate);
	}
	else
	{
		SetCurrentState(EGamePlayState::EGameOver);
	}
}


void AMyGameProject1GameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{

	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
void AMyGameProject1GameMode::SetCurrentState(EGamePlayState NewState)
{
	CurrentState = NewState;

	HandleNewState(NewState);
}

void AMyGameProject1GameMode::HandleNewState(EGamePlayState NewState)
{
	switch (NewState)
	{
		case  EGamePlayState::EPlaying:
		{

		}
		break;
		case EGamePlayState::EGameOver:
		{
		    
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		    PlayerController->SetCinematicMode(true, true, true);
		}
		break;
		case EGamePlayState::EUnknown:
		default:
			//do nothing
			break;

	}
}

float AMyGameProject1GameMode::GetPowerToWin() const
{
	return PowerToWin;
}