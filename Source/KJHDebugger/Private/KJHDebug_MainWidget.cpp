// Fill out your copyright notice in the Description page of Project Settings.


#include "KJHDebug_MainWidget.h"
#include "Components/Button.h"
#include "Components/Overlay.h"
#include "Components/TextBlock.h"
#include "Components/OverlaySlot.h"
#include "Engine/Engine.h"


UKJHDebug_MainWidget::UKJHDebug_MainWidget(const FObjectInitializer &ObjectInitializer)
	: Super(ObjectInitializer)

{
	static ConstructorHelpers::FClassFinder<UKJHDebug_DebugListWidget>DebugListWidget(TEXT("WidgetBlueprint'/KJHDebugger/Debug/KJHDebug_DebugListWidget.KJHDebug_DebugListWidget_C'"));
	if (DebugListWidget.Succeeded()) {
		DebugListClass = DebugListWidget.Class;
	}

	static ConstructorHelpers::FClassFinder<UKJHDebug_ConsoleWidget>ConsoleWidget(TEXT("WidgetBlueprint'/KJHDebugger/Console/KJHDebug_ConsoleWidget.KJHDebug_ConsoleWidget_C'"));
	if (ConsoleWidget.Succeeded()) {
		ConsoleWidgetClass = ConsoleWidget.Class;
	}
	static ConstructorHelpers::FClassFinder<UKJHDebug_SystemInfoWidget>SystemInfoWidget(TEXT("WidgetBlueprint'/KJHDebugger/SystemInfo/systemInfo.SystemInfo_C'"));
	if (SystemInfoWidget.Succeeded()) {
		SystemInfoWidgetClass = SystemInfoWidget.Class;
	}

	static ConstructorHelpers::FClassFinder<UKJHDebug_OptionListWidget>OptionListWidget(TEXT("WidgetBlueprint'/KJHDebugger/Option/KJHDebug_OptionListWidget.KJHDebug_OptionListWidget_C'"));
	if (OptionListWidget.Succeeded()) {
		OptionListWidgetClass = OptionListWidget.Class;
	}
}


void UKJHDebug_MainWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Init();
}


void UKJHDebug_MainWidget::Init()
{
	CreateDebugListWidget();
	CreateConsoleWidget();
	CreateSystemInfoWidget();
	CreateOptionListWidget();

	MainOverlayContainer.Add(Overlay_Debug);
	MainOverlayContainer.Add(Overlay_System);
	MainOverlayContainer.Add(Overlay_Console);
	MainOverlayContainer.Add(Overlay_Option);
	HideAllMainOverlay();

	Btn_ShowMainWidget->OnClicked.AddDynamic(this, &UKJHDebug_MainWidget::OnClick_BtnShowMainWidget);
	Btn_Exit->OnClicked.AddDynamic(this, &UKJHDebug_MainWidget::OnClick_BtnExit);

	Btn_Option->OnClicked.AddDynamic(this, &UKJHDebug_MainWidget::OnClick_BtnOption);
	Btn_Debug->OnClicked.AddDynamic(this, &UKJHDebug_MainWidget::OnClick_BtnDebug);
	Btn_System->OnClicked.AddDynamic(this, &UKJHDebug_MainWidget::OnClick_BtnSystem);
	Btn_Console->OnClicked.AddDynamic(this, &UKJHDebug_MainWidget::OnClick_BtnConsole);


	HideMainWidget();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_ShowMainWidgetBtnStackReset, this,
		&UKJHDebug_MainWidget::Timer_ShowMainWidgetBtnStackReset, 1.0f, true, -1.0f);

	PauseStackTimer();
}


void UKJHDebug_MainWidget::CreateDebugListWidget()
{
	if (CurrentDebugList == nullptr)
	{
		CurrentDebugList = Cast<UKJHDebug_DebugListWidget>(CreateWidget(GetWorld(), DebugListClass));
	}
	UOverlaySlot *OverlaySlot = Overlay_Debug->AddChildToOverlay(CurrentDebugList);
	OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
	OverlaySlot->SetPadding(FMargin(40.f));
}


void UKJHDebug_MainWidget::CreateSystemInfoWidget()
{
	if (CurrentSystemInfoWidget == nullptr)
	{
		CurrentSystemInfoWidget = Cast<UKJHDebug_SystemInfoWidget>(CreateWidget(GetWorld(), SystemInfoWidgetClass));
	}
	UOverlaySlot *OverlaySlot = Overlay_System->AddChildToOverlay(CurrentSystemInfoWidget);
	OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
	OverlaySlot->SetPadding(FMargin(40.f));
}


void UKJHDebug_MainWidget::CreateConsoleWidget()
{
	if (CurrentConsoleWidget == nullptr)
	{
		CurrentConsoleWidget = Cast<UKJHDebug_ConsoleWidget>(CreateWidget(GetWorld(), ConsoleWidgetClass));
	}
	UOverlaySlot *OverlaySlot = Overlay_Console->AddChildToOverlay(CurrentConsoleWidget);
	OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
	OverlaySlot->SetPadding(FMargin(40.f));
}


