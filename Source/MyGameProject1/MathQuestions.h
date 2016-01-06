// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MathQuestions.generated.h"


// enum to store the current state of answers
enum class EAnswerState : short
{
	ECorrectAnswer,
	EWrongAnswer,
	EUnknownAnswer
};


UCLASS()
class AMathQuestions : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMathQuestions();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
	void DisplayQuestion();
	UFUNCTION()
	bool CollectAnswer(int32 Answer);

private:
	// Current answer state
	EAnswerState CurrentState;
	
};
