// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GOAPAction.generated.h"

/**
 * 
 */
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
    float Cost = 1.0f;

    UFUNCTION(BlueprintCallable, Category = "GOAP")
    virtual bool CheckProceduralPreconditions(AActor* Agent) PURE_VIRTUAL(UGoapAction::CheckProceduralPreconditions, return false;);
    UFUNCTION(BlueprintCallable, Category = "GOAP")
    virtual void PerformAction(AActor* Agent) PURE_VIRTUAL(UGoapAction::PerformAction, );;
};
