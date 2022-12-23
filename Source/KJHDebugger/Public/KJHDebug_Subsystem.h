// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "KJHDebug_Subsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(KJHDebug, Log, All);


DECLARE_MULTICAST_DELEGATE_OneParam(FOnAddOptionDelegate, FOptionListItemData);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAddOptionInfoStringDelegate, FString);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAddKJHLog, ELogVerbosity::Type, FString, TCHAR*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAddDebugDelegate, FDebugListItemData);


USTRUCT()
struct FOptionListItemData
{
	GENERATED_BODY()

	FText OptionButtonText;
	FText Description;

#if UE_VER_UPPER5
	TMulticastDelegate<void()>* NoParamMultiDel;
#else
	TMulticastDelegate<void>* NoParamMultiDel;
#endif

	TWeakObjectPtr<UObject> DelegateOwnerObj;
};


USTRUCT()
struct FDebugListItemData
{
	GENERATED_BODY()

	ELogVerbosity::Type Verbosity;
	FText CategoryText;
	FText LogText;
	FString StackTrace;
	float Time;
};


UCLASS()
class KJHDEBUGGER_API UKJHDebug_Subsystem : public UGameInstanceSubsystem, public FOutputDevice
{
	GENERATED_BODY()

public:
	UKJHDebug_Subsystem();
	~UKJHDebug_Subsystem();

	FOnAddOptionDelegate OnAddOptionDelegate;
	FOnAddDebugDelegate OnAddDebugDelegate;
	FOnAddOptionInfoStringDelegate OnSetOptionInfoStringDelegate;

	ANSICHAR temp;

public:
	/*Saved Data*/
	void AddOptionListItemDataArray(FOptionListItemData OptionListItemData);
	TArray<FOptionListItemData> GetOptionListItemDataArray();

	/*Saved Data*/
	void AddDebugListItemDataArray(FDebugListItemData DebugListItemData);
	TArray<FDebugListItemData> GetDebugListItemDataArray();

	void AddOptionWidgetInfoString(FString InfoString);
	void DeleteOption(int32 pos);
	void ClearOptionWidgetInfoString();


/*this public section is for Interface to used by user!*/
public:
	/* 사용자가 옵션리스트위젯에 옵션 하나 추가하고 싶으면 불러줘야될 함수*/


#if UE_VER_UPPER5
	void AddOption(FString OptionButtonText, FString Description, UObject* DelegateOwnerObj, TMulticastDelegate<void()>* NoParamMultiDel);
#else
	void AddOption(FString OptionButtonText, FString Description, UObject* DelegateOwnerObj, TMulticastDelegate<void>* NoParamMultiDel);
#endif
	

private:
	class AKJHDebug_MainActor *MainActor;

	const class UKJHDebug_Settings *KJHDebugSetting;
	const int32 StackTraceInitCutValue = 4;
	int32 StackTraceInitCutStack = 0;

	/*data*/
	TArray<FOptionListItemData> OptionListItemDataArray;
	TArray<FDebugListItemData> DebugListItemDataArray;
	FString OptionWidgetInfoString;


private:
	/*
	 * FOutputDevice methods
	 */
	 // We're hiding UObject::Serialize() by declaring this.  That's OK, but Clang will warn about it.
	#if defined(__clang__)
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Woverloaded-virtual"
	#endif

	virtual void Serialize(const TCHAR* Log, ELogVerbosity::Type Verbosity, const FName& Category) override;

	#if defined(__clang__)
	#pragma clang diagnostic pop
	#endif

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void GetStackTrace(FString &Out);
	void SetDebugDataArrayByMaxSaveLog();
	bool CheckIsExcludeCategoryByUser(FName Category);
	void ConvertToMultiLine(const TCHAR* Message, FString& Out);
};
