// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/cameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

