// Implemented by Leager-zju


#include "Character/RCharacterBase.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ARCharacterBase::ARCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));

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

