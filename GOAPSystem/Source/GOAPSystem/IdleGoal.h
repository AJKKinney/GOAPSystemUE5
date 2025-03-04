// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAPGoal.h"
#include "IdleGoal.generated.h"

/**
 * 
 */
UCLASS()
class GOAPSYSTEM_API UIdleGoal : public UGOAPGoal
{
	GENERATED_BODY()
	
public:
	UIdleGoal();

	// Virtual function to check if the goal is valid to pursue
	virtual bool IsAchievable(const UGOAPWorldState* CurrentState) override;
};
