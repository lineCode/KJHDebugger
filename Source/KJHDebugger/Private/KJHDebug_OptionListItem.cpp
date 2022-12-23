// Fill out your copyright notice in the Description page of Project Settings.


#include "KJHDebug_OptionListItem.h"
#include "KJHDebug_OptionListItemData.h"
#include "KJHDebug_Subsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"


void UKJHDebug_OptionListItem::NativeConstruct()
{
	Btn_Option->OnClicked.AddDynamic(this, &UKJHDebug_OptionListItem::OnClickOptionBTN);
	KJHDebug_Subsystem = (UGameplayStatics::GetGameInstance(GetWorld()))->GetSubsystem<UKJHDebug_Subsystem>();
}


void UKJHDebug_OptionListItem::NativeOnListItemObjectSet(UObject * OptionListViewItemDataObject)
{
	CurrentOptionListViewItemData = Cast<UKJHDebug_OptionListItemData>(OptionListViewItemDataObject);

	if (CurrentOptionListViewItemData != nullptr)
	{
		OptionButtonText->SetText(CurrentOptionListViewItemData->OptionListItemData.OptionButtonText);
		Description->SetText(CurrentOptionListViewItemData->OptionListItemData.Description);
	}
}


void UKJHDebug_OptionListItem::ExecuteOptionDelegate()
{
	if (CurrentOptionListViewItemData != nullptr)
	{
		if (CurrentOptionListViewItemData->OptionListItemData.NoParamMultiDel != nullptr)
		{
			if(CurrentOptionListViewItemData->OptionListItemData.DelegateOwnerObj.IsValid())
			{
				CurrentOptionListViewItemData->OptionListItemData.NoParamMultiDel->Broadcast();
				FString Info = CurrentOptionListViewItemData->OptionListItemData.OptionButtonText.ToString() + " Option Execute -> Owner :" + CurrentOptionListViewItemData->OptionListItemData.DelegateOwnerObj->GetName();
				KJHDebug_Subsystem->AddOptionWidgetInfoString(Info);
			}		
			else
			{
				FString Info = "Can't Execute Option" + CurrentOptionListViewItemData->OptionListItemData.OptionButtonText.ToString() + " -> Invalid Delegate Owner ";
				KJHDebug_Subsystem->AddOptionWidgetInfoString(Info);
			}
		}
	}
}


void UKJHDebug_OptionListItem::OnClickOptionBTN()
{
	ExecuteOptionDelegate();
}
