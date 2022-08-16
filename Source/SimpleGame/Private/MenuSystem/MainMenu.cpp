// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSystem/MainMenu.h"

//System Includes
#include "Components/Button.h"


bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize(); 

	if (!Success)  //if the widget is initialized then we return true
	{
		return false;
	}

	//Binding of Buttons and Widget Elements;

	//Join Game
	if (!ensure(StartGameButton != nullptr)) return false; 
	StartGameButton->OnClicked.AddDynamic(this, &UMainMenu::StartGame);

	//Close Aplication
	if (!ensure(CloseGameButton != nullptr)) return false; 
	CloseGameButton->OnClicked.AddDynamic(this, &UMainMenu::CloseGame); 



	return true;
}

void UMainMenu::StartGame()
{

	UE_LOG(LogTemp, Warning, TEXT("Joining Game")); 
	if (GEngine)
	{
		FString DebugMSG = TEXT("Joining Game");
		GEngine->AddOnScreenDebugMessage(10, 2.0f, FColor::Cyan, DebugMSG,1);
	}
	 
}

void UMainMenu::CloseGame()
{
	if (GEngine)
	{
		FString MessageClosing = TEXT("Closing Game"); 
		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Emerald, MessageClosing, 1); 
	}

	//APlayerController::ConsoleCommand(quit);
}