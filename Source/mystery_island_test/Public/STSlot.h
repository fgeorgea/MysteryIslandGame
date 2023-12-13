// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "STSLot.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct MYSTERY_ISLAND_TEST_API FSTSlot
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STSlot")
	FName	ItemId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STSlot")
	int32	Quantity;
};
