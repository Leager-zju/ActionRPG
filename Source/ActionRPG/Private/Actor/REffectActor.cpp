// Implemented by Leager-zju


#include "Actor/REffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AREffectActor::AREffectActor()
{
  PrimaryActorTick.bCanEverTick = false;

  SetRootComponent(CreateDefaultSubobject<USceneComponent>("Scene Comp"));
}

void AREffectActor::BeginPlay()
{
  Super::BeginPlay();
  
}

bool AREffectActor::ApplyEffectToTarget(AActor* TargetActor, FEffectInfo& EffectInfo, bool bMayCancelLater)
{
  UAbilitySystemComponent* ASCOfTarget = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
  if (!IsValid(ASCOfTarget) || !EffectInfo.GameplayEffectClass)
  {
    return false;
  }

  float EffectLevel = EffectInfo.EffectLevel;
  TSubclassOf<UGameplayEffect> GameplayEffectClass = EffectInfo.GameplayEffectClass;

  // ����һ�� Effect Context�����ں������� Effect
  FGameplayEffectContextHandle EffectContextHandle = ASCOfTarget->MakeEffectContext();
  // ���� Effect ��ʩ���� Source�������� Effect Context ��
  EffectContextHandle.AddSourceObject(this);

  // ���� Effect class �� Effect Context ����һ�� EffectSpec
  const FGameplayEffectSpecHandle EffectSpecHandle = ASCOfTarget->MakeOutgoingSpec(GameplayEffectClass, EffectLevel, EffectContextHandle);

  // ʩ�ӵ� Target �� ASC �ϣ�������һ�� Active Gameplay Effect Handle
  const FActiveGameplayEffectHandle ActiveEffectHandle = ASCOfTarget->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data);
  
  // �����������Ч�� Effect����Ҫ���Ӧ�� ActiveHandle���Ա���ȷִ�С�ȡ������Ϊ
  if (bMayCancelLater && EffectSpecHandle.Data->Def->DurationPolicy == EGameplayEffectDurationType::Infinite)
  {
    AddToWaitForCancel(EffectInfo, ActiveEffectHandle, ASCOfTarget);
  }
  return true;
}

void AREffectActor::OnBeginOverlap(AActor* TargetActor)
{
  for (auto&& Effect : EffectInfos)
  {
    const bool bMayCancelLater = Effect.GameplayEffectCancellationPolicy == EEffectCancellationPolicy::CancelOnEndOverlap;

    if (Effect.GameplayEffectClass && Effect.GameplayEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
    {
      ApplyEffectToTarget(TargetActor, Effect, bMayCancelLater);
    }
  }
}

void AREffectActor::OnEndOverlap(AActor* TargetActor)
{
  for (auto&& Effect : EffectInfos)
  {
    const bool bMayCancelLater = Effect.GameplayEffectCancellationPolicy == EEffectCancellationPolicy::CancelOnEndOverlap;

    if (Effect.GameplayEffectClass && Effect.GameplayEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
    {
      ApplyEffectToTarget(TargetActor, Effect, bMayCancelLater);
    }
    if (bMayCancelLater)
    {
      CancelEffect(Effect, UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
    }
  }
}

void AREffectActor::AddToWaitForCancel(FEffectInfo& EffectInfo, FActiveGameplayEffectHandle Handle, UAbilitySystemComponent* ASC)
{
  EffectInfo.WaitForCancel.Add(Handle, ASC);
}

void AREffectActor::CancelEffect(FEffectInfo& EffectInfo, UAbilitySystemComponent* ASC)
{
  if (!IsValid(ASC)) return;

  TArray<FActiveGameplayEffectHandle> WaitForRemove;
  for (auto&& Handle : EffectInfo.WaitForCancel)
  {
    const FActiveGameplayEffectHandle& ActiveHandle = Handle.Key;
    if (Handle.Value == ASC)
    {
      ASC->RemoveActiveGameplayEffect(ActiveHandle, 1);
      WaitForRemove.Add(ActiveHandle);
    }
  }

  for (auto&& NeedRemove : WaitForRemove)
  {
    EffectInfo.WaitForCancel.FindAndRemoveChecked(NeedRemove);
  }
}

