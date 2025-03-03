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
    TMap<UGOAPAction*, float> BaseActionCost;
    TMap<UGOAPAction*, UGOAPAction*> ComingFromAction;

    for (UGOAPAction* Action : Agent->GetAvailableActions())
    {
        if (Action->CheckProceduralPreconditions(Agent))
        {
            OpenSet.Add(Action);
            BaseActionCost.Add(Action, Action->ActionDefaultCost);
            
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(
                    -1,
                    15.f,
                    FColor::Blue,
                    FString::Printf(TEXT("Found Available Action: %s | Cost: %.2f"), *Action->GetName(), Action->ActionDefaultCost)
                );
            }
        }
    }

    while (OpenSet.Num() > 0)
    {
        if (GEngine)
        {
            for (UGOAPAction* Action : OpenSet)
            {
                float HeuristicCost = CalculateHeuristicCost(CurrentState, Goal->DesiredState);
                float TotalCost = BaseActionCost[Action] + HeuristicCost;

                GEngine->AddOnScreenDebugMessage(
                    -1,
                    15.f,
                    FColor::Cyan,
                    FString::Printf(TEXT("Action: %s | Base Cost: %.2f | Heuristic: %.2f | Total: %.2f"), *Action->GetName(), BaseActionCost[Action], HeuristicCost, TotalCost)
                );
            }
        }

        OpenSet.Sort([&](const UGOAPAction& A, const UGOAPAction& B)
        {
            return (BaseActionCost[&A] + CalculateHeuristicCost(CurrentState, Goal->DesiredState)) < (BaseActionCost[&B] + CalculateHeuristicCost(CurrentState, Goal->DesiredState));
        });

        UGOAPAction* CurrentAction = OpenSet[0];
        OpenSet.RemoveAt(0);

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(
                -1, 
                15.f, 
                FColor::Yellow,
                FString::Printf(TEXT("Selected Action: %s"), *CurrentAction->GetName())
            );
        }

        // Clone state for this action before applying effects
        UGOAPWorldState* ActionState = DuplicateObject(CurrentState, nullptr);

        // Apply the action effects
        for (auto& Effect : CurrentAction->Effects)
        {
            ActionState->State.Add(Effect.Key, Effect.Value);
        }

        /*
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(
                -1, 
                15.f, 
                FColor::Red,
                FString::Printf(TEXT("State after %s: %s"), *CurrentAction->GetName(), *ActionState->ToString())
            );
        }
        */

        // If goal is achieved, construct the final plan
        if (ActionState->MatchesDesiredState(Goal->DesiredState))
        {
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(
                    -1, 
                    15.f, 
                    FColor::Magenta,
                    FString::Printf(TEXT("Goal Achieved! Constructing Plan..."))
                );
            }


            while (ComingFromAction.Contains(CurrentAction))
            {
                if (GEngine)
                {
                    GEngine->AddOnScreenDebugMessage(
                        -1,
                        15.f,
                        FColor::Blue,
                        FString::Printf(TEXT("Adding Action To Plan: %s"), *CurrentAction->GetName())
                    );
                }
                FinalPlan.Insert(CurrentAction, 0);
                CurrentAction = ComingFromAction[CurrentAction];
            }

            FinalPlan.Insert(CurrentAction, 0);  // In case only one action completes the goal


            return FinalPlan;
        }

        // Add neighbors (next actions)
        for (UGOAPAction* Neighbor : Agent->GetAvailableActions())
        {
            if (!Neighbor->CheckProceduralPreconditions(Agent))
                continue;

            float TentativeGScore = BaseActionCost[CurrentAction] + Neighbor->ActionDefaultCost;

            if (!BaseActionCost.Contains(Neighbor) || TentativeGScore < BaseActionCost[Neighbor])
            {
                ComingFromAction.Add(Neighbor, CurrentAction);
                BaseActionCost.Add(Neighbor, TentativeGScore);
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