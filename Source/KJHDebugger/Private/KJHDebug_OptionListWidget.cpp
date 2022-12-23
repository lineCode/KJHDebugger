// Fill out your copyright notice in the Description page of Project Settings.


#include "KJHDebug_OptionListWidget.h"
#include "KJHDebug_OptionListItemData.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"

void UKJHDebug_OptionListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Initializing();
}


void UKJHDebug_OptionListWidget::Initializing()
{
	KJHDebug_Subsystem = (UGameplayStatics::GetGameInstance(GetWorld()))->GetSubsystem<UKJHDebug_Subsystem>();
	
	Btn_InfoClear->OnClicked.AddDynamic(this, &UKJHDebug_OptionListWidget::OnClick_BtnInfoClear);
	Btn_InfoToBottom->OnClicked.AddDynamic(this, &UKJHDebug_OptionListWidget::OnClick_BtnInfoToBottom);

	KJHDebug_Subsystem->OnAddOptionDelegate.AddUObject(this, &UKJHDebug_OptionListWidget::AddOptionDataToList);
	KJHDebug_Subsystem->OnSetOptionInfoStringDelegate.AddUObject(this, &UKJHDebug_OptionListWidget::SetInfoText);

	Refresh();
}


/*서브시스템으로부터 저장된 옵션리스트 데이터 불러와서 적용시키는 과정*/
void UKJHDebug_OptionListWidget::Refresh()
{
	if (KJHDebug_Subsystem != nullptr)
	{
		TArray<FOptionListItemData> SavedItemDataArray = KJHDebug_Subsystem->GetOptionListItemDataArray();
		int32 ItemDataSize = SavedItemDataArray.Num();

		for (int DataIdx = 0; DataIdx < ItemDataSize; DataIdx++)
		{
			if (SavedItemDataArray[DataIdx].DelegateOwnerObj.IsValid() == true)
			{
				AddOptionDataToList(SavedItemDataArray[DataIdx]);
			}
			else
			{
				FString Info = SavedItemDataArray[DataIdx].OptionButtonText.ToString() +" Option Deleted : Invalid Delegate Owner";
				KJHDebug_Subsystem->AddOptionWidgetInfoString(Info);

				KJHDebug_Subsystem->DeleteOption(DataIdx);
				SavedItemDataArray.RemoveAt(DataIdx);
				DataIdx--;
				ItemDataSize--;
			}
		}	
	}
}


void UKJHDebug_OptionListWidget::AddOptionDataToList(FOptionListItemData OptionListItemData)
{
	if (OptionListItemData.DelegateOwnerObj.IsValid() == true)
	{
		if (OptionListItemData.NoParamMultiDel != nullptr)
		{
			OptionListItemDataObj = NewObject<UKJHDebug_OptionListItemData>(this);
			OptionListItemDataObj->OptionListItemData = OptionListItemData;
			OptionListItemDataObj->OptionListItemData.DelegateOwnerObj = OptionListItemData.DelegateOwnerObj;
			OptionListView->AddItem(OptionListItemDataObj);

			FString Info = OptionListItemData.OptionButtonText.ToString()+ " Option Spawned From " + OptionListItemData.DelegateOwnerObj->GetName();
			KJHDebug_Subsystem->AddOptionWidgetInfoString(Info);
		}
	}
}


void UKJHDebug_OptionListWidget::SetInfoText(FString InfoString)
{
	InfoText->SetText(FText::FromString(InfoString));

	if (bIsScrollBoxToBottom == true)
	{
		InfoScrollBox->ScrollToEnd();
	}
}


void UKJHDebug_OptionListWidget::ResetInfoText()
{
	KJHDebug_Subsystem->ClearOptionWidgetInfoString();
}


void UKJHDebug_OptionListWidget::ToggleScrollBoxToBottom()
{
	if (bIsScrollBoxToBottom == true)
	{
		bIsScrollBoxToBottom = false;
		InfoToBottomText->SetColorAndOpacity(FSlateColor(FLinearColor(0.2f, 0.2f, 0.2f, 1.0f)));
	}
	else
	{
		bIsScrollBoxToBottom = true;
		InfoScrollBox->ScrollToEnd();
		InfoToBottomText->SetColorAndOpacity(FSlateColor(FLinearColor(0.f, 0.63f, 1.0f, 1.0f)));
	}
}


void UKJHDebug_OptionListWidget::OnClick_BtnInfoToBottom()
{
	ToggleScrollBoxToBottom();
}


void UKJHDebug_OptionListWidget::OnClick_BtnInfoClear()
{
	ResetInfoText();
}


