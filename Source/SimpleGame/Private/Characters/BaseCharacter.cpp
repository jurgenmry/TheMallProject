// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"

//System Includes
#include "GameFramework/SpringArmComponent.h"
#include "Camera/cameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

//Custome Includes

#include "items/InteractInterface.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//====================== Creation of Camera Bomm and its settings =====================//

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SocketOffset = FVector(0.0f, 50.0f, 70.0f);

	//====================== Creation of Camera  and its settings =========================//

	MyCamera = CreateDefaultSubobject <UCameraComponent>(TEXT("MyCamera"));
	MyCamera->SetupAttachment(CameraBoom);
	MyCamera->bUsePawnControlRotation = true;


	// Dont rotate when the control rotates.  Let the controller only affect the camera

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true; 
	bUseControllerRotationRoll = false; 

	//Configure Character Movement
	GetCharacterMovement() ->bOrientRotationToMovement = true;  // Character moves in the direction of input
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 300.0f;             
	GetCharacterMovement()->AirControl = 0.2f;


	bShouldTraceForItems = false;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()                                                                                    
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	TraceOverlap(); 
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


// =============================================================================================== //
//==================== For the  Overlap Events with Items / interactables ======================== //

void ABaseCharacter::IncrementOverlappedItemCount(int8 Amount)
{
	if (OverlappedItemCount + Amount <= 0)
	{
		OverlappedItemCount = 0;
		bShouldTraceForItems = false;
	}

	else
	{
		OverlappedItemCount+= Amount;
		bShouldTraceForItems = true;
	}
}

bool ABaseCharacter::TraceUnderTheCrosshairs(FHitResult& OutHitResult)
{
	// check if we have a viewport
	FVector2D ViewPortSize; 
	if (GEngine && GEngine ->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewPortSize);
	}

	//check the Screen space Location and Direction
	FVector2D CenterOftheScreenLocation(ViewPortSize.X / 2.0f, ViewPortSize.Y / 2.0f);
	FVector WorldPositionCenter;
	FVector WorldDirectionCenter;

	bool ScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(
		UGameplayStatics::GetPlayerController(this, 0), CenterOftheScreenLocation,
		WorldPositionCenter, WorldDirectionCenter);

	if (ScreenToWorld)
	{
		const FVector StartLocation{WorldPositionCenter};
		const FVector EndLocation{ StartLocation + WorldDirectionCenter * 500.0f };
		GetWorld()->LineTraceSingleByChannel(
			OutHitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility);
		DrawDebugLine(GetWorld(),StartLocation,EndLocation, FColor::Red, false, 1, 0, 1);

		if (OutHitResult.bBlockingHit)
		{
			return true;
		}
	}

	return false;
}

void ABaseCharacter::TraceOverlap()
{
	if (bShouldTraceForItems)
	{
		FHitResult ItemTrace; 
		TraceUnderTheCrosshairs(ItemTrace);
		if (ItemTrace.bBlockingHit)
		{
			AActor* Interactable = ItemTrace.GetActor(); 
			if (Interactable != TraceItemLastFrame)
			{
				if (TraceItemLastFrame)
				{
					IInteractInterface* Interface = Cast<IInteractInterface>(TraceItemLastFrame);
					if (Interface)
					{
						Interface->Execute_OnActorEndFocus(TraceItemLastFrame);  //Set Visibility (true)
					}
				}

				IInteractInterface* InterFace = Cast<IInteractInterface>(Interactable);
				if (InterFace)
				{
					InterFace->Execute_OnActorStartFocus(Interactable);
				}

				TraceItemLastFrame = Interactable;
			}
		}

		else if (TraceItemLastFrame)
		{
			IInteractInterface* Interface = Cast<IInteractInterface>(TraceItemLastFrame);
			if (Interface)
			{
				Interface->Execute_OnActorEndFocus(TraceItemLastFrame); 
			}

			TraceItemLastFrame = nullptr; 
		}
	}

	else if (TraceItemLastFrame)
	{
		IInteractInterface* Interface = Cast<IInteractInterface>(TraceItemLastFrame);
		if (Interface)
		{
			Interface->Execute_OnActorEndFocus(TraceItemLastFrame);
		}
		TraceItemLastFrame = nullptr;
	}
}



//================================================================================================ //
//================================== For interaction with World/Items ============================ //

void ABaseCharacter::StartInteraction()
{
	if (TraceItemLastFrame)
	{
		IInteractInterface* Interface = Cast<IInteractInterface>(TraceItemLastFrame);
		if (Interface)
		{
			Interface->Execute_OnInteract(TraceItemLastFrame, this);
		}
	}
}

void ABaseCharacter::EndInteraction()
{
	// remove the pointer 
}
