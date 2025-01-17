// Implemented by Leager-zju


#include "Character/Enermy/REnermyBase.h"
#include "Components/GAS/RGASComponent.h"
#include "Components/GAS/RGASAttributeSet.h"

AREnermyBase::AREnermyBase()
{
  GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
  GetMesh()->CustomDepthStencilValue = 250.0f;

  Weapon->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
  Weapon->CustomDepthStencilValue = 250.0f;

  AbilitySystemComponent = CreateDefaultSubobject<URGASComponent>("GAS Comp");
  ensure(AbilitySystemComponent);
  AttributeSet = CreateDefaultSubobject<URGASAttributeSet>("GAS Attribute Set");
  ensure(AttributeSet);

  AbilitySystemComponent->SetIsReplicated(true);
  AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

void AREnermyBase::Highlight()
{
  GetMesh()->SetRenderCustomDepth(true);
  Weapon->SetRenderCustomDepth(true);
}

void AREnermyBase::UnHighlight()
{
  GetMesh()->SetRenderCustomDepth(false);
  Weapon->SetRenderCustomDepth(false);
}
