// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "KJHDebug_Subsystem.h"
#include "KJHDebug_DebugListItemData.generated.h"


UCLASS()
class KJHDEBUGGER_API UKJHDebug_DebugListItemData : public UObject
{
	GENERATED_BODY()
	
public:
	UKJHDebug_DebugListItemData();

	FDebugListItemData DebugListItemData;
};
