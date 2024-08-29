// Implemented by Leager-zju

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "RCharacterBase.generated.h"

class UAbilitySystemComponent;
class URGASAttributeSet;

/**
 * 
 */
UCLASS(Abstract)
class ACTIONRPG_API ARCharacterBase : public ACharacter, public IAbilitySystemInterface
{
  GENERATED_BODY()

public:
  ARCharacterBase();

  UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
  URGASAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
  void PossessedBy(AController*) override;
  void OnRep_PlayerState() override;

private:
  void InitAbilityActorInfo();

protected:
  UPROPERTY(EditDefaultsOnly, Category = "Apperance")
  TObjectPtr<USkeletalMeshComponent> Weapon;

  UPROPERTY(EditDefaultsOnly, Category = "GAS")
  TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

  UPROPERTY(EditDefaultsOnly, Category = "GAS")
  TObjectPtr<URGASAttributeSet> AttributeSet;
};
