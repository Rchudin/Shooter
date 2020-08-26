// Copyright © 2020 ruslanchudin.com

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Shooter/UI/Widget/LoadingScreenInterface.h"
#include "ShooterGameInstance.generated.h"


UCLASS()
class SHOOTER_API UShooterGameInstance : public UGameInstance, public ILoadingScreenInterface
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
    class UDataTable* WeaponInstanceData;

    UPROPERTY(EditAnywhere, Category = "Widget", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<UUserWidget> LoadingScreenWidgetClass;

    UPROPERTY()
    class UUserWidget* LoadingScreenWidget;

protected:
    virtual void LoadComplete(const float LoadTime, const FString& MapName) override;

public:
    UShooterGameInstance();

    virtual void AddLoadingScreenToViewport() override;

    virtual void RemoveLoadingScreenFromViewport() override;

    /** Returns Weapon Instance Data sub object **/
    FORCEINLINE UDataTable* GetWeaponInstanceData() const { return WeaponInstanceData; }
};
