// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "KJHDebug_WorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class KJHDEBUGGER_API UKJHDebug_WorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
private:
	const class UKJHDebug_Settings *KJHDebugSetting;

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	void SpawnKJHMainActor();
};
