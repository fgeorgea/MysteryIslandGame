// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Libft.generated.h"


UCLASS()
class MYSTERY_ISLAND_TEST_API ULibft : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// ----- UFUNCTION -----
	// MATH
	UFUNCTION(BlueprintPure, Category = "Math")
	static void CalculateRaycastVector(AActor* Actor, float VectorLength, FVector& Start, FVector& End);

	// DEBUG
	UFUNCTION(BlueprintCallable, Category="Debug", meta = (AdvancedDisplay = 1, DevelopmentOnly = "true"))
	static void PrStr(const FString& String = "Default Debug", const float Duration = 2.0f, FLinearColor Color = FLinearColor(0.0f, 1.0f, 0.0f, 1.0f), float Size = 1.0f
	);

	// ITEM
	UFUNCTION(BlueprintPure, Category="Item", meta = (CompactNodeTitle = "Contains Item By Id"))
	static bool ContainsItemById(TArray<FSTSlot> Content, FName ItemId);

	UFUNCTION(BlueprintPure, Category="Item")
	static FSTItem GetItemById(FName ItemId);

	UFUNCTION(BlueprintPure, Category = "Item")
	static int32 GetStackSize(FName ItemId);

	UFUNCTION(BlueprintPure, Category = "Item")
	static FSTItem GetItemBySlot(FSTSlot Slot);

	UFUNCTION(BlueprintPure, Category = "Item")
	static FName GetItemIdByName(FName ItemName);

	UFUNCTION(BlueprintPure, Category = "Item")
	static FName GetItemIdByClass(TSoftClassPtr<ACppBaseInteractible> ItemClass);

	UFUNCTION(BlueprintPure, Category = "Item", meta = (DeterminesOutputType = "ComponentType"))
	static UActorComponent* GetPlayerComponent(TSubclassOf<UActorComponent> ComponentType);

private:
	static void LoadDataTable(const FString& DataTablePath = "/Game/MysteryIsland/mechanics/survivalMechanics/inventory/DTItems.DTItems");
};