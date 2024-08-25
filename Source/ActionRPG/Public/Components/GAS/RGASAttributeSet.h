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
