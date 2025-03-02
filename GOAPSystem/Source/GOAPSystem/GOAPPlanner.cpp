// Fill out your copyright notice in the Description page of Project Settings.

#include "GOAPPlanner.h"
#include "GOAPAgent.h"
#include "GOAPAction.h"
#include "GOAPWorldState.h"
#include "GOAPGoal.h"

TArray<UGOAPAction*> UGOAPPlanner::CreatePlan(AGOAPAgent* Agent, UGOAPWorldState* CurrentState, UGOAPGoal* Goal)
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
            GScore.Add(Action, Action->ActionDefaultCost);
        }
    }

    while (OpenSet.Num() > 0)
    {
        OpenSet.Sort([&](const UGOAPAction& A, const UGOAPAction& B)
            {
                return (GScore[&A] + CalculateHeuristicCost(CurrentState, Goal->DesiredState)) < (GScore[&B] + CalculateHeuristicCost(CurrentState, Goal->DesiredState));
            });

        UGOAPAction* CurrentAction = OpenSet[0];
        OpenSet.RemoveAt(0);

        // Apply the action effects
        for (auto& Effect : CurrentAction->Effects)
        {
            CurrentState->State.Add(Effect.Key, Effect.Value);
        }

        // If goal is achieved, construct the final plan
        if (CurrentState->MatchesDesiredState(Goal->DesiredState))
        {
            while (CameFrom.Contains(CurrentAction))
            {
                FinalPlan.Insert(CurrentAction, 0);
                CurrentAction = CameFrom[CurrentAction];
            }
            return FinalPlan;
        }

        // Add neighbors (next actions)
        for (UGOAPAction* Neighbor : Agent->GetAvailableActions())
        {
            if (!Neighbor->CheckProceduralPreconditions(Agent))
                continue;

            float TentativeGScore = GScore[CurrentAction] + Neighbor->ActionDefaultCost;

            if (!GScore.Contains(Neighbor) || TentativeGScore < GScore[Neighbor])
            {
                CameFrom.Add(Neighbor, CurrentAction);
                GScore.Add(Neighbor, TentativeGScore);
                OpenSet.Add(Neighbor);
            }
        }
    }

    return FinalPlan;  // Return an empty plan if no solution found
}

//Returns a cost which is equal to the number of variables which would need to be changed in order to reach the given world state
float UGOAPPlanner::CalculateHeuristicCost(UGOAPWorldState* CurrentWorldState, UGOAPWorldState* DesiredState)
{
    float Cost = 0.0f;
    
    for (const auto& Condition : DesiredState->State)
    {
        if (!CurrentWorldState->State.Contains(Condition.Key) || CurrentWorldState->State[Condition.Key] != Condition.Value)
        {
            Cost += 1.0f;  // Simple heuristic: count mismatched conditions
        }
    }
    
    return Cost;
}