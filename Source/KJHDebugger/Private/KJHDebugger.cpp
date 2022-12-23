// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "KJHDebugger.h"
#include "KJHDebug_Settings.h"
#include "Developer/Settings/Public/ISettingsModule.h"
#include "UObject/Package.h"

#define LOCTEXT_NAMESPACE "FKJHDebuggerModule"

void FKJHDebuggerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "KJHDebug_Settings",
			LOCTEXT("RuntimeSettingsName", "KJHDebugger"), LOCTEXT("RuntimeSettingsDescription", "Configure KJHDebugger settings"),
			GetMutableDefault<UKJHDebug_Settings>());
	}
}

void FKJHDebuggerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "KJHDebug_Settings");
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FKJHDebuggerModule, KJHDebugger);