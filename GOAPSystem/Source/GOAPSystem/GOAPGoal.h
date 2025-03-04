// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GOAPWorldState.h"
#include "GOAPGoal.generated.h"

/**
 * 
 */
UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGoalEnded, bool, bWasSuccessful);


UCLASS(Abstract, Blueprintable)
class GOAPSYSTEM_API UGOAPGoal : public UObject
{
	GENERATED_BODY()
	
public:
    UGOAPGoal();

    // The world state the agent wants to achieve (could be a TMap or a more complex structure)
    UPROPERTY()
    UGOAPWorldState* DesiredState{};

    // Virtual function to check if the goal is valid to pursue
    UFUNCTION(BlueprintCallable, Category = "GOAP")
    virtual bool IsAchievable(const UGOAPWorldState* CurrentState) PURE_VIRTUAL(UGOAPGoal::IsAchievable, return false;);

    FOnGoalEnded OnGoalEnded;
};
