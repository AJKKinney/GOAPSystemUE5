// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAPWorldState.h"


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