// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEGAME_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

	ABasePlayerController(); 

	virtual void BeginPlay() override; 
	virtual void Tick(float DeltaSeconds) override;

	void SetupInputComponent() override;

	// ============================ For the Movement of the character =============================== //
	// ===================================== Pad Movement =========================================== //

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpRate(float Rate);


	//Base Turn Rate in deg/sec, Other Scalling may affect Final turn Rate
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate = 90.0f; // Turn sides

	//BaseLookup / down rate, in degrees by sec, other scalling can affect final turn rate
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate = 90.0f; //Look Up with camera

	// ===================================== Mouse Movement ========================================== //

	//Rotate Controller base on mouse Y and Y movement
	void MouseTurn(float Rate);
	void MouseLookUp(float Rate);

	void RequestJump();


// =============================================================================================== //
//========================    Declaration of Animation montage Slote   =========================== //

	/* Montage for Firing the Weapon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UAnimMontage* HipFireMontage;

	void FireWeapon(); 


	// =================================== Crouching Movement A ===================================== //
	
	void RequestCrouch(); 
	bool bCrouching;


	// ================================= Running Movement + Stamina A ================================= //

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RunningSpeed; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float JoggingSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float Stamina; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float StaminaReduction; 

	FTimerHandle StaminaRegenerationHandle;
	FTimerHandle StaminaDegenerationHandle; 
	
	
	void RequestSprintPress(); 
	void RequestSprintRealease(); 

	void RegenerateStamina();
	void DegenerateStamina();

	bool bShouldSprint; // true when we can run, false when waiting for the timer
	void StartRunningTimer();

	bool RunButtonPressed; 

	float SpeedMultiplier;

public:

	// ================================= Crouching & Running Movement b ================================= //

	bool canCharacterJump;
	bool bIsSprinting;
	
	FORCEINLINE bool GetbCrouching() const { return bCrouching;}
	FORCEINLINE bool GetbIsSprinting() const { return bIsSprinting; }
};
