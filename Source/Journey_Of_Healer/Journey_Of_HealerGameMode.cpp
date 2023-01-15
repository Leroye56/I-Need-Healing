// Copyright Epic Games, Inc. All Rights Reserved.

#include "Kismet/GameplayStatics.h"
#include "Journey_Of_HealerGameMode.h"
#include "Journey_Of_HealerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AJourney_Of_HealerGameMode::AJourney_Of_HealerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	TArray<AActor*> actorGM;
	TSubclassOf<AGameManager> classToFind = AGameManager::StaticClass();;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, actorGM);

	if (actorGM.Num() != 0)
	{
		gameManager = Cast<AGameManager>(actorGM.Last());
		score = gameManager->Score;
	}
}
