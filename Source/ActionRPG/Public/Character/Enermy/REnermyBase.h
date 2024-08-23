// Implemented by Leager-zju

#pragma once

#include "CoreMinimal.h"
#include "Character/RCharacterBase.h"
#include "Interface/RHighLightable.h"
#include "REnermyBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class ACTIONRPG_API AREnermyBase : public ARCharacterBase, public IRHighLightable
{
  GENERATED_BODY()

public:
  AREnermyBase();

public:
  void Highlight() override;
  void UnHighlight() override;
};
