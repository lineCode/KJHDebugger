// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KJHDebug_Subsystem.h"
#include "KJHDebug_DebugListWidget.generated.h"


UCLASS()
class KJHDEBUGGER_API UKJHDebug_DebugListWidget : public UUserWidget
{
	GENERATED_BODY()


private:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void Initializing();

	UFUNCTION()
	void SearchLog();

	UFUNCTION()
	void ResizeListByMaxSaveLog();

	UFUNCTION()
	void AddAllSavedDebugDataToList();

	UFUNCTION()
	void ToggleListToBottom();

	UFUNCTION()
	void SetStackTraceText(UObject* Obj);

	UFUNCTION()
	bool CheckIsContainSearchInfo(FDebugListItemData DebugListItemData);

	UFUNCTION()
	void AddDebugDataToList(FDebugListItemData DebugListItemData);


	UFUNCTION()
	void OnListItemClicked(UObject* Obj);

	UFUNCTION()
	void OnListItemHovered(UObject* Obj, bool bIsHovered);

	UFUNCTION()
	void OnCategorySearchTextBoxCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void OnLogSearchTextBoxCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void OnClick_BtnListToBottom();

	UFUNCTION()
	void OnClick_VerbosityComboBox(FString SelectedItem, ESelectInfo::Type SelectionType);


private:
	UPROPERTY(Meta = (BindWidget))
	class UListView *DebugListView;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *StackTraceText;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *StackTraceNameText;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *ListToBottomText;

	UPROPERTY(Meta = (BindWidget))
	class UEditableText *CategorySearchText;

	UPROPERTY(Meta = (BindWidget))
	class UEditableText *LogSearchText;

	UPROPERTY(Meta = (BindWidget))
	class UButton *Btn_ListToBottom;

	UPROPERTY(Meta = (BindWidget))
	class UComboBoxString *VerbosityComboBox;

	FString ParseVerbosityToString(ELogVerbosity::Type Verbose);

	class UKJHDebug_DebugListItemData *DebugListItemDataObj;
	class UKJHDebug_Subsystem *KJHDebug_Subsystem;
	const class UKJHDebug_Settings *KJHDebugSetting;

	bool bIsListToBottomSet = true;
};
