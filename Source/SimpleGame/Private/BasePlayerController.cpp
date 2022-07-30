// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "BaseCharacter.Generated.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"



ABasePlayerController::ABasePlayerController()
	:bCrouching(false)
	,Stamina(100.0f)
	,canCharacterJump(true)
	,RunningSpeed(900.0f)
	,bIsSprinting(false)
	,JoggingSpeed(250.0f)
	,StaminaReduction(10.0f)
	,bShouldSprint(true)
	,SpeedMultiplier(2.0f)
{
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay(); 

}

void ABasePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}


void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{

		//Pad Movement
		InputComponent->BindAxis(TEXT("MoveForward"), this, &ABasePlayerController::MoveForward);
		InputComponent->BindAxis(TEXT("MoveRight"), this, &ABasePlayerController::MoveRight);
		InputComponent->BindAxis(TEXT("Turn"), this, &ABasePlayerController::TurnAtRate);
		InputComponent->BindAxis(TEXT("LookUpRate"), this, &ABasePlayerController::LookUpRate);

		//Mouse Movement
		InputComponent->BindAxis("MouseTurn", this, &ABasePlayerController::MouseTurn);
		InputComponent->BindAxis("MouseLookUp", this, &ABasePlayerController::MouseLookUp);

		//Character Jump
		InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ABasePlayerController::RequestJump);

		//Character Interact
		//InputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &ABasePlayerController::RequestInteract);


		//Fire Weapons
		InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ABasePlayerController::FireWeapon);

		//Crouching
		InputComponent->BindAction("Crouch", EInputEvent::IE_Pressed, this, &ABasePlayerController::RequestCrouch);

		//Sprinting
		InputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ABasePlayerController::RequestSprintPress);
		InputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ABasePlayerController::RequestSprintRealease);
	}
}

// ============================= For the Movement of the character ================================= //
// ================================================================================================= //

void ABasePlayerController::MoveForward(float Value)
{
	if (Value != 0)
	{
		//Find Out wich way if forward
		const FRotator Rotation = GetControlRotation();     // Gets the Rotations of the controller
		const FRotator YawRotation = FRotator(0.0f, Rotation.Yaw, 0.0f);// Direction of the yaw
		const FVector Direction = FRotationMatrix{ YawRotation }.GetUnitAxis(EAxis::X);

		GetPawn()->AddMovementInput(Direction, Value);
	}
}

void ABasePlayerController::MoveRight(float Value)
{
	if (Value != 0)
	{
		//Find Out wich way if Right
		const FRotator Rotation = GetControlRotation();     // Gets the Rotations of the controller
		const FRotator YawRotation = FRotator(0.0f, Rotation.Yaw, 0.0f);// Direction of the yaw

		const FVector Direction = FRotationMatrix{ YawRotation }.GetUnitAxis(EAxis::Y);

		GetPawn()->AddMovementInput(Direction, Value);
	}
}

// ====================== For the Movement of the character Camera  ================================ //
// ================================================================================================= //


