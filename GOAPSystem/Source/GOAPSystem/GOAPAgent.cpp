// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAPAgent.h"
#include "GOAPAction.h"
#include "GOAPPlanner.h"
#include "GOAPWorldState.h"
#include "GOAPGoal.h"
#include "AIController.h"

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

    if (!AIController)
    {
        AIController = GetWorld()->SpawnActor<AAIController>(AAIController::StaticClass());
        AIController -> Possess(this);

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(
                -1,
                15.f,
                FColor::Emerald,
                FString("AI Possessed by AI Controller")
            );
        }
    }

    if (CurrentWorldState)
    {
        UGOAPGoal* Goal = FindValidGoal();

        if (ActionPlanner)
        {
            // Generate plan using A*
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(
                    -1,
                    15.f,
                    FColor::Blue,
                    FString(TEXT("Generating an Action Plan"))
                );
            }

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
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(
                    -1,
                    15.f,
                    FColor::Blue,
                    FString::Printf(TEXT("Found Valid Goal: %s"), *Goal->GetName())
                );
            }

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

