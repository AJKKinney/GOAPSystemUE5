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

UCLASS()
class GOAPSYSTEM_API UGOAPPlanner : public UObject
{
	GENERATED_BODY()

public:
	TArray<UGOAPAction*> Plan(AGOAPAgent* Agent, UGOAPWorldState* CurrentState, TMap<FString, bool> Goal);

private:
	float HeuristicCost(UGOAPWorldState* State, TMap<FString, bool> Goal);
};