void ABasePlayerController::TurnAtRate(float Rate)
{
	AddYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABasePlayerController::LookUpRate(float Rate)
{
	AddPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}


//Pending

void ABasePlayerController::MouseTurn(float Rate)
{

}  

void ABasePlayerController::MouseLookUp(float Rate)
{
}


// =================================== For the  character Jumping  ================================= //
// ================================================================================================= //
void ABasePlayerController::RequestJump()
{
	
	if (GetCharacter())
	{
		if (canCharacterJump == true)
		{
			GetCharacter()->Jump();
		}
		else if (canCharacterJump == false)
		{
			GetCharacter()->StopJumping();
		}
	}
}



// =================================== For the character firing weapons ============================ //
// ================================================================================================= //
void ABasePlayerController::FireWeapon()
{
	//Sound
	//Muzzelflash

	UAnimInstance* AnimInstance = GetCharacter()->GetMesh()->GetAnimInstance(); 
	if (AnimInstance && HipFireMontage)
	{
		AnimInstance->Montage_Play(HipFireMontage);
		AnimInstance->Montage_JumpToSection(FName("StartFire"));
		/*
		FString DebusgMsg = TEXT("In Anim Instance"); 
		GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Red, DebusgMsg);
		*/	
	}
}



// =================================== For the character crouching  ================================ //
// ================================================================================================= //
void ABasePlayerController::RequestCrouch()
{
	if (!GetCharacter() ->GetCharacterMovement() ->IsFalling())
	{
		bCrouching = !bCrouching; 
	}
}



// =================================== For the character Sprinting  ================================ //
// ================================================================================================= //

void ABasePlayerController::RequestSprintPress()
{
	
	if (Stamina >= 20.0f && !GetCharacter()->GetCharacterMovement()->IsFalling() && !bCrouching)
	{
		RunButtonPressed = true;// test Line
		bIsSprinting = true;
		bShouldSprint = true;
		StartRunningTimer();
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = FMath::Clamp(SpeedMultiplier, RunningSpeed, JoggingSpeed);
		//Check this bug
	}
	else
	{
		RunButtonPressed = true; // test line
		bIsSprinting = false;
		bShouldSprint = false;
		StartRunningTimer();
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = JoggingSpeed;
	}
}

void ABasePlayerController::RequestSprintRealease()
{
	RunButtonPressed = false;

	StartRunningTimer(); //test

	bIsSprinting = false;
	bShouldSprint = false;
	StartRunningTimer();

	GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = JoggingSpeed;
	//InterpolateSpeed();

	//FString RotationMesaggesss = FString::Printf(TEXT("Button Was released"));
	//GEngine->AddOnScreenDebugMessage(16, 10.0f, FColor::White, RotationMesaggesss);
}

// ================================ For the Stamina System for Sprinting =========================== //
// ================================================================================================= //

void  ABasePlayerController::StartRunningTimer()
{
	if (bShouldSprint)
	{
		//bShouldSprint = false;
		GetWorld()->GetTimerManager().SetTimer(StaminaDegenerationHandle,
			this, &ABasePlayerController::DegenerateStamina,
			1.0f, true);

		GetWorld()->GetTimerManager().PauseTimer(StaminaRegenerationHandle);
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(StaminaRegenerationHandle,
			this, &ABasePlayerController::RegenerateStamina,
			1.0f, true);

		GetWorld()->GetTimerManager().PauseTimer(StaminaDegenerationHandle);
	}
}

void ABasePlayerController::RegenerateStamina()
{
	if (Stamina >= 100.0f)
	{
		Stamina = 100.0f; 

		GetWorld()->GetTimerManager().PauseTimer(StaminaDegenerationHandle); 
		GetWorld()->GetTimerManager().PauseTimer(StaminaRegenerationHandle); 
	}

	else
	{
		++Stamina; 
		FString RotationMesaggesss = FString::Printf(TEXT("The regen current Stamina is:  %f"), Stamina);
		GEngine->AddOnScreenDebugMessage(16, 10.0f, FColor::White, RotationMesaggesss);
	}
}

void ABasePlayerController::DegenerateStamina()
{
	if (Stamina <= 0.0f)
	{
		Stamina = 0.0f;
		FString RotationMesaggesss = FString::Printf(TEXT("The current dege  Stamina is:  %f"), Stamina);
		GEngine->AddOnScreenDebugMessage(17, 10.0f, FColor::White, RotationMesaggesss);

		GetWorld()->GetTimerManager().PauseTimer(StaminaDegenerationHandle); //test line
	}

	else
	{
		Stamina = Stamina - StaminaReduction;

		if (Stamina <= 20.0f) // || RunButtonPressed == false)
		{
			GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 300.0f; //works test
			//InterpolateSpeed(); 
		}

		FString RotationMesaggesss = FString::Printf(TEXT("The current dege 2 Stamina is:  %f"), Stamina);
		GEngine->AddOnScreenDebugMessage(18, 10.0f, FColor::White, RotationMesaggesss);
	}
}

