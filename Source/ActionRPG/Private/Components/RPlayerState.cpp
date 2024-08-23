// Implemented by Leager-zju


#include "Components/RPlayerState.h"
#include "Components/GAS/RGASComponent.h"
#include "Components/GAS/RGASAttributeSet.h"

ARPlayerState::ARPlayerState()
{
  NetUpdateFrequency = 100.0f;

  GASComponent = CreateDefaultSubobject<URGASComponent>("GAS Comp");
  ensure(GASComponent);
  GASAttributeSet = CreateDefaultSubobject<URGASAttributeSet>("GAS Attribute Set");
  ensure(GASAttributeSet);

  GASComponent->SetIsReplicated(true);
  GASComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}