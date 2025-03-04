// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAPWorldState.h"




void UGOAPWorldState::SetInitialWorldStateValues()
{

    if (State.Contains("PlayernNearby") == false)
    {
        State.Add("PlayerNearby", false);  // AI wants to be near the player
    }
}

bool UGOAPWorldState::MatchesDesiredState(UGOAPWorldState* DesiredState) const
{
    for (const auto& Condition : DesiredState->State)
    {
        if (!State.Contains(Condition.Key) || State[Condition.Key] != Condition.Value)
        {
            return false;
        }
    }
    return true;
}

void UGOAPWorldState::SetState(FString Key, bool bStateValue)
{
    if (State.Contains(Key) == true)
    {
        State[Key] = bStateValue;
    }
    else
    {
        State.Add(Key, bStateValue);
    }
}
