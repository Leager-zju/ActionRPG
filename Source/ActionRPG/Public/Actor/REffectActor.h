// Implemented by Leager-zju

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "REffectActor.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
  DoNotApply,
  ApplyOnBeginOverlap,
  ApplyOnEndOverlap,
};

UENUM(BlueprintType)
enum class EEffectCancellationPolicy : uint8
{
  DoNotCancel,
  CancelOnEndOverlap,
};

USTRUCT(BlueprintType)
struct FEffectInfo
{
  GENERATED_BODY()

  UPROPERTY(EditAnywhere)
  float EffectLevel = 1.0f;

  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<UGameplayEffect> GameplayEffectClass;
  UPROPERTY(EditDefaultsOnly)
  EEffectApplicationPolicy GameplayEffectApplicationPolicy;
  UPROPERTY(EditDefaultsOnly)
  EEffectCancellationPolicy GameplayEffectCancellationPolicy; // Only For Infinite Effect

  TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> WaitForCancel;  // Only For Infinite Effect
};

UCLASS()
class ACTIONRPG_API AREffectActor : public AActor
{
  GENERATED_BODY()

public:
  AREffectActor();

protected:
  virtual void BeginPlay() override;

  UFUNCTION(BlueprintCallable)
  bool ApplyEffectToTarget(AActor* TargetActor, FEffectInfo& EffectInfo, bool bMayCancelLater = false);

  UFUNCTION(BlueprintCallable)
  void OnBeginOverlap(AActor* TargetActor);

  UFUNCTION(BlueprintCallable)
  void OnEndOverlap(AActor* TargetActor);

  void AddToWaitForCancel(FEffectInfo& EffectInfo, FActiveGameplayEffectHandle Handle, UAbilitySystemComponent* ASC);
  void CancelEffect(FEffectInfo& EffectInfo, UAbilitySystemComponent* ASC);

protected:
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
  bool bDestoryAfterApplication = false;

  UPROPERTY(EditDefaultsOnly, Category = "Effect")
  TArray<FEffectInfo> EffectInfos;
};