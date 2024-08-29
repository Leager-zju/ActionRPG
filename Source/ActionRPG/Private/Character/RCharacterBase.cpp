// Implemented by Leager-zju


#include "Character/RCharacterBase.h"
#include "Components/RPlayerState.h"
#include "AbilitySystemComponent.h"

ARCharacterBase::ARCharacterBase()
{
  PrimaryActorTick.bCanEverTick = false;

  Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
  ensure(Weapon);

  Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
  Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ARCharacterBase::PossessedBy(AController* NewController)
{
  Super::PossessedBy(NewController);

  InitAbilityActorInfo();
}

void ARCharacterBase::OnRep_PlayerState()
{
  Super::OnRep_PlayerState();

  InitAbilityActorInfo();
}

void ARCharacterBase::InitAbilityActorInfo()
{
  if (AbilitySystemComponent)
  {
    AbilitySystemComponent->InitAbilityActorInfo(this, this);
  }
}
