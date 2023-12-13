// Fill out your copyright notice in the Description page of Project Settings.


#include "Libft.h"
#include "STSlot.h"
#include "STItem.h"
#include "CppBaseInteractible.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"

UDataTable* DataTable = nullptr;

void ULibft::CalculateRaycastVector(AActor* Actor, float VectorLength, FVector& Start, FVector& End)
{
	Start = FVector(0);
	End = FVector(0);
	if (Actor)
	{
		FVector ForwardVector = Actor->GetActorForwardVector() * VectorLength;
		FVector ActorLocation = Actor->GetActorLocation();
		Start = ActorLocation;
		End = ActorLocation + ForwardVector;
	}
}

void ULibft::PrStr(const FString& String, const float Duration, FLinearColor Color, float Size)
{
	GEngine->ClearOnScreenDebugMessages();
	GEngine->AddOnScreenDebugMessage(1, Duration, Color.ToFColor(true), String, true, FVector2D(Size));
}

bool ULibft::ContainsItemById(TArray<FSTSlot> Content, FName ItemId)
{
	int32 i = 0;
	int32 ContentLen = Content.Num();
	while (i < ContentLen)
	{
		if (Content[i].ItemId == ItemId)
			return (true);
	}
	return (false);
}

FSTItem ULibft::GetItemById(FName ItemId)
{
	LoadDataTable();
	if (LoadDataTable == nullptr || ItemId == "")
		return FSTItem();
	FSTItem* Item = DataTable->FindRow<FSTItem>(ItemId, "");
	if (Item)
		return (*Item);
	return FSTItem();
}

int32 ULibft::GetStackSize(FName ItemId)
{
	LoadDataTable();
	if (LoadDataTable == nullptr)
		return int32(-1);
	FSTItem* Item = DataTable->FindRow<FSTItem>(ItemId, "");
	if (Item)
		return int32(Item->StackSize);
	return int32(-1);
}

FSTItem ULibft::GetItemBySlot(FSTSlot Slot)
{
	LoadDataTable();
	if (LoadDataTable == nullptr)
		return FSTItem();
	FSTItem* Item = DataTable->FindRow<FSTItem>(Slot.ItemId, "");
	if (Item)
		return FSTItem(*Item);
	return FSTItem();
}

FName ULibft::GetItemIdByName(FName ItemName)
{
	LoadDataTable();
	if (LoadDataTable == nullptr)
		return FName("");
	TArray<FName> RowNames = DataTable->GetRowNames();
	int32 i = 0;
	int32 Len = RowNames.Num();
	while (i < Len)
	{
		if (GetItemById(RowNames[i]).Name == ItemName)
			return (RowNames[i]);
		i++;
	}
	return FName("");
}

FName ULibft::GetItemIdByClass(TSoftClassPtr<ACppBaseInteractible> ItemClass)
{
	LoadDataTable();
	if (LoadDataTable == nullptr)
		return FName("");
	TArray<FName> RowNames = DataTable->GetRowNames();
	int32 i = 0;
	int32 Len = RowNames.Num();
	while (i < Len)
	{
		if (GetItemById(RowNames[i]).Class == ItemClass)
			return (RowNames[i]);
		i++;
	}
	return FName("");
}

UActorComponent* ULibft::GetPlayerComponent(TSubclassOf<UActorComponent> ComponentType)
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GWorld, 0);
	if (PlayerCharacter == nullptr)
		return nullptr;
	TArray<UActorComponent*> Components;
	PlayerCharacter->GetComponents(Components);
	for (UActorComponent* Component : Components)
	{
		// Check if the component is of the specified type or its subclass
		if (Component->IsA(ComponentType))
		{
			return Component;
		}
	}
	return nullptr;
}

void	ULibft::LoadDataTable(const FString& DataTablePath)
{
	if (DataTable == nullptr)
		DataTable = LoadObject<UDataTable>(nullptr, *DataTablePath);
}
