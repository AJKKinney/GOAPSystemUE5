// Fill out your copyright notice in the Description page of Project Settings.

#include "GOAPAgent.h"
#include "GOAPAction.h"
#include "GOAPWorldState.h"
#include "GOAPPlanner.h"


TArray<UGOAPAction*> UGOAPPlanner::Plan(AGOAPAgent* Agent, UGOAPWorldState* CurrentState, TMap<FString, bool> Goal)
{
    TArray<UGOAPAction*> OpenSet;
    TArray<UGOAPAction*> FinalPlan;
    TMap<UGOAPAction*, float> GScore;
    TMap<UGOAPAction*, UGOAPAction*> CameFrom;

    for (UGOAPAction* Action : Agent->GetAvailableActions())
    {
        if (Action->CheckProceduralPreconditions(Agent))
        {
            OpenSet.Add(Action);
            GScore.Add(Action, Action->Cost);
        }
    }

    while (OpenSet.Num() > 0)
    {
        OpenSet.Sort([&](const UGOAPAction& A, const UGOAPAction& B)
            {
                return (GScore[&A] + HeuristicCost(CurrentState, Goal)) < (GScore[&B] + HeuristicCost(CurrentState, Goal));
            });

        UGOAPAction* Current = OpenSet[0];
        OpenSet.RemoveAt(0);

        // Apply the action effects
        for (auto& Effect : Current->Effects)
        {
            CurrentState->State.Add(Effect.Key, Effect.Value);
        }

        // If goal is achieved, construct the final plan
        if (CurrentState->MatchesGoal(Goal))
        {
            while (CameFrom.Contains(Current))
            {
                FinalPlan.Insert(Current, 0);
                Current = CameFrom[Current];
            }
            return FinalPlan;
        }

        // Add neighbors (next actions)
        for (UGOAPAction* Neighbor : Agent->GetAvailableActions())
        {
            if (!Neighbor->CheckProceduralPreconditions(Agent))
                continue;

            float TentativeGScore = GScore[Current] + Neighbor->Cost;

            if (!GScore.Contains(Neighbor) || TentativeGScore < GScore[Neighbor])
            {
                CameFrom.Add(Neighbor, Current);
                GScore.Add(Neighbor, TentativeGScore);
                OpenSet.Add(Neighbor);
            }
        }
    }

    return FinalPlan;  // Return an empty plan if no solution found
}

//Returns a cost which is equal to the number of variables which would need to be changed in order to reach the given world state
float UGOAPPlanner::HeuristicCost(UGOAPWorldState* State, TMap<FString, bool> Goal)
{
    float Cost = 0.0f;

    for (const auto& Condition : Goal)
    {
        if (!State->State.Contains(Condition.Key) || State->State[Condition.Key] != Condition.Value)
        {
            Cost += 1.0f;  // Simple heuristic: count mismatched conditions
        }
    }
    return Cost;
}