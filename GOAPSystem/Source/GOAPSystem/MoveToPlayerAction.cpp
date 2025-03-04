// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToPlayerAction.h"
#include "GOAPAgent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GOAPWorldState.h"
#include "Navigation/PathFollowingComponent.h"


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
    ACharacter* Character = Cast<ACharacter>(Agent);
    if (!Character) return false;

    AActor* Player = GetWorld()->GetFirstPlayerController();
    if (!Player) return false;

    AGOAPAgent* GOAPAgent = Cast<AGOAPAgent>(Agent);
    if (!GOAPAgent) return false;

    if (FVector::Dist(Character->GetActorLocation(), Player->GetActorLocation()) < 200.0f)
    {
        // Update world state to reflect that player is nearby

        if (GOAPAgent && GOAPAgent->CurrentWorldState)
        {
            GOAPAgent->CurrentWorldState->SetState("PlayerNearby", true);
        }
    }

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
    AIController = Cast<AAIController>(Character->GetController());
    if (!AIController) return;

    AGOAPAgent* GOAPAgent = Cast<AGOAPAgent>(Agent);
    if (!GOAPAgent) return;


        FAIMoveRequest MoveRequest;
        MoveRequest.SetGoalActor(Player);
        MoveRequest.SetUsePathfinding(true);
        MoveRequest.SetAcceptanceRadius(50.0f); // Stops AI when close

        FNavPathSharedPtr NavPath;

        AIController->ReceiveMoveCompleted.AddDynamic(this, &ThisClass::OnMoveCompleted);
        AIController->MoveTo(MoveRequest, &NavPath);

}

void UMoveToPlayerAction::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1,
            15.f,
            FColor::Blue,
            FString::Printf(TEXT("Completed Move"))
        );
    }

    bool bSuccess = (Result == EPathFollowingResult::Success);

    OnActionCompleted.Broadcast(bSuccess);

    AIController->ReceiveMoveCompleted.RemoveDynamic(this, &ThisClass::OnMoveCompleted);
}