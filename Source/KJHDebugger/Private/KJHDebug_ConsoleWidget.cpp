// Fill out your copyright notice in the Description page of Project Settings.


#include "KJHDebug_ConsoleWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"


void UKJHDebug_ConsoleWidget::NativeConstruct()
{
	Btn_Enter->OnClicked.AddDynamic(this, &UKJHDebug_ConsoleWidget::OnClick_BtnEnter);
	ConsoleCommandEditTextBox->OnTextCommitted.AddDynamic(this, &UKJHDebug_ConsoleWidget::OnTextCommited_ConsoleCommmadEditTextBox);
}


void UKJHDebug_ConsoleWidget::OnClick_BtnEnter()
{
	ExecuteConsoleCommand();
}


void UKJHDebug_ConsoleWidget::ExecuteConsoleCommand()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->ConsoleCommand(ConsoleCommandEditTextBox->GetText().ToString(), true);
		ConsoleCommandEditTextBox->SetText(FText::FromString(""));
	}
}


void UKJHDebug_ConsoleWidget::OnTextCommited_ConsoleCommmadEditTextBox(const FText & Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		ExecuteConsoleCommand();
	}
}
