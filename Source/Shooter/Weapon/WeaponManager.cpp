// Copyright © 2020 ruslanchudin.com


#include "WeaponManager.h"

// Sets default values for this component's properties
UWeaponManager::UWeaponManager()
{
	PrimaryComponentTick.bCanEverTick = true;
	/*SetNetAddressable();*/ // Make DSO components net addressable
	SetIsReplicated(true);
}

void UWeaponManager::BeginPlay()
{
	ParrentCharacter = Cast<AShooterCharacter>(GetOwner());
}

void UWeaponManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	/*Super::GetLifetimeReplicatedProps(OutLifetimeProps); */

	DOREPLIFETIME(UWeaponManager, CurrentWeapon);
	DOREPLIFETIME_CONDITION(UWeaponManager, MainWeapon, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UWeaponManager, SecondaryWeapon, COND_OwnerOnly);
}

void UWeaponManager::AttachWeapon()
{
	if (ParrentCharacter && CurrentWeapon && (!GetOwner()->HasAuthority() || GetNetMode() == NM_ListenServer)) {
		FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
		CurrentWeapon->AttachToComponent(ParrentCharacter->GetMesh(), rules, "weapon");
	}
}

void UWeaponManager::OnRep_CurrentWeapon()
{
	AttachWeapon();
}

void UWeaponManager::TakeWeapon(AWeapon* Weapon)
{
	if (Weapon) {
		CurrentWeapon = Weapon;
		if (GetNetMode() == NM_Standalone) {
			AttachWeapon();
		}
	}

	
	/*static ConstructorHelpers::FObjectFinder<UBlueprint> WeaponBP(TEXT("/Game/Shooter/Weapon/M16/BP_M16"));

	UWorld* World = GetWorld();
	if (World && !GetClass()) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

		AWeapon* Weapon = World->SpawnActor<AWeapon>(GetClass(), FVector(), FRotator(), SpawnParams);

		CurrentWeapon = Weapon;

	}*/
}
