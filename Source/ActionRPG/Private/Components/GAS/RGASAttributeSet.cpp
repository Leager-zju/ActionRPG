// Implemented by Leager-zju


#include "Components/GAS/RGASAttributeSet.h"
#include "Net/UnrealNetwork.h"

URGASAttributeSet::URGASAttributeSet()
{
  InitCurHealth(50.0f);
  InitMaxHealth(100.0f);
  InitCurMana(0.0f);
  InitMaxMana(50.0f);
}

void URGASAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
  Super::GetLifetimeReplicatedProps(OutLifetimeProps);

  DOREPLIFETIME_CONDITION_NOTIFY(URGASAttributeSet, CurHealth, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(URGASAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(URGASAttributeSet, CurMana, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(URGASAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}


void URGASAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
  Super::PreAttributeBaseChange(Attribute, NewValue);
}

void URGASAttributeSet::PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const
{
  Super::PostAttributeBaseChange(Attribute, OldValue, NewValue);
}

void URGASAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
  Super::PreAttributeChange(Attribute, NewValue);

  if (Attribute == GetCurHealthAttribute())
  {
    NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
  }
  if (Attribute == GetCurManaAttribute())
  {
    NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
  }
}

void URGASAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
  Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

bool URGASAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
  Super::PreGameplayEffectExecute(Data);

  return true;
}

void URGASAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
  Super::PostGameplayEffectExecute(Data);

}

SETUP_ONREP_FUNCTION_DECLARATION(URGASAttributeSet, CurHealth)
SETUP_ONREP_FUNCTION_DECLARATION(URGASAttributeSet, MaxHealth)
SETUP_ONREP_FUNCTION_DECLARATION(URGASAttributeSet, CurMana)
SETUP_ONREP_FUNCTION_DECLARATION(URGASAttributeSet, MaxMana)