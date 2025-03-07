// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GOAPAction.generated.h"

/**
 * 
 */
UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionCompleted, bool, bWasSuccessful);

UCLASS(Abstract, Blueprintable)
class GOAPSYSTEM_API UGOAPAction : public UObject
{
	GENERATED_BODY()

public:
    UGOAPAction();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FString, bool> Preconditions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FString, bool> Effects;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ActionDefaultCost = 1.0f;

    // Check if the action can be performed (based on preconditions)
    UFUNCTION(BlueprintCallable, Category = "GOAP")
    virtual bool CheckProceduralPreconditions(AActor* Agent) PURE_VIRTUAL(UGoapAction::CheckProceduralPreconditions, return false;);

    // Each action needs a PerformAction function that defines its execution logic
    UFUNCTION(BlueprintCallable, Category = "GOAP")
    virtual void PerformAction(AActor* Agent) PURE_VIRTUAL(UGoapAction::PerformAction, );;

    FOnActionCompleted OnActionCompleted;
};
