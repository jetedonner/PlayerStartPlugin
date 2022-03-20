// Copyright (c.) 2022 kimhauser.ch, DaVe Inc. (Kim David Hauser) - All rights reserved.


//#include "PlayerStartCustomization.h"
#include "PlayerStartCustomization.h"
#include "IDetailsView.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "DetailCategoryBuilder.h"
#include "Widgets/SNullWidget.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/SBoxPanel.h"
//#include "Widgets/SAssetPickerButton.h"
#include "Internationalization/Text.h"
#include "UObject/Class.h"
 
TSharedRef<IDetailCustomization> FPlayerStartCustomization::MakeInstance()
{
    return MakeShareable(new FPlayerStartCustomization);
}
 
void FPlayerStartCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
    //Edits a category. If it doesn't exist it creates a new one
    IDetailCategoryBuilder& CustomCategory = DetailBuilder.EditCategory("PlayerStart");
 
    //Store the currently selected objects from the viewport to the SelectedObjects array.
    DetailBuilder.GetObjectsBeingCustomized(SelectedObjects);
    
    PlayerStartProperty = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(APlayerStartWorldSettings, DefaultPlayerStartTag), APlayerStartWorldSettings::StaticClass());
    
    DetailBuilder.HideProperty(PlayerStartProperty);
    
    this->ReloadPlayerStarts();
    
    FString PlayerStartTagSetting;
    PlayerStartProperty->GetValue(PlayerStartTagSetting);
    
    TSharedPtr<FString> CurrentPlayerStartSharedRef;
    for(TSharedPtr<FString> item : ComboBoxOptions)
    {
        FString FSItem = *item;
        if(FSItem.Equals(PlayerStartTagSetting, ESearchCase::CaseSensitive))
        {
            UE_LOG(LogTemp, Log, TEXT("PlayerStart Found and Selected: %s"), *PlayerStartTagSetting);
            CurrentPlayerStartSharedRef = item;
            break;
        }
    }
    
    CustomCategory.AddCustomRow(FText::FromString("PlayerStart"))
        .NameContent()
        [
            SNew(STextBlock).Text(FText::FromString("Player Start"))
            .Font(IDetailLayoutBuilder::GetDetailFont())
        ]
        .ValueContent()
        .VAlign(VAlign_Center)
        .MaxDesiredWidth(250)
        [
            //SNew(STextComboBox)
            SAssignNew(PlayerStartComboBox, STextComboBox)
            .Font(IDetailLayoutBuilder::GetDetailFont())
            .OptionsSource(&ComboBoxOptions)
            .InitiallySelectedItem(CurrentPlayerStartSharedRef)
            .OnSelectionChanged(this, &FPlayerStartCustomization::OnPlayerStartChanged)
        ];
    
    
    
    CustomCategory.AddCustomRow(FText::FromString("Goto actor in level"))
