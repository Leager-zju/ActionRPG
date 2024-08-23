// Implemented by Leager-zju

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "RPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class ACTIONRPG_API ARPlayerState : public APlayerState, public IAbilitySystemInterface
{
  GENERATED_BODY()

public:
  ARPlayerState();

  UAbilitySystemComponent* GetAbilitySystemComponent() const override { return GASComponent; };
  UAttributeSet* GetAttributeSet() const { return GASAttributeSet; };

protected:

  UPROPERTY(EditDefaultsOnly, Category = "GAS")
  TObjectPtr<UAbilitySystemComponent> GASComponent;

  UPROPERTY(EditDefaultsOnly, Category = "GAS")
  TObjectPtr<UAttributeSet> GASAttributeSet;
};
