// Copyright © 2020 ruslanchudin.com

#include "Weapon.h"



// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));

	Mesh = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	if (Mesh)
	{
		Mesh->SetupAttachment(RootComponent);
		Mesh->SetWorldLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
	}

	MaxAmmo = 30;
	UseRate = 1.0f;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentAmmo = MaxAmmo;
}

void AWeapon::Trace(FHitResult& OutHit, FVector& Start, FVector& End) const
{
	OutHit = FHitResult(ForceInit);

	FCollisionQueryParams TraceParams(FName(TEXT("Fire trace")));
	TraceParams.bReturnPhysicalMaterial = true;

	UWorld* World = GetWorld();
	if (World)
	{
		World->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, TraceParams);
	}
}

void AWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeapon, CurrentAmmo);
}

void AWeapon::UseWeaponEffects_Implementation()
{
	if (!HasAuthority() || GetNetMode() == NM_Standalone) {
		if (FireAnimation && Mesh) {
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Effect"));
			
			Mesh->PlayAnimation(FireAnimation, false);
		}
	}
}

// [Server] Use
bool AWeapon::Use_Validate() { return CanBeUsed(); }
void AWeapon::Use_Implementation() { UseWeapon(); }

// [Server] StopUse
bool AWeapon::StopUse_Validate(){return true;}
void AWeapon::StopUse_Implementation(){}

bool AWeapon::CanBeUsed() const
{
	if (CurrentAmmo <= 0) {
		return false;
	}
	return true;
}