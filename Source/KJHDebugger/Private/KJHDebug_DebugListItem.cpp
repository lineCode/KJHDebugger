// Fill out your copyright notice in the Description page of Project Settings.


#include "KJHDebug_DebugListItem.h"
#include "KJHDebug_Subsystem.h"
#include "KJHDebug_Settings.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Kismet/KismetMathLibrary.h"


void UKJHDebug_DebugListItem::NativeOnListItemObjectSet(UObject * DebuggerListViewItemDataObject)
{
	CurrentDebugListViewItemData = Cast<UKJHDebug_DebugListItemData>(DebuggerListViewItemDataObject);

	const UKJHDebug_Settings *KJHDebugSetting = GetDefault<UKJHDebug_Settings>();
	if (KJHDebugSetting)
	{
		//실시간 변화를 위해서는 Set해줄때 색을 set해줘야됨.
		if (CurrentDebugListViewItemData != nullptr)
		{
			CategoryTextbox->SetText(CurrentDebugListViewItemData->DebugListItemData.CategoryText);
			LogTextbox->SetText(CurrentDebugListViewItemData->DebugListItemData.LogText);
			TimeTextBox->SetText(FText::FromString(FString::SanitizeFloat(CurrentDebugListViewItemData->DebugListItemData.Time)));

			switch (CurrentDebugListViewItemData->DebugListItemData.Verbosity)
			{
			case 0: //NoLogging
				VerboseImage->SetColorAndOpacity(KJHDebugSetting->NoLogging);
				break;

			case 2://Error
				VerboseImage->SetColorAndOpacity(KJHDebugSetting->Error);
				break;

			case 3://Warning
				VerboseImage->SetColorAndOpacity(KJHDebugSetting->Warning);
				break;

			case 4://Display
				VerboseImage->SetColorAndOpacity(KJHDebugSetting->Display);
				break;

			case 5://Log
				VerboseImage->SetColorAndOpacity(KJHDebugSetting->Log);
				break;

			case 6://Verbose
				VerboseImage->SetColorAndOpacity(KJHDebugSetting->Verbose);
				break;

			case 7://VeryVerbose
				VerboseImage->SetColorAndOpacity(KJHDebugSetting->VeryVerbose);
				break;
			default:
				break;
			}
		}
	}
}
