// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameManager.h"
#include "Journey_Of_HealerGameMode.generated.h"

UCLASS(minimalapi)
class AJourney_Of_HealerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AJourney_Of_HealerGameMode();

	AGameManager* gameManager;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int score;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GM", DisplayName = "king", meta = (AllowPrivateAccess = "true"))
		class AKing* king;
	UPROPERTY(EditAnywhere, Category = GM, DisplayName = "ZoneArray", meta = (AllowPrivateAccess = "true"))
		TArray<class AZone*> ZoneArray;
};



