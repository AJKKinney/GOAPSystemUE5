// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAPWorldState.h"


bool UGOAPWorldState::MatchesGoal(TMap<FString, bool> Goal) const
{
    for (const auto& Condition : Goal)
    {
        if (!State.Contains(Condition.Key) || State[Condition.Key] != Condition.Value)
        {
            return false;
        }
    }
    return true;
}