// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "MyGameProject1Character.generated.h"

UCLASS(config=Game)
class AMyGameProject1Character : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AMyGameProject1Character();

	// Do initialization and update every Tick
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	// Pickup items implementations
	// Collection volume
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Power")
	class USphereComponent* CollectionSphere;

	UFUNCTION(BlueprintCallable, Category = "Power")
	void CollectBatteries();
	// Called by CollectBatteries() to use the Blueprinted PowerUp functionality
	UFUNCTION(BlueprintImplementableEvent, Category = "Power")
	void PowerUp(float BatterPower);
	virtual void PowerUp_Implementation(float BatterPower);

	//Do some maths questions
	UFUNCTION(BlueprintCallable, Category = "Answer")
	bool CollectAnswers();
    // If answer is correct, get power boots
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetCurrentPower();
	UFUNCTION(BlueprintCallable, Category = "Power")
	void UpdatePower(float PowerChange);
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetInitialPower();

	// Power & grade levels of the pawn
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Power")
	float PowerLevel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Power")
	float PowerChange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float SpeedFactor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float BaseSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
	float GradeLevel;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	// Set the initial power
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", Meta = (BlueprintProtected = "true"))
	float InitialPower;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

