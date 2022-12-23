// Fill out your copyright notice in the Description page of Project Settings.


#include "KJHDebug_DebugListWidget.h"
#include "KJHDebug_DebugListItemData.h"
#include "KJHDebug_DebugListItem.h"
#include "KJHDebug_Settings.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/ComboBoxString.h"
#include "Blueprint/UserWidget.h"


void UKJHDebug_DebugListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Initializing();
}


void UKJHDebug_DebugListWidget::Initializing()
{
	KJHDebug_Subsystem = (UGameplayStatics::GetGameInstance(GetWorld()))->GetSubsystem<UKJHDebug_Subsystem>();
	KJHDebugSetting = GetDefault<UKJHDebug_Settings>();
	if (KJHDebug_Subsystem != nullptr)
	{
		AddAllSavedDebugDataToList();

		KJHDebug_Subsystem->OnAddDebugDelegate.AddUObject(this, &UKJHDebug_DebugListWidget::AddDebugDataToList);

		DebugListView->OnItemClicked().AddUObject(this, &UKJHDebug_DebugListWidget::OnListItemClicked);
		DebugListView->OnItemIsHoveredChanged().AddUObject(this, &UKJHDebug_DebugListWidget::OnListItemHovered);
		CategorySearchText->OnTextCommitted.AddDynamic(this, &UKJHDebug_DebugListWidget::OnCategorySearchTextBoxCommitted);
		LogSearchText->OnTextCommitted.AddDynamic(this, &UKJHDebug_DebugListWidget::OnLogSearchTextBoxCommitted);
		Btn_ListToBottom->OnClicked.AddDynamic(this, &UKJHDebug_DebugListWidget::OnClick_BtnListToBottom);
		VerbosityComboBox->OnSelectionChanged.AddDynamic(this, &UKJHDebug_DebugListWidget::OnClick_VerbosityComboBox);
	}
}


void UKJHDebug_DebugListWidget::AddDebugDataToList(FDebugListItemData DebugListItemData)
{
	if (!IsGarbageCollecting())
	{
		DebugListItemDataObj = NewObject<UKJHDebug_DebugListItemData>(this);
		DebugListItemDataObj->DebugListItemData = DebugListItemData;

		if (CheckIsContainSearchInfo(DebugListItemData))
		{
			DebugListView->AddItem(DebugListItemDataObj);
		}

		ResizeListByMaxSaveLog();

		if (bIsListToBottomSet == true)
		{
			DebugListView->ScrollToBottom();
		}
	}
}


void UKJHDebug_DebugListWidget::OnListItemClicked(UObject* Obj)
{
	SetStackTraceText(Obj);
}


void UKJHDebug_DebugListWidget::OnListItemHovered(UObject * Obj, bool bIsHovered)
{
	//StackTraceText->SetText(FText::FromString(""));
	//StackTraceText->Text = FText::FromString("");
}


void UKJHDebug_DebugListWidget::OnCategorySearchTextBoxCommitted(const FText & Text, ETextCommit::Type CommitMethod)
{
	SearchLog();
}


void UKJHDebug_DebugListWidget::OnLogSearchTextBoxCommitted(const FText & Text, ETextCommit::Type CommitMethod)
{
	SearchLog();	
}


void UKJHDebug_DebugListWidget::OnClick_VerbosityComboBox(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	SearchLog();
}


void UKJHDebug_DebugListWidget::OnClick_BtnListToBottom()
{
	ToggleListToBottom();
}


void UKJHDebug_DebugListWidget::AddAllSavedDebugDataToList()
{
	TArray<FDebugListItemData> SavedItemDataArray = KJHDebug_Subsystem->GetDebugListItemDataArray();
	for (int DataIdx = 0; DataIdx < SavedItemDataArray.Num(); DataIdx++)
	{
		AddDebugDataToList(SavedItemDataArray[DataIdx]);
	}
}


void UKJHDebug_DebugListWidget::ToggleListToBottom()
{
	if (bIsListToBottomSet == true)
	{
		bIsListToBottomSet = false;
		ListToBottomText->SetColorAndOpacity(FSlateColor(FLinearColor(0.2f, 0.2f, 0.2f, 1.0f)));
	}
	else
	{
		bIsListToBottomSet = true; 
		ListToBottomText->SetColorAndOpacity(FSlateColor(FLinearColor(0.f, 0.63f, 1.0f, 1.0f)));
		DebugListView->ScrollToBottom();
	}
}


void UKJHDebug_DebugListWidget::SetStackTraceText(UObject * Obj)
{
	UKJHDebug_DebugListItemData *ItemDataObj = Cast<UKJHDebug_DebugListItemData>(Obj);
	StackTraceNameText->SetText(ItemDataObj->DebugListItemData.LogText);
	StackTraceText->SetText(FText::FromString(ItemDataObj->DebugListItemData.StackTrace));
}


void UKJHDebug_DebugListWidget::SearchLog()
{
	DebugListView->ClearListItems();

	if (LogSearchText->GetText().IsEmpty() && CategorySearchText->GetText().IsEmpty() && VerbosityComboBox->GetSelectedOption().Equals("All"))
	{
		AddAllSavedDebugDataToList();
	}
	else
	{
		TArray<FDebugListItemData> SavedItemDataArray = KJHDebug_Subsystem->GetDebugListItemDataArray();
		int32 SavedItemSize = SavedItemDataArray.Num();

		for (int32 idx = 0; idx < SavedItemSize; idx++)
		{
			if (!CheckIsContainSearchInfo(SavedItemDataArray[idx]))
			{
				SavedItemDataArray.RemoveAt(idx);
				idx--;
				SavedItemSize--;
				continue;
			}
		}

		for (int32 idx = 0; idx < SavedItemSize; idx++)
		{
			AddDebugDataToList(SavedItemDataArray[idx]);
		}
	}
}


void UKJHDebug_DebugListWidget::ResizeListByMaxSaveLog()
{
	if (DebugListView->GetNumItems()> KJHDebugSetting->MaxSaveLog)
	{
		DebugListView->RemoveItem(DebugListView->GetItemAt(0));
	}
}


bool UKJHDebug_DebugListWidget::CheckIsContainSearchInfo(FDebugListItemData DebugListItemData)
{
	FString SearchLog = LogSearchText->GetText().ToString();
	FString Log = DebugListItemData.LogText.ToString();

	if (!LogSearchText->GetText().IsEmpty() && !Log.Contains(SearchLog))//포함되어 있지 않으면
	{
		return false;
	}

	if (!CategorySearchText->GetText().IsEmpty() && !CategorySearchText->GetText().EqualToCaseIgnored(DebugListItemData.CategoryText))//같지 않으면 빼기
	{
		return false;
	}

	if (!VerbosityComboBox->GetSelectedOption().Equals("All") && !VerbosityComboBox->GetSelectedOption().Equals(ParseVerbosityToString(DebugListItemData.Verbosity)))
	{
		return false;
	}

	return true;
}


FString UKJHDebug_DebugListWidget::ParseVerbosityToString(ELogVerbosity::Type Verbose)
{
	switch (Verbose)
	{
	case 0: //NoLogging
		return "NoLoggging";
		break;

	case 2://Error
		return "Error";
		break;

	case 3://Warning
		return "Warning";
		break;

	case 4://Display
		return "Display";
		break;

	case 5://Log
		return "Log";
		break;

	case 6://Verbose
		return "Verbose";
		break;

	case 7://VeryVerbose
		return "VeryVerbose";
		break;

	default:
		return "";
		break;
	}
}
