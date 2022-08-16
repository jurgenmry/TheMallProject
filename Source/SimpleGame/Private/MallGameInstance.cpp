// Fill out your copyright notice in the Description page of Project Settings.


#include "MallGameInstance.h"

//Sytem Includes
#include "Blueprint/UserWidget.h" // for the use of widgets 
#include "UObject/ConstructorHelpers.h"


UMallGameInstance::UMallGameInstance(const FObjectInitializer& ObjectInitializer)
{

	// Creating a default Subclass but calling by string reference

	ConstructorHelpers::FClassFinder<UUserWidget>MenuBPClass(TEXT("/Game/_Game/Widgets/MainMenu_WBP"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;

	MenuClass = MenuBPClass.Class;
}

void UMallGameInstance::Init()
{
}


void UMallGameInstance::LoadMainMenuTest()
{
	//if the Main menu exist -> create it -> add to view Port
	if (!ensure(MenuClass != nullptr)) return;
	UUserWidget* Menu = CreateWidget<UUserWidget>(this, MenuClass);
	Menu->AddToViewport(); 

	if (GEngine)
	{
		FString Test = TEXT("Call Load Main Menu");
		GEngine->AddOnScreenDebugMessage(2, 2.50f, FColor::Red,Test, 1);
	}

}

void UMallGameInstance::LoadMenuBlueprintCallable()
{
	if (!ensure(MenuClass != nullptr)) return;
	UUserWidget* Menu = CreateWidget <UUserWidget>(this, MenuClass);
	Menu->AddToViewport();

	//Get A reference of the player controller
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return; 

	// Get the struct input Mode and change it to UI only
	FInputModeUIOnly InputModeData; 
	InputModeData.SetWidgetToFocus(Menu->TakeWidget()); //We need to convert widget to SWidget
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // move Mouse Outside menu

	PlayerController->SetInputMode(InputModeData); // Setting the type of input for the player controller

	PlayerController->bShowMouseCursor = true;  //Display the mouse allWays.
}