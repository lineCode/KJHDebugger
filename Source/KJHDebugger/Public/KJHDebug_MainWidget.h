// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KJHDebug_DebugListWidget.h"
#include "KJHDebug_ConsoleWidget.h"
#include "KJHDebug_SystemInfoWidget.h"
#include "KJHDebug_OptionListWidget.h"
#include "KJHDebug_MainWidget.generated.h"


UCLASS()
class KJHDEBUGGER_API UKJHDebug_MainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UKJHDebug_MainWidget(const FObjectInitializer &ObjectInitializer);

	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	TSubclassOf<UKJHDebug_DebugListWidget> DebugListClass;

	UPROPERTY()
	UKJHDebug_DebugListWidget* CurrentDebugList;

	UPROPERTY()
	TSubclassOf<UKJHDebug_ConsoleWidget> ConsoleWidgetClass;

	UPROPERTY()
	UKJHDebug_ConsoleWidget* CurrentConsoleWidget;

	UPROPERTY()
	TSubclassOf<UKJHDebug_SystemInfoWidget> SystemInfoWidgetClass;

	UPROPERTY()
	UKJHDebug_SystemInfoWidget* CurrentSystemInfoWidget;

	UPROPERTY()
	TSubclassOf<UKJHDebug_OptionListWidget> OptionListWidgetClass;

	UPROPERTY()
	UKJHDebug_OptionListWidget* CurrentOptionListWidget;



	UPROPERTY(Meta = (BindWidget))
	class UButton *Btn_ShowMainWidget;

	UPROPERTY(Meta = (BindWidget))
	class UButton *Btn_Exit;

	UPROPERTY(Meta = (BindWidget))
	class UButton *Btn_Option;

	UPROPERTY(Meta = (BindWidget))
	class UButton *Btn_Console;

	UPROPERTY(Meta = (BindWidget))
	class UButton *Btn_System;

	UPROPERTY(Meta = (BindWidget))
	class UButton *Btn_Debug;

	UPROPERTY(Meta = (BindWidget))
	class UOverlay *Overlay_HiddenMainWidget;

	UPROPERTY(Meta = (BindWidget))
	class UOverlay *Overlay_ShownMainWidget;

	UPROPERTY(Meta = (BindWidget))
	class UOverlay *Overlay_System;

	UPROPERTY(Meta = (BindWidget))
	class UOverlay *Overlay_Debug;

	UPROPERTY(Meta = (BindWidget))
	class UOverlay *Overlay_Option;

	UPROPERTY(Meta = (BindWidget))
	class UOverlay *Overlay_Console;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *TitleText;


	FTimerHandle TimerHandle_ShowMainWidgetBtnStackReset;

	TArray<UOverlay *> MainOverlayContainer;


	const int32 ResetTimeForStackTosShowMainWidget = 3; //스택이 초기화 되는 시간
	const int32 StackToShowMainWidget = 5;//보여지려면 쌓아야 할 스택 개수

	int32 CurrentResetTimeForStackToShowMainWidget;
	int32 CurrentStackToShowMainWidget;

	bool bShowMouseCursorBefore;

private:
	void Init();
	void ShowMainWidget();
	void HideMainWidget();
	void ChangeTitleText(FText Title);
	void PauseStackTimer();
	void UnPauseStackTimer();


	void CreateDebugListWidget();
	void CreateSystemInfoWidget();
	void CreateConsoleWidget();
	void CreateOptionListWidget();
	void HideAllMainOverlay();


	UFUNCTION()
	void Timer_ShowMainWidgetBtnStackReset();

	UFUNCTION()
	void OnClick_BtnOption();

	UFUNCTION()
	void OnClick_BtnConsole();

	UFUNCTION()
	void OnClick_BtnShowMainWidget();

	UFUNCTION()
	void OnClick_BtnExit();

	UFUNCTION()
	void OnClick_BtnSystem();

	UFUNCTION()
	void OnClick_BtnDebug();

};