//        .NameContent()
//        [
//            SNew(SAssetPickerButton)
//        ]
        .ValueContent()
        .VAlign(VAlign_Center) // set vertical alignment to center
        .MaxDesiredWidth(250)
        [
            SNew(SButton)
            .VAlign(VAlign_Center)
            .OnClicked(this, &FPlayerStartCustomization::ClickedOnButton)
            .Content()
            [
                SNew(STextBlock).Text(FText::FromString("GoTo PlayerStart"))
                .Font(IDetailLayoutBuilder::GetDetailFont())
            ]
        ];
    
    if (GEngine)
    {
        GEngine->OnLevelActorAdded().AddRaw(this, &FPlayerStartCustomization::OnLevelActorAdded);
        
        GEngine->OnLevelActorDeleted().AddRaw(this, &FPlayerStartCustomization::OnLevelActorDeleted);
    }
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION;
void FPlayerStartCustomization::InitializeWidgets()
{
//    check(FAsyncCompiler::Get() != nullptr);
    // Create the core list
//    const auto& cores = FAsyncCompiler::Get()->GetCores();
//    check(cores.Num() > 0);
//    for (const auto& core : cores)
//    {
//        CoreNames.Add(MakeShareable(new FString(core->GetName())));
//    }
//    SelectedCore = &cores[0].Get();
//    UpdateRevisionList();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION;

void FPlayerStartCustomization::OnLevelActorAdded(AActor* AddedActor)
{
    TSharedPtr<FString> SelPlayerStart = PlayerStartComboBox->GetSelectedItem();
    GLog->Log("Actor ADDED - CUSTOMIZATION!");
    this->ReloadPlayerStarts();
//    PlayerStartComboBox->SetSelectedItem(SelPlayerStart);
    
    FString PlayerStartTagSetting;
    PlayerStartProperty->GetValue(PlayerStartTagSetting);
    
    TSharedPtr<FString> CurrentPlayerStartSharedRef;
    for(TSharedPtr<FString> item : ComboBoxOptions)
    {
        FString FSItem = *item;
        if(FSItem.Equals(*SelPlayerStart, ESearchCase::CaseSensitive))
        {
            UE_LOG(LogTemp, Log, TEXT("PlayerStart Found and Selected: %s - ADD"), *PlayerStartTagSetting);
//            CurrentPlayerStartSharedRef = item;
            PlayerStartComboBox->SetSelectedItem(item);
            break;
        }
    }
}

void FPlayerStartCustomization::OnLevelActorDeleted(AActor* DeletedActor)
{
    TSharedPtr<FString> SelPlayerStart = PlayerStartComboBox->GetSelectedItem();
    GLog->Log("Actor DELETED - CUSTOMIZATION!");
    this->ReloadPlayerStarts();
//    PlayerStartComboBox->SetSelectedItem(SelPlayerStart);
    
    FString PlayerStartTagSetting;
    PlayerStartProperty->GetValue(PlayerStartTagSetting);
    
    TSharedPtr<FString> CurrentPlayerStartSharedRef;
    for(TSharedPtr<FString> item : ComboBoxOptions)
    {
        FString FSItem = *item;
        if(FSItem.Equals(*SelPlayerStart, ESearchCase::CaseSensitive))
        {
            UE_LOG(LogTemp, Log, TEXT("PlayerStart Found and Selected: %s - ADD"), *PlayerStartTagSetting);
//            CurrentPlayerStartSharedRef = item;
            PlayerStartComboBox->SetSelectedItem(item);
            break;
        }
    }
}

void FPlayerStartCustomization::ReloadPlayerStarts()
{
    GLog->Log("Reload PlayerStarts!");
    
    if(UWorld* World = GEditor->GetEditorWorldContext().World())
    {
        ComboBoxOptions.Empty();
        
        TArray<AActor*> ActorsToFind;
        UGameplayStatics::GetAllActorsOfClass(GEditor->GetEditorWorldContext().World(), APlayerStart::StaticClass(), ActorsToFind);
        
        for (AActor* PlayerStartActor: ActorsToFind)
        {
            APlayerStart* PlayerStartCast = Cast<APlayerStart>(PlayerStartActor);
            if (PlayerStartCast)
            {
                UE_LOG(LogTemp, Log, TEXT("PlayerStart Found %s"), *PlayerStartCast->GetActorLabel());
                
                TSharedPtr<FString> PlayerStartSharedRef = MakeShared<FString>(FString(PlayerStartCast->GetActorLabel()));
                
                ComboBoxOptions.Add(PlayerStartSharedRef);
            }
        }
    }
    if(PlayerStartComboBox)
    {
        PlayerStartComboBox->RefreshOptions();
    }
}

FReply FPlayerStartCustomization::ClickedOnButton()
{
    if (GEngine)
    {
        GLog->Log("ViewPortCamera goto actor!");

        if (GEditor)
        {
            TArray<AActor*> ActorsToFind;
            
            if(UWorld* World = GEditor->GetEditorWorldContext().World())
            {
                UGameplayStatics::GetAllActorsOfClass(GEditor->GetEditorWorldContext().World(), APlayerStart::StaticClass(), ActorsToFind);
                
                for (AActor* PlayerStartActor: ActorsToFind)
                {
                    APlayerStart* PlayerStartCast = Cast<APlayerStart>(PlayerStartActor);
                    if (PlayerStartCast)
                    {
                        UE_LOG(LogTemp, Log, TEXT("PlayerStart Found %s"), *PlayerStartCast->GetActorLabel());
                        
                        TSharedPtr<FString> PlayerStartSharedRef = MakeShared<FString>(FString(PlayerStartCast->GetActorLabel()));
                        
                        FString PlayerStartTagSetting;
                        PlayerStartProperty->GetValue(PlayerStartTagSetting);
                        
                        if(PlayerStartTagSetting.Equals(FString(PlayerStartCast->GetActorLabel())))
                        {
                            GEditor->MoveViewportCamerasToActor(*PlayerStartCast, true);
                            break;
                        }
                    }
                }
            }
        }
    }
    return FReply::Handled();
}

void FPlayerStartCustomization::OnPlayerStartChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo)
{
    if(NewValue)
    {
        FString FSNewValue = *NewValue;
        PlayerStartProperty->SetValue(static_cast<FString>(FSNewValue));
        
        UE_LOG(LogTemp, Log, TEXT("PlayerStart Selected: %s"), *FSNewValue);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("PlayerStart Selected: EMPTY!!"));
    }
}
