// Copyright © 2020 ruslanchudin.com

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "Engine/Blueprint.h"
#include"../Character/ShooterCharacter.h"
#include "Weapon.h"
#include "Containers/Array.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Actor.h"
//#include "UObject/ConstructorHelpers.h"
#include "WeaponManager.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTER_API UWeaponManager : public UActorComponent
{
	GENERATED_BODY()
private:
	class AShooterCharacter* ParrentCharacter;

	UPROPERTY(VisibleAnywhere, Transient, ReplicatedUsing = OnRep_CurrentWeapon, Category = "Weapon")
		class AWeapon* CurrentWeapon;

	UPROPERTY(replicated)
		class AWeapon* MainWeapon;

	UPROPERTY(replicated)
		class AWeapon* SecondaryWeapon;

	UFUNCTION()
		void AttachWeapon();

	/** Called when the CurrentWepon variable gets updated */
	UFUNCTION()
		void OnRep_CurrentWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	// Sets default values for this component's properties
	UWeaponManager();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void TakeWeapon(AWeapon* Weapon);
};
