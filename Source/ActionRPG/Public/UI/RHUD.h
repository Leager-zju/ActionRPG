// Implemented by Leager-zju

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RHUD.generated.h"

class URStatusBarWidget;

/**
 * 
 */
UCLASS()
class ACTIONRPG_API ARHUD : public AHUD
{
  GENERATED_BODY()

public:
  URStatusBarWidget* GetStatusBar() { return StatusBar; }

  void InitAndDraw();
	
protected:

private:
  UPROPERTY(VisibleAnywhere)
  TObjectPtr<URStatusBarWidget> StatusBar;

  UPROPERTY(EditDefaultsOnly)
  TSubclassOf<URStatusBarWidget> StatusBarClass;
};
