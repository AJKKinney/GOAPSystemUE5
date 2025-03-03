// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToPlayerAction.h"
#include "GOAPAgent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GOAPWorldState.h"
#include "AIController.h"

UMoveToPlayerAction::UMoveToPlayerAction()
{
    // Preconditions (optional)
    Preconditions.Add("PlayerVisible", true); // AI must see the player

    // Effects
    Effects.Add("PlayerNearby", true); // Action results in AI being near player

    ActionDefaultCost = 1.0f; // Cost of movement
}

bool UMoveToPlayerAction::CheckProceduralPreconditions(AActor* Agent)
{
    return true;//Agent->GetWorld()->GetTimeSeconds() > 0;
}

void UMoveToPlayerAction::PerformAction(AActor* Agent)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1,
            15.f,
            FColor::Blue,
            FString(TEXT("Moving to Player"))
        );
    }

    ACharacter* Character = Cast<ACharacter>(Agent);
    if (!Character) return;

    AActor* Player = GetWorld()->GetFirstPlayerController();
    if (!Player) return;

    // Get the AIController
    AAIController* AIController = Cast<AAIController>(Character->GetController());
    if (!AIController) return;

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1,
            15.f,
            FColor::Blue,
            FString(TEXT("Has Necessary Components"))
        );
    }

    // Move the AI character to the player's location
    AIController->MoveToActor(Player);

    /*
    // Check if close enough
    if (FVector::Dist(Character->GetActorLocation(), Player->GetActorLocation()) < 200.0f)
    {
        // Update world state to reflect that player is nearby
        AGOAPAgent* GOAPAgent = Cast<AGOAPAgent>(Agent);

        // Update Current World State
        if (GOAPAgent && GOAPAgent->CurrentWorldState)
        {
            GOAPAgent->CurrentWorldState->State.Add("PlayerNearby", true);
        }
    }
    */
}
