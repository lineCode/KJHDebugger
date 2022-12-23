// Fill out your copyright notice in the Description page of Project Settings.


#include "KJHDebug_Subsystem.h"
#include "KJHDebug_MainActor.h"
#include "KJHDebug_Settings.h"
#include "Engine/Engine.h"


DEFINE_LOG_CATEGORY(KJHDebug);


UKJHDebug_Subsystem::UKJHDebug_Subsystem()
{
	check(GLog);
	GLog->AddOutputDevice(this);
}


UKJHDebug_Subsystem::~UKJHDebug_Subsystem()
{
	if (GLog != nullptr)
	{
		GLog->RemoveOutputDevice(this);
	}
}


void UKJHDebug_Subsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	KJHDebugSetting = GetDefault<UKJHDebug_Settings>();
}


void UKJHDebug_Subsystem::AddOptionListItemDataArray(FOptionListItemData OptionListItemData)
{
	OptionListItemDataArray.Add(OptionListItemData);
}


TArray<FOptionListItemData> UKJHDebug_Subsystem::GetOptionListItemDataArray()
{
	return OptionListItemDataArray;
}


void UKJHDebug_Subsystem::AddDebugListItemDataArray(FDebugListItemData DebugListItemData)
{
	DebugListItemDataArray.Add(DebugListItemData);
}


TArray<FDebugListItemData> UKJHDebug_Subsystem::GetDebugListItemDataArray()
{
	return DebugListItemDataArray;
}


void UKJHDebug_Subsystem::Serialize(const TCHAR * Log, ELogVerbosity::Type Verbosity, const FName & Category)
{
	if (KJHDebugSetting == nullptr) 
	{
		KJHDebugSetting = GetDefault<UKJHDebug_Settings>();
	}

	if(KJHDebugSetting->bIsActive)
	{
		if (CheckIsExcludeCategoryByUser(Category))
		{
			return;
		}
		else
		{
			FString StackTraceString;
			if (KJHDebugSetting->bIsSaveCallStack)
			{	
				GetStackTrace(StackTraceString);
			}

			FDebugListItemData DebugListItemData;
			DebugListItemData.LogText = FText::FromString(Log);
			DebugListItemData.CategoryText = FText::FromName(Category);
			DebugListItemData.Verbosity = Verbosity;
			DebugListItemData.StackTrace = StackTraceString;

			if (GetWorld() != nullptr)
			{
				DebugListItemData.Time = UGameplayStatics::GetRealTimeSeconds(GetWorld());
			}

			AddDebugListItemDataArray(DebugListItemData);
			SetDebugDataArrayByMaxSaveLog();

			if (!IsGarbageCollecting())
			{
				OnAddDebugDelegate.Broadcast(DebugListItemData);
			}
		}
	}
}


void UKJHDebug_Subsystem::GetStackTrace(FString &Out)
{
#if !NO_LOGGING
	// Walk the stack and dump it to the allocated memory.
	const SIZE_T StackTraceSize = 65535;
	ANSICHAR* StackTrace = (ANSICHAR*)FMemory::SystemMalloc(StackTraceSize);

	StackTrace[0] = 0;

	const int32 NumStackFramesToIgnore = 1;
	FPlatformStackWalk::StackWalkAndDumpEx(StackTrace, StackTraceSize, NumStackFramesToIgnore, FGenericPlatformStackWalk::EStackWalkFlags::FlagsUsedWhenHandlingEnsure);
	
	ConvertToMultiLine(ANSI_TO_TCHAR(StackTrace), Out);

	GLog->Flush();
	FMemory::SystemFree(StackTrace);
#endif
}


bool UKJHDebug_Subsystem::CheckIsExcludeCategoryByUser(FName Category)
{
	TArray<FString> ExclusionLogCategories = KJHDebugSetting->ExclusionLogCategories;

	for (int32 idx = 0; idx < KJHDebugSetting->ExclusionLogCategories.Num(); idx++)
	{
		if (Category==(FName(*ExclusionLogCategories[idx])))//if same, return 0
		{
			return true;
		}
	}

	return false;
}


