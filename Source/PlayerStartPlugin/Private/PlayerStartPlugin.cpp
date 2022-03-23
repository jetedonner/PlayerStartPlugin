// Copyright (c.) 2022 kimhauser.ch, DaVe Inc. (Kim David Hauser) - All rights reserved.

#include "PlayerStartPlugin.h"

#define LOCTEXT_NAMESPACE "FPlayerStartPluginModule"

void FPlayerStartPluginModule::StartupModule()
{
    // Put your module initialization code here
     UE_LOG(LogTemp, Warning, TEXT("FPlayerStartPluginModule module has started!"));
    
    FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    
    //Register the custom details panel we have created
    PropertyModule.RegisterCustomClassLayout(APSWorldSettingsBase::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FPlayerStartCustomization::MakeInstance));
    
//    GetModuleChecked
    PropertyModule.NotifyCustomizationModuleChanged();
}

void FPlayerStartPluginModule::ShutdownModule()
{
    // Put your module termination code here
    UE_LOG(LogTemp, Warning, TEXT("FPlayerStartPluginModule module has shutdown!"));
    
    if(FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
    {
        auto& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

        PropertyModule.UnregisterCustomClassLayout(APSWorldSettingsBase::StaticClass()->GetFName());
        
        PropertyModule.NotifyCustomizationModuleChanged();
    }
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FPlayerStartPluginModule, PlayerStartPlugin)
