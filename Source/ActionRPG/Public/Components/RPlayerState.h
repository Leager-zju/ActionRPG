// Implemented by Leager-zju

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "RPlayerState.generated.h"

#define SETUP_GET_ATTR_DECLARATION(Attr) float Get##Attr() const;
#define SETUP_GET_ATTR_IMPLEMENTATION(ClassName, Attr, AS) float ClassName::Get##Attr() const { return AS->Get##Attr(); }

#define SET_ON_CHANGED(Attr, AS)\
          FDelegateHandle On##Attr##ChangedDelegateHandle;\
          void On##Attr##Changed(const FOnAttributeChangeData& Data);\

#define GENERATE_ATTR(Attr, AS)\
          SET_ON_CHANGED(Attr, AS)\
          SETUP_GET_ATTR_DECLARATION(Attr)

#define SETUP_DELEGATE_HANDLE(ClassName, Attr, ASC, AS)\
          On##Attr##ChangedDelegateHandle =\
          ASC->GetGameplayAttributeValueChangeDelegate(AS->Get##Attr##Attribute())\
          .AddUObject(this, &ClassName::On##Attr##Changed);



class UAbilitySystemComponent;
class URGASAttributeSet;
class ARHUD;

/**
 * 
 */
UCLASS()
class ACTIONRPG_API ARPlayerState : public APlayerState, public IAbilitySystemInterface
{
  GENERATED_BODY()

public:
  ARPlayerState();

  UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; };
  URGASAttributeSet* GetAttributeSet() const { return AttributeSet; };

protected:
  virtual void BeginPlay() override;

private:
  void InitHUD();

protected:
  UPROPERTY(EditDefaultsOnly, Category = "GAS")
  UAbilitySystemComponent* AbilitySystemComponent;

  UPROPERTY(EditDefaultsOnly, Category = "GAS")
  URGASAttributeSet* AttributeSet;

  UPROPERTY(EditDefaultsOnly)
  TObjectPtr<ARHUD> HUD;

public:
  GENERATE_ATTR(CurHealth, AttributeSet)
  GENERATE_ATTR(MaxHealth, AttributeSet)
  GENERATE_ATTR(CurMana, AttributeSet)
  GENERATE_ATTR(MaxMana, AttributeSet)
};