void UKJHDebug_MainWidget::CreateOptionListWidget()
{
	if (CurrentOptionListWidget == nullptr)
	{
		CurrentOptionListWidget = Cast<UKJHDebug_OptionListWidget>(CreateWidget(GetWorld(), OptionListWidgetClass));
	}
	UOverlaySlot *OverlaySlot = Overlay_Option->AddChildToOverlay(CurrentOptionListWidget);
	OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
	OverlaySlot->SetPadding(FMargin(40.f));
}


void UKJHDebug_MainWidget::HideAllMainOverlay()
{
	for (int OverlayIndex = 0; OverlayIndex < MainOverlayContainer.Num(); OverlayIndex++)
	{
		MainOverlayContainer[OverlayIndex]->SetVisibility(ESlateVisibility::Hidden);
	}
}


void UKJHDebug_MainWidget::ShowMainWidget()
{
	Overlay_HiddenMainWidget->SetVisibility(ESlateVisibility::Hidden);
	Overlay_ShownMainWidget->SetVisibility(ESlateVisibility::Visible);

	CurrentSystemInfoWidget->Refresh();

}


void UKJHDebug_MainWidget::HideMainWidget()
{
	Overlay_HiddenMainWidget->SetVisibility(ESlateVisibility::Visible);
	Overlay_ShownMainWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UKJHDebug_MainWidget::ChangeTitleText(FText Title)
{
	TitleText->SetText(Title);
}


void UKJHDebug_MainWidget::PauseStackTimer()
{
	GetWorld()->GetTimerManager().PauseTimer(TimerHandle_ShowMainWidgetBtnStackReset);
}


void UKJHDebug_MainWidget::UnPauseStackTimer()
{
	GetWorld()->GetTimerManager().UnPauseTimer(TimerHandle_ShowMainWidgetBtnStackReset);
}


void UKJHDebug_MainWidget::Timer_ShowMainWidgetBtnStackReset()
{
	CurrentResetTimeForStackToShowMainWidget++;

	if (CurrentResetTimeForStackToShowMainWidget > ResetTimeForStackTosShowMainWidget)//현재 시각이 스택초기화 시간을 넘어섰다면,
	{
		CurrentStackToShowMainWidget = 0;
		PauseStackTimer();
	}
}


void UKJHDebug_MainWidget::OnClick_BtnOption()
{
	if (Overlay_Option->GetVisibility() != ESlateVisibility::Visible)
	{
		HideAllMainOverlay();
		Overlay_Option->SetVisibility(ESlateVisibility::Visible);
		ChangeTitleText(FText::FromString("Option"));
	}
	//for test
	UE_LOG(LogTemp, Warning, TEXT("OptionButtonClicked!"));
}


void UKJHDebug_MainWidget::OnClick_BtnConsole()
{
	if (Overlay_Console->GetVisibility() != ESlateVisibility::Visible)
	{
		HideAllMainOverlay();
		Overlay_Console->SetVisibility(ESlateVisibility::Visible);
		ChangeTitleText(FText::FromString("Console"));
	}
	//for test
	UE_LOG(LogTemp, Warning, TEXT("ConsoleButtonClicked!"));
}


void UKJHDebug_MainWidget::OnClick_BtnShowMainWidget()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("KJHDebug Click!"));

	CurrentResetTimeForStackToShowMainWidget = 0;
	UnPauseStackTimer();

	CurrentStackToShowMainWidget++;

	if (StackToShowMainWidget == CurrentStackToShowMainWidget)
	{
		CurrentStackToShowMainWidget = 0;
		ShowMainWidget();
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameAndUI());

		bShowMouseCursorBefore = GetWorld()->GetFirstPlayerController()->bShowMouseCursor;
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	}
}


void UKJHDebug_MainWidget::OnClick_BtnExit()
{
	HideMainWidget();
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = bShowMouseCursorBefore;
}


void UKJHDebug_MainWidget::OnClick_BtnSystem()
{
	if (Overlay_System->GetVisibility() != ESlateVisibility::Visible)
	{
		HideAllMainOverlay();
		Overlay_System->SetVisibility(ESlateVisibility::Visible);
		ChangeTitleText(FText::FromString("System"));
		CurrentSystemInfoWidget->Refresh();
	}
}


void UKJHDebug_MainWidget::OnClick_BtnDebug()
{
	if (Overlay_Debug->GetVisibility() != ESlateVisibility::Visible)
	{
		HideAllMainOverlay();
		Overlay_Debug->SetVisibility(ESlateVisibility::Visible);
		ChangeTitleText(FText::FromString("Debug"));
	}
}
