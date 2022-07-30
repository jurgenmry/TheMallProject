// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "BasePlayerController.h"

void UMyGameAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (MyCharacter == nullptr)
	{
		MyCharacter = Cast <ABaseCharacter>(TryGetPawnOwner());
	}

	if (MyPlayerController == nullptr)
	{
		MyPlayerController = Cast <ABasePlayerController>(GetWorld() ->GetFirstPlayerController()); 
	}

	if (MyCharacter && MyPlayerController)
	{
		
		bCrouching = MyPlayerController->GetbCrouching();
		bIsRunning = MyPlayerController->GetbIsSprinting(); 


		//Get Speed from character from velocity
		FVector Velocity{ MyCharacter->GetVelocity() };
		Velocity.Z = 0.0f; 
		speed = Velocity.Size();  // Get lateral speed of the velocity

		//is the character in the air
		bIsInAir = MyCharacter ->GetCharacterMovement() -> IsFalling();

		//Is the character Accelerating
		if (MyCharacter ->GetCharacterMovement() ->GetCurrentAcceleration().Size() > 0.0f)
		{
			bIsAccelarating = true; 
			
			FString Speedofchar = FString::Printf(TEXT("Speed of the character: %f"), speed);

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(1, 0.0f, FColor::White, Speedofchar);
			}

		}

		else
		{
			bIsAccelarating = false; 
			bIsRunning = false;
		}

		
		FRotator AimRotation = MyCharacter->GetBaseAimRotation(); 
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(MyCharacter->GetVelocity());
		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw; 

		/*
		FString RotationMesagge = FString::Printf(TEXT("Base Aim Rotation: %f"), AimRotation.Yaw); 
		FString MovementRotationMessage = FString::Printf(TEXT("Movement Rotation: %f"), MovementRotation.Yaw);

		
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1, 0.0f, FColor::White, RotationMesagge); 
			GEngine->AddOnScreenDebugMessage(2, 0.0f, FColor::White, MovementRotation); 
		}
		*/
	}
}

void UMyGameAnimInstance::NativeInitializeAnimation()
{
	MyCharacter = Cast <ABaseCharacter>(TryGetPawnOwner());
	MyPlayerController = Cast <ABasePlayerController>(GetWorld()->GetFirstPlayerController());
}