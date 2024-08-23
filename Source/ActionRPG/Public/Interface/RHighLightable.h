// Implemented by Leager-zju

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RHighLightable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URHighLightable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ACTIONRPG_API IRHighLightable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
  virtual void Highlight() = 0;
  virtual void UnHighlight() = 0;
};
