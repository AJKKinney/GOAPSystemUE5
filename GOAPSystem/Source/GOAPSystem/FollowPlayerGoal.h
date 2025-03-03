// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAPGoal.h"
#include "FollowPlayerGoal.generated.h"

/**
 * 
 */
UCLASS()
class GOAPSYSTEM_API UFollowPlayerGoal : public UGOAPGoal
{
	GENERATED_BODY()

public:
    UFollowPlayerGoal();

    virtual bool IsAchievable(const UGOAPWorldState* CurrentState) override;
};
