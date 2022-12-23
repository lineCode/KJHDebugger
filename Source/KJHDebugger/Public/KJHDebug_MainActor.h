// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KJHDebug_MainWidget.h"
#include "KJHDebug_MainActor.generated.h"

UCLASS()
class KJHDEBUGGER_API AKJHDebug_MainActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AKJHDebug_MainActor();


private:
	UPROPERTY()
	TSubclassOf<UKJHDebug_MainWidget> KJHDebug_MainWidgetClass;

	UPROPERTY()
	UKJHDebug_MainWidget* CurrentKJHDebug_MainWidget;

	UPROPERTY()
	APlayerController *CurrentPlayerController;

	UPROPERTY()
	AGameModeBase *CurrentGameMode;

private:
	const class UKJHDebug_Settings* KJHDebugSetting;

private:
	virtual void BeginPlay() override;

	void CreateKJHDebug_MainWidget();

};
