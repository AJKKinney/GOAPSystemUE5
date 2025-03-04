// Fill out your copyright notice in the Description page of Project Settings.


#include "IdleGoal.h"

UIdleGoal::UIdleGoal()
{
	DesiredState = NewObject<UGOAPWorldState>();
}

bool UIdleGoal::IsAchievable(const UGOAPWorldState* CurrentState)
{
	return true;
}
