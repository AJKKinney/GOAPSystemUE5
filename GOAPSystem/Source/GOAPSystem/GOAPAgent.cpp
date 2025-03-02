// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAPAgent.h"
#include "GOAPAction.h"
#include "GOAPPlanner.h"
#include "GOAPWorldState.h"
#include "GOAPGoal.h"

// Sets default values
AGOAPAgent::AGOAPAgent()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActionPlanner = CreateDefaultSubobject<UGOAPPlanner>(TEXT("GOAP Planner"));
	CurrentWorldState = CreateDefaultSubobject<UGOAPWorldState>(TEXT("GOAP World State"));
}

// Called when the game starts or when spawned
void AGOAPAgent::BeginPlay()
{
	Super::BeginPlay();

    if (CurrentWorldState)
    {
        UGOAPGoal* Goal = FindValidGoal();

        if (ActionPlanner)
        {
            // Generate plan using A*
            CurrentActionPlan = ActionPlanner->CreatePlan(this, CurrentWorldState, Goal);
            CurrentActionIndex = 0;
        }
    }

    ExecuteNextAction();
}

// Called every frame
void AGOAPAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UGOAPGoal* AGOAPAgent::FindValidGoal()
{
    for (UGOAPGoal* Goal : Goals)
    {
        if (Goal->IsAchievable(CurrentWorldState))
        {
            return Goal;
        }
    }
    return nullptr;
}

void AGOAPAgent::ExecuteNextAction()
{
    if (CurrentActionPlan.IsValidIndex(CurrentActionIndex))
    {
        CurrentActionPlan[CurrentActionIndex]->PerformAction(this);
        CurrentActionIndex++;
    }
}

