// Copyright (c.) 2022 kimhauser.ch, DaVe Inc. (Kim David Hauser) - All rights reserved.

#include "PSWorldSettings.h"

//DEFINE_LOG_CATEGORY(DaVeLog);

#define LOCTEXT_NAMESPACE "FPSWorldSettingsModule"

//#define RH_LOG_PARAM(pn, pv) UE_LOG(RHLogGeneral, Warning, TEXT("%s - R%i - %s - %s:%s"), __FILENAME__, __LINE__, __FUNCTION__, pn, pv);

void FPSWorldSettingsModule::StartupModule()
{
    // Put your module initialization code here
    UE_LOG(LogTemp, Warning, TEXT("FPSWorldSettingsModule module has started!"));
    
//    UE_LOG(LogTemp, Warning, TEXT("TESET DaVeLog: %s"), *FString(__FUNCTION__));

    DAVE_LOG_GENERAL;
    
//    RH_LOG_PARAM(TEXT("FPSWorldSettingsModule"), *InstigatorPawn->GetName());
    
//    FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
//
//    //Register the custom details panel we have created
//    PropertyModule.RegisterCustomClassLayout(APlayerStartWorldSettings::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FPlayerStartCustomization::MakeInstance));
}

void FPSWorldSettingsModule::ShutdownModule()
{
    // Put your module termination code here
    UE_LOG(LogTemp, Warning, TEXT("FPSWorldSettingsModule module has shutdown!"));
    
//    if(FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
//    {
//        auto& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
//
//        PropertyModule.UnregisterCustomClassLayout(APlayerStartWorldSettings::StaticClass()->GetFName());
//    }
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FPSWorldSettingsModule, PSWorldSettings)
