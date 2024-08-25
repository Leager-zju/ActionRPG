// Implemented by Leager-zju


#include "Components/RPlayerState.h"
#include "Components/RPlayerController.h"
#include "Components/GAS/RGASComponent.h"
#include "Components/GAS/RGASAttributeSet.h"
#include "UI/RHUD.h"
#include "UI/Widget/RStatusBarWidget.h"


ARPlayerState::ARPlayerState()
{
  NetUpdateFrequency = 100.0f;

  AbilitySystemComponent = CreateDefaultSubobject<URGASComponent>("GAS Comp");
  ensure(AbilitySystemComponent);
  AttributeSet = CreateDefaultSubobject<URGASAttributeSet>("GAS Attribute Set");
  ensure(AttributeSet);

  AbilitySystemComponent->SetIsReplicated(true);
  AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

void ARPlayerState::BeginPlay()
{
  Super::BeginPlay();

  if (AbilitySystemComponent && AttributeSet)
  {
    SETUP_DELEGATE_HANDLE(ARPlayerState, CurHealth, AbilitySystemComponent, AttributeSet)
    SETUP_DELEGATE_HANDLE(ARPlayerState, MaxHealth, AbilitySystemComponent, AttributeSet)
    SETUP_DELEGATE_HANDLE(ARPlayerState, CurMana, AbilitySystemComponent, AttributeSet)
    SETUP_DELEGATE_HANDLE(ARPlayerState, MaxMana, AbilitySystemComponent, AttributeSet)
  }

  if (ARPlayerController* PC = Cast<ARPlayerController>(GetOwner()))
  {
    HUD = Cast<ARHUD>(PC->GetHUD());
  }
}

/* ON ATTRIBUTE CHANGED */
void ARPlayerState::OnCurHealthChanged(const FOnAttributeChangeData& Data)
{
  if (URStatusBarWidget* StatusBar = HUD->GetStatusBar())
  {
    StatusBar->SetHealthBarPercentage(Data.NewValue / GetMaxHealth());
  }
}

void ARPlayerState::OnMaxHealthChanged(const FOnAttributeChangeData& Data)
{
  if (URStatusBarWidget* StatusBar = HUD->GetStatusBar())
  {
    StatusBar->SetHealthBarPercentage(GetCurHealth() / Data.NewValue);
  }
}

void ARPlayerState::OnCurManaChanged(const FOnAttributeChangeData& Data)
{
  if (URStatusBarWidget* StatusBar = HUD->GetStatusBar())
  {
    StatusBar->SetManaBarPercentage(Data.NewValue / GetMaxMana());
  }
}

void ARPlayerState::OnMaxManaChanged(const FOnAttributeChangeData& Data)
{
  if (URStatusBarWidget* StatusBar = HUD->GetStatusBar())
  {
    StatusBar->SetManaBarPercentage(GetCurMana() / Data.NewValue);
  }
}

/* GETTER */
SETUP_GET_ATTR_IMPLEMENTATION(ARPlayerState, CurHealth, AttributeSet)
SETUP_GET_ATTR_IMPLEMENTATION(ARPlayerState, MaxHealth, AttributeSet)
SETUP_GET_ATTR_IMPLEMENTATION(ARPlayerState, CurMana, AttributeSet)
SETUP_GET_ATTR_IMPLEMENTATION(ARPlayerState, MaxMana, AttributeSet)