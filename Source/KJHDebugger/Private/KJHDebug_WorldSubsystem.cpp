// Fill out your copyright notice in the Description page of Project Settings.


#include "KJHDebug_WorldSubsystem.h"
#include "KJHDebug_Settings.h"
#include "KJHDebug_MainActor.h"
#include "Engine/World.h"

void UKJHDebug_WorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	KJHDebugSetting = GetDefault<UKJHDebug_Settings>();
	SpawnKJHMainActor();
}

void UKJHDebug_WorldSubsystem::SpawnKJHMainActor()
{
	if (!((GetWorld()->WorldType) == EWorldType::Type::Editor))
	{
		if (KJHDebugSetting->bIsActive)
		{
			GetWorld()->SpawnActor<AKJHDebug_MainActor>(AKJHDebug_MainActor::StaticClass());
		}
	}
}
