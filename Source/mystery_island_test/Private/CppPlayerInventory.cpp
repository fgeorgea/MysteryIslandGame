// Fill out your copyright notice in the Description page of Project Settings.


#include "CppPlayerInventory.h"
#include "Libft.h"
#include "STItem.h"

// Utils
bool UCppPlayerInventory::PlayerInvHasSpace(FName ItemId, int32 Quantity)
{
	int32 CanAddQuantity = CalculateCanAddQuantity(ItemId) + HotbarRef->CalculateCanAddQuantity(ItemId);
	if (CanAddQuantity >= Quantity)
		return true;
	return false;
}

TArray<FSTSlot> UCppPlayerInventory::AppendPlayerInv()
{
	TArray<FSTSlot> AppendArrays = HotbarRef->Content;
	AppendArrays.Append(Content);
	return TArray<FSTSlot>(AppendArrays);
}

void UCppPlayerInventory::SplitPlayerInv(TArray<FSTSlot> AppendArray)
{
	int32 i = 0;
	int32 Len = AppendArray.Num();
	while (i < Len)
	{
		if (i <= HotbarRef->InventorySize - 1)
			HotbarRef->Content[i] = AppendArray[i];
		else
			Content[i - HotbarRef->InventorySize] = AppendArray[i];
		i++;
	}
	Update();
	HotbarRef->Update();
}

// Craft
bool UCppPlayerInventory::HasRecipe(TMap<TSoftClassPtr<ACppBaseInteractible>, int32> Recipe)
{
	TMap<TSoftClassPtr<ACppBaseInteractible>, int32> TmpRecipe = Recipe;
	bool HasRecipe = true;
	TArray<FSTSlot> AppendArray = AppendPlayerInv();
	for (TPair<TSoftClassPtr<ACppBaseInteractible>, int32>& Pair : TmpRecipe)
	{
		int32 ItemQuantity = GetItemQuantity(ULibft::GetItemIdByClass(Pair.Key), AppendArray);
		if (ItemQuantity < Pair.Value)
		{
			HasRecipe = false;
			break;
		}
	}
	SplitPlayerInv(AppendArray);
	return HasRecipe;
}

void UCppPlayerInventory::RemoveRecipe(TMap<TSoftClassPtr<ACppBaseInteractible>, int32> Recipe)
{
	TMap<TSoftClassPtr<ACppBaseInteractible>, int32> TmpRecipe = Recipe;
	if (!HasRecipe(TmpRecipe))
		return void();
	TArray<FSTSlot> AppendArray = AppendPlayerInv();
	TArray<TSoftClassPtr<ACppBaseInteractible>> Keys;
	TmpRecipe.GetKeys(Keys);
	for (TSoftClassPtr<ACppBaseInteractible> Key : Keys)
	{	
		while (TmpRecipe[Key] > 0)
		{
			int32 FoundSlot = FindSlot(ULibft::GetItemIdByClass(Key), AppendArray);
			int32 TmpQuantity = TmpRecipe[Key];
			TmpRecipe[Key] -= FMath::Clamp(AppendArray[FoundSlot].Quantity, 0, TmpQuantity);
			RemoveItemFromPlayerInv(FoundSlot, FMath::Clamp(AppendArray[FoundSlot].Quantity, 0, TmpQuantity), AppendArray, false);
		}
	}
	SplitPlayerInv(AppendArray);
	Update();
	HotbarRef->Update();
}

void UCppPlayerInventory::RemoveItemFromPlayerInv(int32 Index, int32 RmQuantity, TArray<FSTSlot>& Inventory, bool UpdateInventory)
{
	if (Inventory[Index].Quantity - RmQuantity <= 0)
		Inventory[Index] = FSTSlot("", 0);
	else
		Inventory[Index].Quantity -= RmQuantity;
}

void UCppPlayerInventory::Craft(FName ItemId, int32 QuantityToAdd, bool& Crafted)
{
	FSTItem Item = ULibft::GetItemById(ItemId);
	Crafted = false;
	if (HasRecipe(Item.Recipe))
	{
		RemoveRecipe(Item.Recipe);
		AddItemToPlayerInv(ItemId, QuantityToAdd);
		Crafted = true;
	}
}

// Default
int32 UCppPlayerInventory::AddItemToPlayerInv(FName ItemId, int32 QuantityToAdd)
{
	TArray<FSTSlot> AppendArray = AppendPlayerInv();
	int32 StackSize = ULibft::GetStackSize(ItemId);
	int32 QuantityLeft = QuantityToAdd;
	while (QuantityLeft > 0)
	{
		int32 FoundSlotIndex = FindAddableSlotById(ItemId, AppendArray);
		int32 FoundEmptyIndex = FindEmptySlot(AppendArray);
		if (FoundSlotIndex != -1 && AppendArray[FoundSlotIndex].Quantity < StackSize)
		{
			int32 CanAddOnSlot = StackSize - AppendArray[FoundSlotIndex].Quantity;
			AppendArray[FoundSlotIndex].Quantity += FMath::FMath::Clamp(CanAddOnSlot, 0, QuantityLeft);
			QuantityLeft -= FMath::Clamp(CanAddOnSlot, 0, QuantityLeft);
		}
		else if (FoundEmptyIndex != -1)
		{
			AppendArray[FoundEmptyIndex] = FSTSlot(ItemId, FMath::Clamp(StackSize, 0, QuantityLeft));
			QuantityLeft -= FMath::Clamp(StackSize, 0, QuantityLeft);
		}
		else
		{
			SplitPlayerInv(AppendArray);
			Update();
			HotbarRef->Update();
			return int32(QuantityLeft);
		}
	}
	SplitPlayerInv(AppendArray);
	Update();
	HotbarRef->Update();
	return int32(QuantityLeft);
}