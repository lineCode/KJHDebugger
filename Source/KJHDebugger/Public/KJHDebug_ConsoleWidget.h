// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KJHDebug_ConsoleWidget.generated.h"


UCLASS()
class KJHDEBUGGER_API UKJHDebug_ConsoleWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Meta = (BindWidget))
	class UEditableTextBox *ConsoleCommandEditTextBox;
	UPROPERTY(Meta = (BindWidget))
	class UButton *Btn_Enter;


private:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnClick_BtnEnter();

	UFUNCTION()
	void ExecuteConsoleCommand();

	//ETextCommit ������ ������Ʈ.build.cs���� �ؿ��� �ּ� �������־�� ��.
	//PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	UFUNCTION()
	void OnTextCommited_ConsoleCommmadEditTextBox(const FText &Text, ETextCommit::Type CommitMethod);
};
