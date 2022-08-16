// Fill out your copyright notice in the Description page of Project Settings.


#include "items/PickUpBase.h"
#include "Components/WidgetComponent.h"

APickUpBase::APickUpBase()
	:isStackable(false)
	, canBeDiscarded(false)
	, canBeCombined(false)
	, MaxStack(200)
{

}

void APickUpBase::OnInteract_Implementation(AActor* caller)
{
	if (GEngine)
	{
		FString Message = TEXT("Destroy_Object");
		GEngine->AddOnScreenDebugMessage(1,5.0f, FColor::Red, Message,1);
	}
	Destroy();
}

void APickUpBase::OnActorStartFocus_Implementation()
{
	if (APickUpBase::GetPickupWidget())
	{
		APickUpBase::GetPickupWidget()->SetVisibility(true);
	}
}

void APickUpBase::OnActorEndFocus_Implementation()
{
	if (APickUpBase::GetPickupWidget())
	{
		APickUpBase::GetPickupWidget()->SetVisibility(false);
	}
}
