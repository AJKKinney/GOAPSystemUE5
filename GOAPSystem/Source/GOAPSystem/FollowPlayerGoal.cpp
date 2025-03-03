// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowPlayerGoal.h"

UFollowPlayerGoal::UFollowPlayerGoal()
{
    DesiredState = NewObject<UGOAPWorldState>();
    DesiredState->State.Add("PlayerNearby", true);  // AI wants to be near the player
}

bool UFollowPlayerGoal::IsAchievable(const UGOAPWorldState* CurrentState)
{
    return true; // Always achievable
}
