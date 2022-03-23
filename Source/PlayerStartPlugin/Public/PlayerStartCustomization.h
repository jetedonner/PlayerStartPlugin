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
#include "SlateBasics.h"
#include "Widgets/Input/STextComboBox.h"
#include "PSWorldSettingsBase.h"
#include "IDetailCustomization.h"

class FPlayerStartCustomization: public IDetailCustomization
{
private:
 
    /* Contains references to all selected objects inside in the viewport */
    TArray<TWeakObjectPtr<UObject>> SelectedObjects;
    
public:
    
    TArray<TSharedPtr<FString>> ComboBoxOptions;
    TSharedPtr<IPropertyHandle> PlayerStartProperty;
    TSharedPtr<STextComboBox> PlayerStartComboBox;
    
    static TSharedRef<IDetailCustomization> MakeInstance();
    
    // IDetailCustomization interface
    virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
    
    void OnPlayerStartChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo);
    void OnNewActorsDropped(const TArray<UObject*>&, const TArray<AActor*>&);
    
    void ReloadPlayerStarts();
    FReply ClickedOnButton();  
};
