// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "KJHDebug_DebugListItemData.h"
#include "KJHDebug_DebugListItem.generated.h"


UCLASS()
class KJHDEBUGGER_API UKJHDebug_DebugListItem : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
private:
	virtual void NativeOnListItemObjectSet(UObject *DebuggerListViewItemDataObject) override;


private:
	UPROPERTY(Meta = (BindWidget))
	class UImage *VerboseImage;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *CategoryTextbox;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *LogTextbox;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *TimeTextBox;

	UPROPERTY(Meta = (BindWidget))
	class UImage *BackgroundIMG;

	UKJHDebug_DebugListItemData* CurrentDebugListViewItemData;
};
