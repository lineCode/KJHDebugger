// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KJHDebug_Subsystem.h"
#include "KJHDebug_OptionListWidget.generated.h"

/**
 * 
 */
UCLASS()
class KJHDEBUGGER_API UKJHDebug_OptionListWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(Meta = (BindWidget))
	class UListView *OptionListView;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *InfoText;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *InfoToBottomText;

	UPROPERTY(Meta = (BindWidget))
	class UButton *Btn_InfoClear;

	UPROPERTY(Meta = (BindWidget))
	class UButton *Btn_InfoToBottom;

	UPROPERTY(Meta = (BindWidget))
	class UScrollBox *InfoScrollBox;

	bool bIsScrollBoxToBottom = true;

	class UKJHDebug_OptionListItemData *OptionListItemDataObj;
	class UKJHDebug_Subsystem *KJHDebug_Subsystem;

private:
	virtual void NativeConstruct() override;

	void Initializing();
	void Refresh();
	void ResetInfoText();
	void ToggleScrollBoxToBottom();

	UFUNCTION()
	void OnClick_BtnInfoToBottom();

	UFUNCTION()
	void OnClick_BtnInfoClear();

	UFUNCTION()
	void AddOptionDataToList(FOptionListItemData OptionListItemData);

	UFUNCTION()
	void SetInfoText(FString InfoString);
};