void UKJHDebug_Subsystem::ConvertToMultiLine(const TCHAR* Message, FString& Out)
{
	StackTraceInitCutStack = 0;
	for (const TCHAR* LineStart = Message;; )
	{
		TCHAR SingleLine[1024];

		// Find the end of the current line
		const TCHAR* LineEnd = LineStart;
		TCHAR* SingleLineWritePos = SingleLine;
		int32 SpaceRemaining = UE_ARRAY_COUNT(SingleLine) - 1;

		while (SpaceRemaining > 0 && *LineEnd != 0 && *LineEnd != '\r' && *LineEnd != '\n')
		{
			*SingleLineWritePos++ = *LineEnd++;
			--SpaceRemaining;
		}

		// cap it
		*SingleLineWritePos = 0;


		if (StackTraceInitCutStack >= StackTraceInitCutValue)
		{
			Out.Append(SingleLine);
			Out.Append("\n");
		}
		else
		{
			StackTraceInitCutStack++;
		}

		// Quit if this was the last line
		if (*LineEnd == 0)
		{
			break;
		}

		// Move to the next line
		LineStart = (LineEnd[0] == '\r' && LineEnd[1] == '\n') ? (LineEnd + 2) : (LineEnd + 1);
	}
}


#if UE_VER_UPPER5
void UKJHDebug_Subsystem::AddOption(FString OptionButtonText, FString Description, UObject* DelegateOwnerObj, TMulticastDelegate<void()>* NoParamMultiDel)
{
	if (KJHDebugSetting->bIsActive)
	{
		FOptionListItemData OptionListItemData;
		OptionListItemData.OptionButtonText = FText::FromString(OptionButtonText);
		OptionListItemData.Description = FText::FromString(Description);
		OptionListItemData.NoParamMultiDel = NoParamMultiDel;
		OptionListItemData.DelegateOwnerObj = DelegateOwnerObj;

		AddOptionListItemDataArray(OptionListItemData);

		OnAddOptionDelegate.Broadcast(OptionListItemData);
	}
}
#else
void UKJHDebug_Subsystem::AddOption(FString OptionButtonText, FString Description, UObject* DelegateOwnerObj, TMulticastDelegate<void>* NoParamMultiDel)
{
	if (KJHDebugSetting->bIsActive)
	{
		FOptionListItemData OptionListItemData;
		OptionListItemData.OptionButtonText = FText::FromString(OptionButtonText);
		OptionListItemData.Description = FText::FromString(Description);
		OptionListItemData.NoParamMultiDel = NoParamMultiDel;
		OptionListItemData.DelegateOwnerObj = DelegateOwnerObj;

		AddOptionListItemDataArray(OptionListItemData);

		OnAddOptionDelegate.Broadcast(OptionListItemData);
	}
}
#endif


void UKJHDebug_Subsystem::AddOptionWidgetInfoString(FString InfoString)
{
	OptionWidgetInfoString.Append("\n");
	OptionWidgetInfoString.Append(InfoString);

	OnSetOptionInfoStringDelegate.Broadcast(OptionWidgetInfoString);
}


void UKJHDebug_Subsystem::ClearOptionWidgetInfoString()
{
	OptionWidgetInfoString.Empty();

	OnSetOptionInfoStringDelegate.Broadcast(OptionWidgetInfoString);
}


void UKJHDebug_Subsystem::SetDebugDataArrayByMaxSaveLog()
{
	if (DebugListItemDataArray.Num() >= KJHDebugSetting->MaxSaveLog)
	{
		DebugListItemDataArray.RemoveAt(0);
	}
}


void UKJHDebug_Subsystem::DeleteOption(int32 Pos)
{
	OptionListItemDataArray.RemoveAt(Pos);
}




