// Implemented by Leager-zju


#include "Character/RCharacterBase.h"
#include "Components/RPlayerState.h"
#include "AbilitySystemComponent.h"

// Sets default values
ARCharacterBase::ARCharacterBase()
{
  PrimaryActorTick.bCanEverTick = false;

  Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
  ensure(Weapon);

  Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
  Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ARCharacterBase::BeginPlay()
{
  Super::BeginPlay();
}

void ARCharacterBase::PossessedBy(AController* NewController)
{
  Super::PossessedBy(NewController);

  if (GASComponent)
  {
    GASComponent->InitAbilityActorInfo(this, this);
  } 
  else
  {
    InitAbilityActorInfo();
  }
}

void ARCharacterBase::OnRep_PlayerState()
{
  Super::OnRep_PlayerState();

  InitAbilityActorInfo();
}

void ARCharacterBase::InitAbilityActorInfo()
{
  if (ARPlayerState* PS = GetPlayerState<ARPlayerState>())
  {
    if (UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent())
    {
      ASC->InitAbilityActorInfo(PS, this);
    }
  }
}
