// Copyright (c.) 1991 - 2022 kimhauser.ch, DaVe Inc. All rights reserved.


#include "PlayerStartGameModeBase.h"

AActor* APlayerStartGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
    GLog->Log("ChoosePlayerStart_Implementation => FIRST CALL");
    if(Player)
    {
        if(Player->GetWorld())
        {
            UWorld* World = Player->GetWorld();
            
            if(World)
            {
                APSWorldSettingsBase* PlayerStartWorldSettings = Cast<APSWorldSettingsBase>(World->GetWorldSettings());
                
                if(PlayerStartWorldSettings)
                {
                    GLog->Log("ChoosePlayerStart_Implementation!");

                    TArray<AActor*> ActorsToFind;
                    UGameplayStatics::GetAllActorsOfClass(World, APlayerStart::StaticClass(), ActorsToFind);
                    
                    for (AActor* PlayerStartActor: ActorsToFind)
                    {
                        APlayerStart* PlayerStartCast = Cast<APlayerStart>(PlayerStartActor);
                        if (PlayerStartCast)
                        {
                            UE_LOG(LogTemp, Log, TEXT("PlayerStart Found %s"), *PlayerStartCast->GetActorLabel());
                            
                            TSharedPtr<FString> PlayerStartSharedRef = MakeShared<FString>(FString(PlayerStartCast->GetActorLabel()));
                            
                            FString PlayerStartTagSetting = PlayerStartWorldSettings->DefaultPlayerStartTag;
                            
                            if(PlayerStartTagSetting.Equals(FString(PlayerStartCast->GetActorLabel())))
                            {
                                UE_LOG(LogTemp, Log, TEXT("ChoosePlayerStart_Implementation => PlayerStart Found %s"), *PlayerStartCast->GetActorLabel());
                                return PlayerStartCast;
                            }
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
            GLog->Log("ChoosePlayerStart_Implementation => GetWorld() IS NULL");
        }
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("APlayerStartGameModeBase::ChoosePlayerStart_Implenentation => Player IS NULL!"));
    }
    return NULL;
}
