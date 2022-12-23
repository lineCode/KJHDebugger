// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KJHDebug_Subsystem.h"
#include "KJHDebug_OptionListItemData.generated.h"

/**
 * 
 */
UCLASS()
class KJHDEBUGGER_API UKJHDebug_OptionListItemData : public UObject
{
	GENERATED_BODY()

public:
	UKJHDebug_OptionListItemData();

	FOptionListItemData OptionListItemData;
	
};

