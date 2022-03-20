// Copyright (c.) 2022 kimhauser.ch, DaVe Inc. (Kim David Hauser) - All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "PlayerStartWorldSettings.generated.h"

UCLASS()
class PLAYERSTARTPLUGIN_API APlayerStartWorldSettings : public AWorldSettings
{
    GENERATED_BODY()
    
public:
    APlayerStartWorldSettings();
    
protected:
    virtual void BeginPlay() override;
    
public:
    
    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="PlayerStart", meta=(AllowPrivateAccess = "true"))
    FString DefaultPlayerStartTag;

};
