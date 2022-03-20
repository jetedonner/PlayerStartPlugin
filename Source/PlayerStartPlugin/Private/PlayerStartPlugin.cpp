// Copyright (c.) 2022 by kimhauser.ch (Kim David Hauser), Inc. All Rights Reserved.

#include "PlayerStartPlugin.h"

#define LOCTEXT_NAMESPACE "FPlayerStartPluginModule"

void FPlayerStartPluginModule::StartupModule()
{
    // Put your module initialization code here
     UE_LOG(LogTemp, Warning, TEXT("FPlayerStartPluginModule module has started!"));
    
    FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    
    //Register the custom details panel we have created
    PropertyModule.RegisterCustomClassLayout(APlayerStartWorldSettings::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FPlayerStartCustomization::MakeInstance));
    
    if (GEngine)
    {
        GLog->Log("GEngine is NOT NULL - MODULE!");
        GEngine->OnLevelActorAdded().AddRaw(*PropertyModule, &FPlayerStartCustomization::OnLevelActorAdded);
        
        GEngine->OnLevelActorDeleted().AddRaw(*PropertyModule, &FPlayerStartCustomization::OnLevelActorDeleted);
    }
    else
    {
        GLog->Log("GEngine IS NULL - MODULE!");
    }
}

void FPlayerStartPluginModule::OnLevelActorAdded(AActor* AddedActor)
{
    GLog->Log("Actor ADDED - MODULE!");
}

void FPlayerStartPluginModule::OnLevelActorDeleted(AActor* DeletedActor)
{
    GLog->Log("Actor DELETED - MODULE!");
}

void FPlayerStartPluginModule::ShutdownModule()
{
    // Put your module termination code here
    UE_LOG(LogTemp, Warning, TEXT("FPlayerStartPluginModule module has shutdown!"));
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FPlayerStartPluginModule, PlayerStartPlugin)
