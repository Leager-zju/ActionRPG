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

/**
 * 
 */
UCLASS()
class ACTIONRPG_API URGASAttributeSet : public UAttributeSet
{
  GENERATED_BODY()

public:
  void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
 
public:
  UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CurHealth)
  FGameplayAttributeData CurHealth;
 
  UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth)
  FGameplayAttributeData MaxHealth;
  
  UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CurMana)
  FGameplayAttributeData CurMana;

  UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana)
  FGameplayAttributeData MaxMana;


public:
  ATTRIBUTE_ACCESSORS(URGASAttributeSet, CurHealth)
  ATTRIBUTE_ACCESSORS(URGASAttributeSet, MaxHealth)
  ATTRIBUTE_ACCESSORS(URGASAttributeSet, CurMana)
  ATTRIBUTE_ACCESSORS(URGASAttributeSet, MaxMana)

public:
  UFUNCTION()
  void OnRep_CurHealth(const FGameplayAttributeData& OldCurHealth) const;
  
  UFUNCTION()
  void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;  

  UFUNCTION()
  void OnRep_CurMana(const FGameplayAttributeData& OldCurMana) const;

  UFUNCTION()
  void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
};
