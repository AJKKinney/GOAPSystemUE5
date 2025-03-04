// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GOAPAgent.generated.h"


class UGOAPPlanner;
class UGOAPAction;
class UGOAPWorldState;
class UGOAPGoal;
class AAIController;

UCLASS()
class GOAPSYSTEM_API AGOAPAgent : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGOAPAgent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// List of available actions that the agent can perform
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GOAP")
	TArray<UGOAPAction*> AvailableActions;

	/// <summary>
	/// Goals are listed in order of priority with the goal at index of 0 being the highest priority
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GOAP")
	TArray<UGOAPGoal*> Goals;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function to get the available actions
	const TArray<UGOAPAction*>& GetAvailableActions() const { return AvailableActions; }

	UPROPERTY()
	AAIController* AIController;

	UPROPERTY()
	UGOAPWorldState* CurrentWorldState;

private:
	UPROPERTY()
	UGOAPPlanner* ActionPlanner;

	TArray<UGOAPAction*> CurrentActionPlan;
	int32 CurrentActionIndex;

	bool bAwaitingNextAction = false;
	bool bPreviousActionWasSuccessful = false;

	UGOAPGoal* FindValidGoal();
	
	void StartNewGoal();

	void ExecuteNextAction();

	UFUNCTION()
	void HandleActionCompleted(bool bWasSuccessful);
};
