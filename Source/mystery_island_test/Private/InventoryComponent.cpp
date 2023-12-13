// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "STItem.h"
#include "STSLot.h"
#include "Libft.h"
#include "Engine/DataTable.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	InventorySize = 12;
	RowSize = 4;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...

}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// UTILS
int32 UInventoryComponent::FindEmptySlot(TArray<FSTSlot> Inventory)
{
	int32	i = 0;
	int32	ContentLength = Inventory.Num();
	while (i < ContentLength)
	{
		if (Inventory[i].Quantity == 0)
		{
			return int32(i);
		}
		i++;
	}
	return int32(-1);
}

int32 UInventoryComponent::FindSlot(FName ItemId, TArray<FSTSlot> Inventory)
{
	int32	i = 0;
	int32	ContentLength = Inventory.Num();
	while (i < ContentLength)
	{
		if (ItemId == Inventory[i].ItemId)
			return (i);
		i++;
	}
	return (-1);
}

int32 UInventoryComponent::FindAddableSlotById(FName ItemId, TArray<FSTSlot> Inventory)
{
	int32 i = 0;
	int32 Len = Inventory.Num();
	while (i < Len)
	{
		if (Inventory[i].ItemId == ItemId && Inventory[i].Quantity < ULibft::GetStackSize(ItemId))
			return (i);
		i++;
	}
	return (-1);
}

void UInventoryComponent::CalculateRmbQuantity(int32 Quantity, int32& SrcQuantity, int32& DstQuantity)
{
	(Quantity % 2 == 0) ? DstQuantity = Quantity / 2 : DstQuantity = (Quantity / 2) + 1;
	SrcQuantity = Quantity - DstQuantity;
}

int32 UInventoryComponent::GetItemQuantity(FName ItemId, TArray<FSTSlot> Inventory)
{
	int32 Quantity = 0;
	for (const FSTSlot& Slot : Inventory)
	{
		if (Slot.ItemId == ItemId)
			Quantity += Slot.Quantity;
	}
	return int32(Quantity);
}

void UInventoryComponent::AddToStack(int32 Index, int32 Quantity)
{
	Content[Index].Quantity += Quantity;
}

void UInventoryComponent::CreateStack(FName ItemId, int32 Quantity)
{
	int32	EmptySlotIndex = FindEmptySlot(Content);
	Content[EmptySlotIndex] = FSTSlot(ItemId, Quantity);
}

bool UInventoryComponent::InventoryHasSpace(FName ItemId, int32 Quantity)
{
	bool HasSpace = false;
	if (CalculateCanAddQuantity(ItemId) >= Quantity)
		HasSpace = true;
	return HasSpace;
}

// Checks how much an Item can be added into an inventory.
int32 UInventoryComponent::CalculateCanAddQuantity(FName ItemId)
{
	int32 StackSize = ULibft::GetStackSize(ItemId);
	int32 ContentLen = Content.Num();
	int32 i = 0;
	int32 Quantity = 0;
	while (i < ContentLen)
	{
		if (Content[i].ItemId == "")
		{
			Quantity += StackSize;
		}
		else if (Content[i].ItemId == ItemId)
		{
			Quantity += StackSize - Content[i].Quantity;
		}
		i++;
	}
	return int32(Quantity);
}

// MANIPULATION
void UInventoryComponent::SwapSlotShift(int32 Index, UInventoryComponent* DstInventory)
{
	if (DstInventory)
	{
		int32 RemainingQuantity = DstInventory->AddItem(Content[Index].ItemId, Content[Index].Quantity, true);
		RemoveItem(Index, Content[Index].Quantity - RemainingQuantity, true);
	}
}

