#pragma once

#include "CoreMinimal.h"

#include "StructsItems.generated.h"

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<class APickUpBase> ItemClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class UTexture2D* ItemImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float ItemCost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 Value;
};
