// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GOAPAction.h"
#include "AIController.h"
#include "MoveToPlayerAction.generated.h"

/**
 * 
 */
UCLASS()
class GOAPSYSTEM_API UMoveToPlayerAction : public UGOAPAction
{
	GENERATED_BODY()
	
public:
    UMoveToPlayerAction();

	virtual bool CheckProceduralPreconditions(AActor* Agent) override;

	virtual void PerformAction(AActor* Agent) override;

	UFUNCTION()
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);

private:

	AAIController* AIController;

};
