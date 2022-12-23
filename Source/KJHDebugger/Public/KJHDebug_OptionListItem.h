// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "KJHDebug_OptionListItem.generated.h"

/**
 * 
 */
UCLASS()
class KJHDEBUGGER_API UKJHDebug_OptionListItem : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

private:
	UPROPERTY(Meta = (BindWidget))
	class UButton *Btn_Option;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *OptionButtonText;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *Description;

	class UKJHDebug_OptionListItemData *CurrentOptionListViewItemData;
	class UKJHDebug_Subsystem *KJHDebug_Subsystem;


private:
	virtual void NativeConstruct() override;
	virtual void NativeOnListItemObjectSet(UObject *OptionListViewItemDataObject) override;

	UFUNCTION()
	void ExecuteOptionDelegate();

	UFUNCTION()
	void OnClickOptionBTN();
};
