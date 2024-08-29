// Implemented by Leager-zju

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "RGASAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

#define SETUP_ONREP_FUNCTION_DECLARATION(ClassName, Attr)\
		  void ClassName::OnRep_##Attr(const FGameplayAttributeData& Old##Attr) const\
		  {\
			GAMEPLAYATTRIBUTE_REPNOTIFY(ClassName, Attr, Old##Attr);\
		  }

/**
 * 
 */
UCLASS()
class ACTIONRPG_API URGASAttributeSet : public UAttributeSet
{
  GENERATED_BODY()

public:
  URGASAttributeSet();

  void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

  /**
   * PreGameplayEffectExecute -> PreAttributeBaseChange -> PreAttributeChange -> ATTRIBUTE BE CHANGED ->
   * PostAttributeChange -> ON ATTRIBUTE CHANGED -> PostAttributeBaseChange -> PostGameplayEffectExecute
   */

  /**
   * Called just before any modification happens to an attribute's base value which is modified by Instant Gameplay Effects.
   */
  void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

  /**
   * Called just after any modification happens to an attribute's base value which is modified by Instant Gameplay Effects.
   */
  void PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const override;

  /**
   * Called just before any modification happens to an attribute's current value which is modified by Duration based Gameplay Effects.
   * 
   * This function is meant to enforce things like "Health = Clamp(Health, 0, MaxHealth)" and NOT things like "trigger this extra thing if damage is applied, etc".
   */
  void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

  /**
   * Called just after any modification happens to an attribute.'s current value which is modified by Duration based Gameplay Effects.
   */
  void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

  /**
   * Called just before the Gameplay Effect is executed.
   * 
   * Return true to continue, or false to throw out the modification.
   */
  bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;

  /**
   * Called just after the Gameplay Effect is executed.
   * 
   * When PostGameplayEffectExecute() is called, changes to the Attribute have already happened,
   * but they have not replicated back to clients yet so clamping values here will not cause two network updates to clients.
   * Clients will only receive the update after clamping.
   */
  void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

public:
  UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CurHealth) FGameplayAttributeData CurHealth;
  ATTRIBUTE_ACCESSORS(URGASAttributeSet, CurHealth)
  UFUNCTION() void OnRep_CurHealth(const FGameplayAttributeData& OldCurHealth) const;

  UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth) FGameplayAttributeData MaxHealth;
  ATTRIBUTE_ACCESSORS(URGASAttributeSet, MaxHealth)
  UFUNCTION() void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
    
  UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CurMana) FGameplayAttributeData CurMana;
  ATTRIBUTE_ACCESSORS(URGASAttributeSet, CurMana)
  UFUNCTION() void OnRep_CurMana(const FGameplayAttributeData& OldCurMana) const;
  
  UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana) FGameplayAttributeData MaxMana;
  ATTRIBUTE_ACCESSORS(URGASAttributeSet, MaxMana)
  UFUNCTION() void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
};
