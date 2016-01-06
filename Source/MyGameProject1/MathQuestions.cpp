// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameProject1.h"
#include "MathQuestions.h"
#include "Engine.h"


// Sets default values
AMathQuestions::AMathQuestions()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMathQuestions::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMathQuestions::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AMathQuestions::DisplayQuestion()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("1 + 1 = ?"));
}

bool AMathQuestions::CollectAnswer(int32  Answer)
{
	if (Answer == 2)
	{
		CurrentState = EAnswerState::ECorrectAnswer;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Congratulations!"));

		return true;
	}
	else
	{
		CurrentState = EAnswerState::EWrongAnswer;
		return false;
	}

}

