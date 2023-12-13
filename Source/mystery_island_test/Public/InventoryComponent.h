// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "STSLot.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYSTERY_ISLAND_TEST_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	//  ----- FUNCTIONS -----
	// UTILS

	UFUNCTION(BLueprintPure, Category = "Utils", meta = (Tooltip = "Returns a struct of the src and dst quantity of an item when using right click on drap 'n drop."))
	void	CalculateRmbQuantity(int32 Quantity, int32& SrcQuantity, int32& DstQuantity);

	UFUNCTION(BlueprintPure, Category="Utils")
	int32 GetItemQuantity(FName ItemId, TArray<FSTSlot> Inventory);

	UFUNCTION(BLueprintPure, Category = "Utils")
	bool	InventoryHasSpace(FName ItemId, int32 Quantity);

	UFUNCTION(BlueprintPure, Category = "Utils")
	int32 CalculateCanAddQuantity(FName ItemId);

	// UI MANIPULATION
	UFUNCTION(BlueprintCallable, Category = "InventoryManipulation")
	void SwapSlotShift(int32 Index, UInventoryComponent* DstInventory);

	UFUNCTION(BlueprintCallable, Category = "InventoryManipulation", meta = (Tooltip = "Swaps item slots when using right click on drag 'n drop operation."))
	void SwapSlotRmb(int32 SrcIndex, int32 DstIndex, UInventoryComponent* SrcInventory);

	UFUNCTION(BlueprintCallable, Category = "InventoryManipulation", meta = (Tooltip = "Swaps item slots when using left click on drag 'n drop operation."))
	void SwapSlotLmb(int32 SrcIndex, int32 DstIndex, UInventoryComponent * SrcInventory);

	// DEFAULT
	UFUNCTION(BlueprintCallable, Category = "Default")
	void RemoveItem(int32 Index, int32 RmQuantity, bool Update = false);

	UFUNCTION(BlueprintCallable, Category = "Default")
	int32 AddItem(FName ItemId, int32 QuantityToAdd, bool UpdateInventory = false);

	UFUNCTION(BlueprintNativeEvent, Category = "Events")
	void Update();

	// ----- PROPERTIES -----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Content")
	TArray<FSTSlot>	Content;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Size")
	int32	InventorySize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Size")
	int32	RowSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable")
	UDataTable* DataTable;

	// Delegates
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="EventDispatchers")
	FOnInventoryUpdated OnInventoryUpdated;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// UTILS
	UFUNCTION(Category = "Utils", meta = (Tooltip = "Returns the index of the first empty slot found in the inventory."))
	int32	FindEmptySlot(TArray<FSTSlot> Inventory);

	UFUNCTION(Category = "Utils", meta = (Tooltip = "Returns the first index that has ItemId in it. Returns -1 is no slot of ItemId kind was found."))
	int32	FindSlot(FName ItemId, TArray<FSTSlot> Inventory);

	UFUNCTION(Category = "Utils")
	void AddToStack(int32 Index, int32 Quantity);

	UFUNCTION(Category = "Utils")
	void CreateStack(FName ItemId, int32 Quantity);

	UFUNCTION(Category="Utils")
	int32 FindAddableSlotById(FName ItemId, TArray<FSTSlot> Inventory);

private:

};
