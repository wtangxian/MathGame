// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "MyGameProject1GameMode.generated.h"

// enum to store the current state of gameplay
enum class EGamePlayState : short
{
	EPlaying,
	EGameOver,
	EUnknown
};

UCLASS()
class AMyGameProject1GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AMyGameProject1GameMode();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	void SetCurrentState(EGamePlayState NewState);

	//Return power needed to win  for the HUD
	UFUNCTION(BlueprintCallable, Category = "Power")
	float GetPowerToWin() const;
	FORCEINLINE EGamePlayState GetCurrentState() const { return CurrentState; }

	UFUNCTION(BlueprintCallable, Category = "Game Menu")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);


protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power")
	float DecayRate;
	// Power needed to win the game
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power")
	float PowerToWin;

	// The Widget class we will use as our menu when game starts
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Menu")
	TSubclassOf<UUserWidget> StartWidgetClass;
	// The Widget instance that we are using as our menu
	UPROPERTY()
	UUserWidget* MyWidget;

	// The Widget class to use for HUD screen
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power")
	TSubclassOf<UUserWidget> HUDWidgetClass;
	UPROPERTY()
	UUserWidget* CurrentWidget;


private:

	EGamePlayState CurrentState;
	
	void HandleNewState(EGamePlayState NewState);
};



