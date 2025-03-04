// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowPlayerGoal.h"

UFollowPlayerGoal::UFollowPlayerGoal()
{
    DesiredState = NewObject<UGOAPWorldState>();

    DesiredState->SetState("PlayerNearby", true);  // AI wants to be near the player
}

bool UFollowPlayerGoal::IsAchievable(const UGOAPWorldState* CurrentState)
{
    if (DesiredState->State.Contains("PlayerNearby") == true)
    {
        if (*CurrentState->State.Find("PlayerNearby") == false)
        {
            return true;
        }
    }

    return true;
}   
