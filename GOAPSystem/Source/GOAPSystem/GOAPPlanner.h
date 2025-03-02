// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GOAPPlanner.generated.h"

/**
 * 
 */

class UGOAPAction;
class UGOAPWorldState;
class AGOAPAgent;
class UGOAPGoal;

UCLASS()
class GOAPSYSTEM_API UGOAPPlanner : public UObject
{
	GENERATED_BODY()

public:
	TArray<UGOAPAction*> CreatePlan(AGOAPAgent* Agent, UGOAPWorldState* CurrentState, UGOAPGoal* Goal);

private:
	float CalculateHeuristicCost(UGOAPWorldState* CurrentWorldState, UGOAPWorldState* DesiredState);
};
