// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MallGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEGAME_API UMallGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UMallGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init();



	//Load Menu test
	UFUNCTION(Exec)
	void LoadMainMenuTest();

	UFUNCTION(BlueprintCallable)
	void LoadMenuBlueprintCallable();


private:

	TSubclassOf <class UUserWidget> MenuClass;


	
};
