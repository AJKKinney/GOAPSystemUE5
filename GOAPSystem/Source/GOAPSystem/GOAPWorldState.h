// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GOAPWorldState.generated.h"

/**
 * 
 */

UCLASS()
class GOAPSYSTEM_API UGOAPWorldState : public UObject
{
	GENERATED_BODY()
	
public:
	void SetInitialWorldStateValues();

	UPROPERTY()
	TMap<FString, bool> State{};

	bool MatchesDesiredState(UGOAPWorldState* DesiredState) const;

	void SetState(FString Key, bool bStateValue);
};
