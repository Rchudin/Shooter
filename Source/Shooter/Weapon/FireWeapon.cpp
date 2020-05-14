// Copyright © 2020 ruslanchudin.com


#include "FireWeapon.h"

void AFireWeapon::UseWeapon()
{
    if (CanBeUsed()) {

        GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("BANG!"));

        UWorld* World = GetWorld();
        if (World) {
            UseWeaponEffects();
        }

    }
}