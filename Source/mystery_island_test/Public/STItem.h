// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CppBaseInteractible.h"
#include "ENUMItemCategories.h"
#include "STItem.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct MYSTERY_ISLAND_TEST_API FSTItem : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STItem")
	TSoftClassPtr<ACppBaseInteractible>	Class = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STItem")
	FName	Name = "Please enter the item name in the data table.";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STItem")
	FText	Description = FText::FromString("Please enter the item description in the data table.");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STItem")
	TSoftObjectPtr<UTexture2D>	Icon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STItem")
	TSoftObjectPtr<UStaticMesh>	Mesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STItem")
	int32	StackSize = 16;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STItem")
	int32	Index = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STItem")
	EItemCategory	Category;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STItem")
	TMap<TSoftClassPtr<ACppBaseInteractible>, int32> Recipe;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STItem")
	bool	IsCraftable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STItem")
	bool	IsLocked = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STItem")
	TMap<FName, float>	ConsumeVitals = { {"Health", 0.0f},  {"Thirst", 0.0f}, {"Hunger", 0.0f} };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "STItem")
	float	EffectDuration = 5;
};
