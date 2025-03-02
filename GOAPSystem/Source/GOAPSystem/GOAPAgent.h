// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GOAPAgent.generated.h"

class UGOAPPlanner;
class UGOAPAction;
class UGOAPWorldState;

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function to get the available actions
	const TArray<UGOAPAction*>& GetAvailableActions() const { return AvailableActions; }

private:
	UPROPERTY()
	UGOAPPlanner* Planner;

	UPROPERTY()
	UGOAPWorldState* CurrentWorldState;

	TArray<UGOAPAction*> CurrentPlan;
	int32 CurrentActionIndex;


	void ExecuteNextAction();

};
