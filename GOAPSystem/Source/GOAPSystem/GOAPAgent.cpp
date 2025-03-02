// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAPAgent.h"
#include "GOAPAction.h"
#include "GOAPPlanner.h"
#include "GOAPWorldState.h"

// Sets default values
AGOAPAgent::AGOAPAgent()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Planner = CreateDefaultSubobject<UGOAPPlanner>(TEXT("GOAP Planner"));
	CurrentWorldState = CreateDefaultSubobject<UGOAPWorldState>(TEXT("GOAP World State"));

}

// Called when the game starts or when spawned
void AGOAPAgent::BeginPlay()
{
	Super::BeginPlay();

    // Define AI's goal
    TMap<FString, bool> Goal;
    Goal.Add("HasWeapon", true);

    if (CurrentWorldState)
    {
        // Define world state
        CurrentWorldState->State.Add("HasWeapon", false);
        if (Planner)
        {
            // Generate plan using A*
            CurrentPlan = Planner->Plan(this, CurrentWorldState, Goal);
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

void AGOAPAgent::ExecuteNextAction()
{
    if (CurrentPlan.IsValidIndex(CurrentActionIndex))
    {
        CurrentPlan[CurrentActionIndex]->PerformAction(this);
        CurrentActionIndex++;
    }
}

