// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class SIMPLEGAME_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	int8 OverlappedItemCount;  //For the Amount of Items to overlapp events 
	bool bShouldTraceForItems; //Tracing Items for Overlaping Events

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items", meta = (AllowPrivateAccess = "true"))
	class AActor* TraceItemLastFrame; //Item We hit last frame


public:

// =============================================================================================== //
//======================== Declaration of components for the character =========================== //

UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
class USpringArmComponent* CameraBoom;

UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
class UCameraComponent* MyCamera;

FORCEINLINE UCameraComponent* GetMyCamera() const { return MyCamera; };
FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }



FORCEINLINE int8 ReturnIncrementOverlappedItemCount() const { return OverlappedItemCount; }
void IncrementOverlappedItemCount(int8 Amount); 


// =============================================================================================== //
// ============================ Overlap Events with World/ Items ================================= //

bool TraceUnderTheCrosshairs(FHitResult& OutHitResult); 
void TraceOverlap(); 


// =============================================================================================== //
// ============================ For interaction with World/Items ================================= //

void StartInteraction(); 
void EndInteraction(); 

};
