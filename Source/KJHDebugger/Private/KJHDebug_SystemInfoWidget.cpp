// Fill out your copyright notice in the Description page of Project Settings.


#include "KJHDebug_SystemInfoWidget.h"

#if PLATFORM_WINDOWS
#include "Windows/WindowsPlatformMisc.h"
#elif PLATFORM_ANDROID
#include "Android/AndroidPlatformMisc.h"
#elif PLATFORM_IOS
#include "IOS/IOSPlatformMisc.h"
#elif PLATFORM_MAC
#include "Mac/MacPlatformMisc.h"
#endif

#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "HardwareInfo.h"
#include "Misc/App.h"


void UKJHDebug_SystemInfoWidget::NativeConstruct()
{
	Refresh();
}


void UKJHDebug_SystemInfoWidget::Refresh()
{
	OSVersion->SetText(FText::FromString(GetPlatformName() + " " + GetOSVersion()));
	CPUInfo->SetText(FText::FromString(GetCPUBrandName()));
	CPUCore->SetText(FText::FromString(FString::FromInt(GetNumberOfCores())));
	CPUVendor->SetText(FText::FromString(GetCPUVendeor()));
	RAM->SetText(FText::FromString(FString::FromInt(GetTotalRAM()) + "GB"));

	GPUDriverInfo->SetText(FText::FromString(GetGPUDriverInfo()));
	PrimaryGPUBrand->SetText(FText::FromString(GetGPUBrandName()));
	GraphicsAPI->SetText(FText::FromString(GetGraphicsAPI()));
	DeviceType->SetText(FText::FromString(FHardwareInfo::GetHardwareInfo(NAME_TextureFormat)));

	EngineMode->SetText(FText::FromString(GetEngineMode()));
	RunTime->SetText(FText::FromString(FString::SanitizeFloat(GetRunTime())));
	CurrentLevel->SetText(FText::FromString(GetCurrentLevelName()));
	Language->SetText(FText::FromString(GetLanguage()));
	ScreenResolution->SetText(FText::FromString(GetGameResolution()));

	UEVersion->SetText(FText::FromString(GetUEVersion()));
	BuildDate->SetText(FText::FromString(FApp::GetBuildDate()));
	GraphicsRHI->SetText(FText::FromString(FApp::GetGraphicsRHI()));
	BranchName->SetText(FText::FromString(FApp::GetBranchName()));
	BuildTargetType->SetText(FText::FromString(GetBuildTargetType()));
	AppName->SetText(FText::FromString(FApp::GetName()));
	ProjectName->SetText(FText::FromString(FApp::GetProjectName()));
	BuildConfiguration->SetText(FText::FromString(GetBuildConfiguration()));
}


FString UKJHDebug_SystemInfoWidget::GetPlatformName()
{
	return UGameplayStatics::GetPlatformName();
}


FString UKJHDebug_SystemInfoWidget::GetCPUBrandName()
{
	return FPlatformMisc::GetCPUBrand();
}


FString UKJHDebug_SystemInfoWidget::GetCPUVendeor()
{
	return FPlatformMisc::GetCPUVendor();
}


FString UKJHDebug_SystemInfoWidget::GetOSVersion()
{
	return FPlatformMisc::GetOSVersion();
}


int32 UKJHDebug_SystemInfoWidget::GetNumberOfCores()
{
	return FPlatformMisc::NumberOfCores();
}


FString UKJHDebug_SystemInfoWidget::GetGPUBrandName()
{
	return FPlatformMisc::GetPrimaryGPUBrand();
}


FString UKJHDebug_SystemInfoWidget::GetGPUDriverInfo()
{
	return GRHIAdapterUserDriverVersion;
}

FString UKJHDebug_SystemInfoWidget::GetGraphicsAPI()
{
	return FHardwareInfo::GetHardwareInfo(NAME_RHI);
}


int32 UKJHDebug_SystemInfoWidget::GetTotalRAM()
{
	const FPlatformMemoryConstants& MemoryConstants = FPlatformMemory::GetConstants();
	return MemoryConstants.TotalPhysicalGB;
}


FString UKJHDebug_SystemInfoWidget::GetGameResolution()
{
	const FIntPoint ScreenRes = (UGameUserSettings::GetGameUserSettings())->GetScreenResolution();
	FString ScreenResol = FString::Printf(TEXT("%d X %d"), ScreenRes.X, ScreenRes.Y);
	return ScreenResol;
}


FString UKJHDebug_SystemInfoWidget::GetCurrentLevelName()
{
	return UGameplayStatics::GetCurrentLevelName(GetWorld());
}


FString UKJHDebug_SystemInfoWidget::GetEngineMode()
{
	return FPlatformMisc::GetEngineMode();
}


FString UKJHDebug_SystemInfoWidget::GetUEVersion()
{
	return UKismetSystemLibrary::GetEngineVersion();
}


float UKJHDebug_SystemInfoWidget::GetRunTime()
{
	return UGameplayStatics::GetRealTimeSeconds(GetWorld());
}


FString UKJHDebug_SystemInfoWidget::GetLanguage()
{
	return UKismetSystemLibrary::GetDefaultLanguage();
}

FString UKJHDebug_SystemInfoWidget::GetBuildTargetType()
{
	switch (FApp::GetBuildTargetType())
	{
	case EBuildTargetType::Unknown:
		return "Unknown";
		break;
	case EBuildTargetType::Game:
		return "Game";
		break;
	case EBuildTargetType::Server:
		return "Server";
		break;
	case EBuildTargetType::Client:
		return "Client";
		break;
	case EBuildTargetType::Editor:
		return "Editor";
		break;
	case EBuildTargetType::Program:
		return "Program";
		break;
	default:
		return "Unknown";
		break;
	}
}

FString UKJHDebug_SystemInfoWidget::GetBuildConfiguration()
{
	switch (FApp::GetBuildConfiguration())
	{
	case EBuildConfiguration::Unknown:
		return "Unknown";
		break;
	case EBuildConfiguration::Debug:
		return "Debug";
		break;
	case EBuildConfiguration::DebugGame:
		return "DebugGame";
		break;
	case EBuildConfiguration::Development:
		return "Development";
		break;
	case EBuildConfiguration::Shipping:
		return "Shipping";
		break;
	case EBuildConfiguration::Test:
		return "Test";
		break;
	default:
		return "Unknown";
		break;
	}
}