void UInventoryComponent::SwapSlotRmb(int32 SrcIndex, int32 DstIndex, UInventoryComponent* SrcInventory)
{
	if (SrcInventory == nullptr)
		return ;
	FSTSlot& SrcSlot = SrcInventory->Content[SrcIndex];
	FSTSlot& DstSlot = Content[DstIndex];
	int32 SrcQuantity;
	int32 DstQuantity;
	CalculateRmbQuantity(SrcSlot.Quantity, SrcQuantity, DstQuantity);
	// SrcItem == DstItem
	if (SrcSlot.ItemId == DstSlot.ItemId)
	{
		int32 StackSize = ULibft::GetStackSize(SrcSlot.ItemId);
		if (DstQuantity + DstSlot.Quantity > StackSize)
		{
			SrcSlot.Quantity -= (StackSize - DstSlot.Quantity);
			DstSlot.Quantity = StackSize;
		}
		else
		{
			if (SrcQuantity == 0)
				SrcSlot.ItemId = "";
			SrcSlot.Quantity = SrcQuantity;
			DstSlot.Quantity += DstQuantity;
		}
	}
	else // SrcItem != DstItem
	{
		if (DstSlot.ItemId == "")
		{
			SrcSlot.Quantity = SrcQuantity;
			DstSlot = FSTSlot(SrcSlot.ItemId, DstQuantity);
			SrcQuantity <= 0 ? SrcSlot.ItemId = "" : SrcSlot.ItemId = SrcSlot.ItemId;
		}
		else
		{
			FSTSlot TmpSlot = SrcSlot;
			SrcSlot = DstSlot;
			DstSlot = TmpSlot;
		}
	}
	Update();
	if (SrcInventory != this)
		SrcInventory->Update();
}

void UInventoryComponent::SwapSlotLmb(int32 SrcIndex, int32 DstIndex, UInventoryComponent* SrcInventory)
{
	if (SrcInventory == nullptr)
		return ;
	FSTSlot& SrcSlot = SrcInventory->Content[SrcIndex];
	FSTSlot& DstSlot = Content[DstIndex];
	if (SrcSlot.ItemId == DstSlot.ItemId)
	{
		int32 StackSize = ULibft::GetStackSize(SrcSlot.ItemId);
		int32 ClampedValue = FMath::Clamp(SrcSlot.Quantity + DstSlot.Quantity, 0, StackSize);
		SrcSlot.Quantity -= ClampedValue - DstSlot.Quantity;
		DstSlot.Quantity = ClampedValue;
		SrcSlot.Quantity <= 0 ? SrcSlot.ItemId = "" : SrcSlot.ItemId = SrcSlot.ItemId;
	}
	else
	{
		FSTSlot TmpSlot = SrcSlot;
		SrcSlot = DstSlot;
		DstSlot = TmpSlot;
	}
	if (SrcInventory != this)
		SrcInventory->Update();
	Update();
}

// DEFAULT
void UInventoryComponent::RemoveItem(int32 Index, int32 RmQuantity, bool UpdateInventory)
{
	if (Content[Index].Quantity - RmQuantity <= 0)
		Content[Index] = FSTSlot("", 0);
	else
		Content[Index].Quantity -= RmQuantity;
	if (UpdateInventory)
		Update();
}

int32 UInventoryComponent::AddItem(FName ItemId, int32 Quantity, bool UpdateInventory)
{
	int32 QuantityLeft = Quantity;
	int32 StackSize = ULibft::GetStackSize(ItemId);
	while (QuantityLeft > 0)
	{
		int32 FoundSlotIndex = FindAddableSlotById(ItemId, Content);
		int32 FoundEmptyIndex = FindEmptySlot(Content);
		if (FoundSlotIndex != -1 && Content[FoundSlotIndex].Quantity < StackSize)
		{
			int32 CanAddOnSlot = StackSize - Content[FoundSlotIndex].Quantity;
			AddToStack(FoundSlotIndex, FMath::Clamp(CanAddOnSlot, 0, QuantityLeft));
			QuantityLeft -= FMath::Clamp(CanAddOnSlot, 0, QuantityLeft);
		}
		else if (FoundEmptyIndex != -1)
		{
			CreateStack(ItemId, FMath::Clamp(StackSize, 0, QuantityLeft));
			QuantityLeft -= FMath::Clamp(StackSize, 0, QuantityLeft);
		}
		else
		{
			if (UpdateInventory)
				Update();
			return int32(QuantityLeft);
		}
	}
	if (UpdateInventory)
		Update();
	return int32(QuantityLeft);
}

void	UInventoryComponent::Update_Implementation()
{
	OnInventoryUpdated.Broadcast();
}