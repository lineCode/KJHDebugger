// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "KJHDebug_Settings.generated.h"


UCLASS(config = KJHDebugg, defaultconfig)
class KJHDEBUGGER_API UKJHDebug_Settings : public UObject
{
	GENERATED_BODY()
	
public:
	UKJHDebug_Settings(const FObjectInitializer& ObjectInitializer);


public:
	UPROPERTY(Config, EditAnywhere, Category = KJHDebugger)
	bool bIsActive;

	/*
	Unreal Engine Code add 10 to zorder value when you execute funcion 'AddToViewport(int32 zorder)'
	to avoid displaying below any built-in controls, like the virtual joysticks on mobile builds.
	Recommand to set ZOrder value less than 2,147,483,647 - 10
	*/
	UPROPERTY(Config, EditAnywhere, Category = KJHDebugger)
	int32 ZOrder;

	UPROPERTY(Config, EditAnywhere, Category = DebugWidget_Log)
	int32 MaxSaveLog;
	UPROPERTY(Config, EditAnywhere, Category = DebugWidget_Log)
	TArray<FString> ExclusionLogCategories;

	UPROPERTY(Config, EditAnywhere, Category = DebugWidget_CallStack)
	bool bIsSaveCallStack;


	UPROPERTY(config, EditAnywhere, Category = DebugWidget_VerbosityColor)
	FColor NoLogging;
	UPROPERTY(config, EditAnywhere, Category = DebugWidget_VerbosityColor)
	FColor Error;
	UPROPERTY(config, EditAnywhere, Category = DebugWidget_VerbosityColor)
	FColor Warning;
	UPROPERTY(config, EditAnywhere, Category = DebugWidget_VerbosityColor)
	FColor Display;
	UPROPERTY(config, EditAnywhere, Category = DebugWidget_VerbosityColor)
	FColor Log;
	UPROPERTY(config, EditAnywhere, Category = DebugWidget_VerbosityColor)
	FColor Verbose;
	UPROPERTY(config, EditAnywhere, Category = DebugWidget_VerbosityColor)
	FColor VeryVerbose;


};
