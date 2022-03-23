// Copyright (c.) 1991 - 2022 kimhauser.ch, DaVe Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PSWorldSettingsBase.h"
#include "PlayerStartGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PLAYERSTARTPLUGIN_API APlayerStartGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
    AActor* ChoosePlayerStart_Implenentation(AController* Player);
};
