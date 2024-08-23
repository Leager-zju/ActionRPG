// Implemented by Leager-zju

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "RCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS(Abstract)
class ACTIONRPG_API ARCharacterBase : public ACharacter, public IAbilitySystemInterface
{
  GENERATED_BODY()

public:
  ARCharacterBase();

  UAbilitySystemComponent* GetAbilitySystemComponent() const override { return GASComponent; };
  UAttributeSet* GetAttributeSet() const { return GASAttributeSet; };

protected:
  virtual void BeginPlay() override;

  void PossessedBy(AController*) override;
  void OnRep_PlayerState() override;

private:
  void InitAbilityActorInfo();

protected:
  UPROPERTY(EditDefaultsOnly, Category = "Apperance")
  TObjectPtr<USkeletalMeshComponent> Weapon;

  UPROPERTY(EditDefaultsOnly, Category = "GAS")
  TObjectPtr<UAbilitySystemComponent> GASComponent;

  UPROPERTY(EditDefaultsOnly, Category = "GAS")
  TObjectPtr<UAttributeSet> GASAttributeSet;
};
