// Fill out your copyright notice in the Description page of Project Settings.


#include "KJHDebug_Settings.h"

UKJHDebug_Settings::UKJHDebug_Settings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsActive = true;
	ZOrder = 2147483600;
	MaxSaveLog = 200;
	bIsSaveCallStack = true;

	NoLogging = FColor(141, 141, 141, 255);
	Error = FColor(241, 33, 0, 255);
	Warning = FColor(255, 247, 0, 255);
	Display = FColor(105, 96, 242, 255);
	Log = FColor(0, 242, 77, 255);
	Verbose = FColor(105, 95, 243, 255);
	VeryVerbose = FColor(105, 95, 243, 255);
}