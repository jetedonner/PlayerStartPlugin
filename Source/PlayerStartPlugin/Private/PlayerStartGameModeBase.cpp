// Copyright (c.) 1991 - 2022 kimhauser.ch, DaVe Inc. All rights reserved.


#include "PlayerStartGameModeBase.h"

AActor* APlayerStartGameModeBase::ChoosePlayerStart_Implenentation(AController* Player)
{
    GLog->Log("ChoosePlayerStart_Implenentation => FIRST CALL");
    if(Player)
    {
        UWorld* World = Player->GetPawn()->GetWorld();
        if(World)
        {
            
            APSWorldSettingsBase* PlayerStartWorldSettings = Cast<APSWorldSettingsBase>(World->GetWorldSettings());
            
            if(PlayerStartWorldSettings)
            {
                if (GEngine)
                {
                    GLog->Log("ChoosePlayerStart_Implenentation!");

                    if (GEditor)
                    {
                        TArray<AActor*> ActorsToFind;
                        
//                        if(UWorld* World = GEditor->GetEditorWorldContext().World())
//                        {
                            UGameplayStatics::GetAllActorsOfClass(GEditor->GetEditorWorldContext().World(), APlayerStart::StaticClass(), ActorsToFind);
                            
                            for (AActor* PlayerStartActor: ActorsToFind)
                            {
                                APlayerStart* PlayerStartCast = Cast<APlayerStart>(PlayerStartActor);
                                if (PlayerStartCast)
                                {
                                    UE_LOG(LogTemp, Log, TEXT("PlayerStart Found %s"), *PlayerStartCast->GetActorLabel());
                                    
                                    TSharedPtr<FString> PlayerStartSharedRef = MakeShared<FString>(FString(PlayerStartCast->GetActorLabel()));
                                    
                                    FString PlayerStartTagSetting = PlayerStartWorldSettings->DefaultPlayerStartTag;
//                                    PlayerStartProperty->GetValue(PlayerStartTagSetting);
                                    
                                    if(PlayerStartTagSetting.Equals(FString(PlayerStartCast->GetActorLabel())))
                                    {
                                        UE_LOG(LogTemp, Log, TEXT("ChoosePlayerStart_Implenentation => PlayerStart Found %s"), *PlayerStartCast->GetActorLabel());
                                        return PlayerStartCast;
//                                        GEditor->MoveViewportCamerasToActor(*PlayerStartCast, true);
//                                        break;
                                    }
                                }
                            }
//                        }
                    }
                }
            }
            else
            {
                UE_LOG(LogTemp, Log, TEXT("APlayerStartGameModeBase::ChoosePlayerStart_Implenentation => PlayerStartWorldSettings IS NULL (Couldnt be casted)!"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("APlayerStartGameModeBase::ChoosePlayerStart_Implenentation => World IS NULL!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("APlayerStartGameModeBase::ChoosePlayerStart_Implenentation => Player IS NULL!"));
    }
    return NULL;
}
