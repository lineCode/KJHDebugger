// Fill out your copyright notice in the Description page of Project Settings.


#include "KJHDebug_MainActor.h"
#include "KJHDebug_Settings.h"
#include "Kismet/GameplayStatics.h"


AKJHDebug_MainActor::AKJHDebug_MainActor()
{
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FClassFinder<UKJHDebug_MainWidget>KJHDebugWidget(TEXT("WidgetBlueprint'/KJHDebugger/KJHDebug_MainWidget.KJHDebug_MainWidget_C'"));
	if (KJHDebugWidget.Succeeded()) {
		KJHDebug_MainWidgetClass = KJHDebugWidget.Class;
	}
}


void AKJHDebug_MainActor::BeginPlay()
{
	Super::BeginPlay();
	KJHDebugSetting = GetDefault<UKJHDebug_Settings>();
	
	if (KJHDebugSetting->bIsActive)
	{
		CreateKJHDebug_MainWidget();
	}
}


void AKJHDebug_MainActor::CreateKJHDebug_MainWidget()
{
	if (CurrentKJHDebug_MainWidget == nullptr)
	{
		CurrentKJHDebug_MainWidget = Cast<UKJHDebug_MainWidget>(CreateWidget(GetWorld(), KJHDebug_MainWidgetClass));
		if (CurrentKJHDebug_MainWidget != nullptr)
		{
			int32 ZOrder = KJHDebugSetting->ZOrder;
			CurrentKJHDebug_MainWidget->AddToViewport(ZOrder);
		}
	}
}

