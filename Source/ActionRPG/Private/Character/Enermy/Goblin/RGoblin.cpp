// Implemented by Leager-zju


#include "Character/Enermy/Goblin/RGoblin.h"
#include "Components/CapsuleComponent.h"

ARGoblin::ARGoblin()
{
  GetCapsuleComponent()->SetCapsuleHalfHeight(50.0f);
  GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));
  GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
}
