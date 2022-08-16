// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEGAME_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual bool Initialize(); // This is the version of Begging Play

private:

	// ========= Main Menu On Button for starting Game ======//

	UPROPERTY(meta = (BindWidget))  //To Start The Game
	class UButton* StartGameButton;
	UFUNCTION()
	void StartGame(); 

	//=======================================================//

	// ========= Main Menu On Button for starting Game ======//

	UPROPERTY(meta = (BindWidget))
	class UButton* CloseGameButton; //To Close The Game
	UFUNCTION()
	void CloseGame(); 


};
