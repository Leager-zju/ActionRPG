// Implemented by Leager-zju

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RCharacterBase.generated.h"

UCLASS(Abstract)
class ACTIONRPG_API ARCharacterBase : public ACharacter
{
  GENERATED_BODY()

public:
  ARCharacterBase();

protected:
  virtual void BeginPlay() override;

  UPROPERTY(EditDefaultsOnly, Category = "Apperance")
  TObjectPtr<USkeletalMeshComponent> Weapon;
};
