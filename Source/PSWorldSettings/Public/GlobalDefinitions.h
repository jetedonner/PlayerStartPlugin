//
//  GlobalDefinitions.h
//  UE4_PlayerStartDemo
//
//  Created by Kim David Hauser on 22.03.22.
//  Copyright © 2022 Epic Games, Inc. All rights reserved.
//

#ifndef GlobalDefinitions_h
#define GlobalDefinitions_h

#include <string.h>

DECLARE_LOG_CATEGORY_EXTERN(DaVeLog, Log, All);
DEFINE_LOG_CATEGORY(DaVeLog);

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define DAVE_LOG_GENERAL UE_LOG(DaVeLog, Warning, TEXT("%s - Line: %i - Func: %s"), *FString(__FILENAME__), __LINE__, *FString(__FUNCTION__));

#endif /* GlobalDefinitions_h */

