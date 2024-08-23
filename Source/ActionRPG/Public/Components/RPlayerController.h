// Implemented by Leager-zju

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class IRHighLightable;

/**
 * 
 */
UCLASS()
class ACTIONRPG_API ARPlayerController : public APlayerController
{
  GENERATED_BODY()

public:
  ARPlayerController();

protected:
  void BeginPlay() override;

  void PlayerTick(float DeltaTime) override;

  void SetupInputComponent() override;

private:
  void CursorTrace();
  IRHighLightable* Last;
  IRHighLightable* Cur;

private:
  UPROPERTY(EditDefaultsOnly, Category = "Input")
  TObjectPtr<UInputMappingContext> PlayerInputCtx;

  UPROPERTY(EditDefaultsOnly, Category = "Input")
  TObjectPtr<UInputAction> MoveAction;

  void Move(const struct FInputActionValue&);
};
