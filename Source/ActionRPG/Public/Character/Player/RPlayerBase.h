// Implemented by Leager-zju

#pragma once

#include "CoreMinimal.h"
#include "Character/RCharacterBase.h"
#include "RPlayerBase.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS(Abstract)
class ACTIONRPG_API ARPlayerBase : public ARCharacterBase
{
  GENERATED_BODY()
public:
  ARPlayerBase();

protected:
  UPROPERTY(EditDefaultsOnly, Category = "View")
  TObjectPtr<USpringArmComponent> CameraBoom;

  UPROPERTY(EditDefaultsOnly, Category = "View")
  TObjectPtr<UCameraComponent> FollowCamera;
};
