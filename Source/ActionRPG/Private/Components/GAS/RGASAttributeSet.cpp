// Implemented by Leager-zju


#include "Components/GAS/RGASAttributeSet.h"
#include "Net/UnrealNetwork.h"

void URGASAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
  Super::GetLifetimeReplicatedProps(OutLifetimeProps);

  DOREPLIFETIME_CONDITION_NOTIFY(URGASAttributeSet, CurHealth, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(URGASAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(URGASAttributeSet, CurMana, COND_None, REPNOTIFY_Always);
  DOREPLIFETIME_CONDITION_NOTIFY(URGASAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void URGASAttributeSet::OnRep_CurHealth(const FGameplayAttributeData& OldCurHealth) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(URGASAttributeSet, CurHealth, OldCurHealth);
}

void URGASAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(URGASAttributeSet, MaxHealth, OldMaxHealth);
}

void URGASAttributeSet::OnRep_CurMana(const FGameplayAttributeData& OldCurMana) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(URGASAttributeSet, CurMana, OldCurMana);
}

void URGASAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
  GAMEPLAYATTRIBUTE_REPNOTIFY(URGASAttributeSet, MaxMana, OldMaxMana);
}
