// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "items/ItemBase.h"
#include "items/InteractInterface.h" // Interface
#include "items/StructsItems.h"
#include "PickUpBase.generated.h"

/**
 * 
 */

UCLASS()
class SIMPLEGAME_API APickUpBase : public AItemBase, public IInteractInterface
{

	GENERATED_BODY()

public:
	APickUpBase(); 

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "PickupSettings")
	FItemData ItemData; // Struct for the data structure

	//Interface Methods

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void OnInteract(AActor* caller);
	virtual void OnInteract_Implementation(AActor* caller);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void OnActorStartFocus();
	virtual void OnActorStartFocus_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void OnActorEndFocus();
	virtual void OnActorEndFocus_Implementation(); 

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
