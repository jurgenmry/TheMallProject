// Fill out your copyright notice in the Description page of Project Settings.


#include "items/PickUpBase.h"

APickUpBase::APickUpBase()
	:isStackable(false)
	, canBeDiscarded(false)
	, canBeCombined(false)
	, MaxStack(200)
{

}