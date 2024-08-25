// Implemented by Leager-zju

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RStatusBarWidget.generated.h"

class UProgressBar;

/**
 * 
 */
UCLASS()
class ACTIONRPG_API URStatusBarWidget : public UUserWidget
{
  GENERATED_BODY()
	
public:
  void SetHealthBarPercentage(float Percentage);
  void SetManaBarPercentage(float Percentage);

private:
  UPROPERTY(meta = (BindWidget))
  TObjectPtr<UProgressBar> HealthBar;

  UPROPERTY(meta = (BindWidget))
  TObjectPtr<UProgressBar> ManaBar;
};
