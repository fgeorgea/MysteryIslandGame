// Fill out your copyright notice in the Description page of Project Settings.


#include "CppHotbar.h"
#include "STItem.h"
#include "Libft.h"

// BeginPlay

void UCppHotbar::Update_Implementation()
{
	Super::Update_Implementation();

	EquipedItemId = Content[EquipedItemIndex].ItemId;
}

// Hotbar Selection
void UCppHotbar::SetEquipedItemIndex(float ScrollValue)
{
	int32 TmpValue = -1;
	if (ScrollValue == 1)
		TmpValue = 1;
	TmpValue += EquipedItemIndex;
	if (TmpValue < 0)
		EquipedItemIndex = InventorySize - 1;
	else
		TmpValue >= InventorySize ? EquipedItemIndex = 0 : EquipedItemIndex = TmpValue;
	EquipedItemId = Content[EquipedItemIndex].ItemId;
}

void UCppHotbar::GetEquipedItem(FSTItem& EquipedItem)
{
	if (EquipedItemId != "")
	{
		FSTItem Item = ULibft::GetItemBySlot(Content[EquipedItemIndex]);
		EquipedItem = Item;
	}
}

// Default
void UCppHotbar::UseEquipedItem()
{
	if (EquipedItemId == "")
		return;
	FSTItem EquipedItem;
	GetEquipedItem(EquipedItem);
	EItemCategory ItemCategory = EquipedItem.Category;
	switch (ItemCategory)
	{
		case EItemCategory::Consumable:
			ConsumeEquipedItem(EquipedItem);
			break;
		case EItemCategory::Tool:
			ULibft::PrStr("USE TOOL.");
			break;
		case EItemCategory::QuicksandBuoyancyDevice:
			ULibft::PrStr("QuickSand use.");
			break;
		default:
			break;
	}
}

void UCppHotbar::ConsumeEquipedItem(FSTItem Item)
{
	// Use vital decrease here.
	RemoveItem(EquipedItemIndex, 1, true);
}