// Fill out your copyright notice in the Description page of Project Settings.


#include "items/ItemBase.h"

//System includes
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"

//Custome Includes
#include "Characters/BaseCharacter.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(MeshComp); 

	BoxComps = CreateDefaultSubobject <UBoxComponent>(TEXT("BoxComps")); 
	BoxComps->SetupAttachment(GetRootComponent()); 
	BoxComps->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxComps->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	SphereComps = CreateDefaultSubobject <USphereComponent>(TEXT("SphereComps"));
	SphereComps->SetupAttachment(GetRootComponent());

	PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
	PickupWidget->SetupAttachment(GetRootComponent()); 

}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	PickupWidget->SetVisibility(false); 
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SphereComps->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnSphereOverlapBegin);
	SphereComps->OnComponentEndOverlap.AddDynamic(this, &AItemBase::OnSphereOverlapEnd);

}

void AItemBase::OnSphereOverlapBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherComp != nullptr) && (OtherActor != this))
	{
		if (OtherActor ->GetClass() ->IsChildOf(ABaseCharacter::StaticClass()))
		{
			ABaseCharacter* MyCharacter = Cast <ABaseCharacter>(OtherActor);

			if (MyCharacter)
			{
				MyCharacter->IncrementOverlappedItemCount(1);
			}
		}

	}
}


void AItemBase::OnSphereOverlapEnd(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		ABaseCharacter* MyCharacter = Cast <ABaseCharacter>(OtherActor);
		if (MyCharacter)
		{
			MyCharacter->IncrementOverlappedItemCount(-1);
		}
	}
}