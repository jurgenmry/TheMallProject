// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "items/ItemBase.h"
#include "PickUpBase.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEGAME_API APickUpBase : public AItemBase
{

	GENERATED_BODY()

public:
	APickUpBase(); 

private:

	UPROPERTY(EditAnywhere, meta =(AllowPrivateAccess ="true"), Category ="PickupSettings")
	bool isStackable;		// to allow Items to stack
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "PickupSettings")
	bool canBeDiscarded;	// to allow throwing Picking
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "PickupSettings")
	bool canBeCombined;		// to combine with other Objects
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", ClampMin = "0", ClampMax = "200"), Category = "PickupSettings")
	int MaxStack;


public:

	FORCEINLINE bool GetIsStackable() { return isStackable; }
	FORCEINLINE bool GetCanBeDiscarded() { return canBeDiscarded; }
	FORCEINLINE bool GetCanBeCombined() { return canBeCombined; }; 
};
