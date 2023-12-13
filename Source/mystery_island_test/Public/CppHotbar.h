#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "CppHotbar.generated.h"

/**
 * 
 */
UCLASS()
class MYSTERY_ISLAND_TEST_API UCppHotbar : public UInventoryComponent
{
	GENERATED_BODY()
	
public:
	// ----- UFUNCTION -----
	// Hotbar Selection
	UFUNCTION(BlueprintCallable, Category="HotbarSelection")
	void SetEquipedItemIndex(float ScrollValue);

	UFUNCTION(BlueprintPure, Category="HotbarSelection")
	void GetEquipedItem(FSTItem& EquipedItem);

	// Default
	UFUNCTION(BlueprintCallable, Category="Default")
	void UseEquipedItem();

	UFUNCTION(BlueprintCallable, Category="Default")
	void ConsumeEquipedItem(FSTItem Item);

	// ----- UPROPERTY -----
	// Default
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HotbarSelection")
	FName EquipedItemId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HotbarSelection")
	int32 EquipedItemIndex = 0;

	virtual void Update_Implementation() override;

protected:


};
