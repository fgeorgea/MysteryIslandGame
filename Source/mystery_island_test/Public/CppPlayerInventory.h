// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "CppPlayerInventory.generated.h"

/**
 * 
 */
UCLASS()
class MYSTERY_ISLAND_TEST_API UCppPlayerInventory : public UInventoryComponent
{
	GENERATED_BODY()
	
public:

	// ----- UFUNCTION -----
	// UTILS
	UFUNCTION(BlueprintPure, Category = "Utils", meta = (Tooltip = "Checks wether the player inv can receive a quantity of a given ItemId."))
	bool PlayerInvHasSpace(FName ItemId, int32 Quantity);

	UFUNCTION(BlueprintPure, Category="Utils", meta = (Tooltip = "Append the 2 player inventories into a new big one.", CompactNodeTitle = "AppendInventories"))
	TArray<FSTSlot> AppendPlayerInv();

	UFUNCTION(BlueprintCallable, Category = "Utils", meta = (Tooltip = "Takes an array and splits them into the player main inventory and the player hotbar."))
	void SplitPlayerInv(TArray<FSTSlot> AppendArray);

	// Crafting
	UFUNCTION(Blueprintpure, Category = "Crafting", meta = (Tooltip = "Checks if player inv has recipie."))
	bool HasRecipe(TMap<TSoftClassPtr<ACppBaseInteractible>, int32> Recipe);

	UFUNCTION(BlueprintCallable, Category="Crafting")
	void RemoveRecipe(TMap<TSoftClassPtr<ACppBaseInteractible>, int32> Recipe);

	UFUNCTION(BlueprintCallable, Category="Crafting")
	void RemoveItemFromPlayerInv(int32 Index, int32 RmQuantity, TArray<FSTSlot>& Inventory, bool UpdateInventory);

	UFUNCTION(BlueprintCallable, Category="Crafting")
	void Craft(FName ItemId, int32 QuantityToAdd, bool& Crafted);

	// DEFAULT
	UFUNCTION(BlueprintCallable, Category="Default", meta = (Tooltip = "Adds ItemId of a certain quantity to player inventories. Returns the remaining quantity."))
	int32 AddItemToPlayerInv(FName ItemId, int32 QuantityToAdd);


	// ----- UPROPERTY -----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	UInventoryComponent* HotbarRef;
};
