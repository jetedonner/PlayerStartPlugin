// Copyright (c.) 2022 kimhauser.ch, DaVe Inc. (Kim David Hauser) - All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Input/Reply.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Editor/EditorEngine.h"
#include "Engine/Engine.h"
#include "LevelEditor.h"
#include "Editor.h"
#include "Widgets/Input/STextComboBox.h"
#include "PlayerStartWorldSettings.h"
#include "IDetailCustomization.h"

class FPlayerStartCustomization: public IDetailCustomization
{
private:
 
    /* Contains references to all selected objects inside in the viewport */
    TArray<TWeakObjectPtr<UObject>> SelectedObjects;
    
public:
    
    // IDetailCustomization interface
    virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
    
    void OnPlayerStartChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo);
    
    void ReloadPlayerStarts();
    
    void OnLevelActorAdded(AActor* AddedActor);
    void OnLevelActorDeleted(AActor* DeletedActor);
    
    FReply ClickedOnButton();

    static TSharedRef<IDetailCustomization> MakeInstance();
    
    TArray<TSharedPtr<FString>> ComboBoxOptions;
    
    TSharedPtr<IPropertyHandle> PlayerStartProperty;
    
    TSharedPtr<STextComboBox> PlayerStartComboBox;
    
};
