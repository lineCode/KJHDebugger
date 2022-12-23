// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KJHDebug_SystemInfoWidget.generated.h"


UCLASS()
class KJHDEBUGGER_API UKJHDebug_SystemInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Refresh();

private:
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *OSVersion;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *CPUInfo;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *CPUCore;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *CPUVendor;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *RAM;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *GPUDriverInfo;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *PrimaryGPUBrand;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *GraphicsAPI;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *DeviceType;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *EngineMode;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *RunTime;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *CurrentLevel;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *Language;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *ScreenResolution;

	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *UEVersion;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *BuildDate;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *GraphicsRHI;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *BranchName;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *BuildTargetType;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *AppName;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *ProjectName;
	UPROPERTY(Meta = (BindWidget))
	class UTextBlock *BuildConfiguration;

private:
	virtual void NativeConstruct() override;

	FString GetPlatformName();
	FString GetCPUBrandName();
	FString GetCPUVendeor();
	FString GetOSVersion();
	int32 GetNumberOfCores();

	FString GetGPUBrandName();
	FString GetGPUDriverInfo();
	FString GetGraphicsAPI();

	int32 GetTotalRAM();
	FString GetGameResolution();

	FString GetCurrentLevelName();
	FString GetEngineMode();
	float GetRunTime();
	FString GetLanguage();

	FString GetUEVersion();
	FString GetBuildTargetType();
	FString GetBuildConfiguration();
};
