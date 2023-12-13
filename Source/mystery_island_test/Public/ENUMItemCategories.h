// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ENUMItemCategories.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	Default = 0 UMETA(DisplayName = "Default"),
	Consumable = 1 UMETA(DisplayName = "Consumable"),
	Tool = 2 UMETA(DisplayName = "Tool"),
	QuicksandBuoyancyDevice = 3 UMETA(DisplayName = "QuicksandBuoyancyDevice")
};
