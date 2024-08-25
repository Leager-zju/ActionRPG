// Implemented by Leager-zju


#include "Components/GAS/RGASAttributeSet.h"
#include "Net/UnrealNetwork.h"

URGASAttributeSet::URGASAttributeSet()
{
  InitCurHealth(100.0f);
  InitMaxHealth(100.0f);
  InitCurMana(50.0f);
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

SETUP_ONREP_FUNCTION_DECLARATION(URGASAttributeSet, CurHealth)
SETUP_ONREP_FUNCTION_DECLARATION(URGASAttributeSet, MaxHealth)
SETUP_ONREP_FUNCTION_DECLARATION(URGASAttributeSet, CurMana)
SETUP_ONREP_FUNCTION_DECLARATION(URGASAttributeSet, MaxMana)
