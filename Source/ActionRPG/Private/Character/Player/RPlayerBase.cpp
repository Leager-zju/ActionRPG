// Implemented by Leager-zju


#include "Character/Player/RPlayerBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/RPlayerState.h"

ARPlayerBase::ARPlayerBase()
{
  bUseControllerRotationRoll = false;
  bUseControllerRotationPitch = false;
  bUseControllerRotationYaw = false;
  GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));
  GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
  
  // 旋转朝向运动
  GetCharacterMovement()->bOrientRotationToMovement = true;
  // 设置转身速率
  GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
  // 限制对象在特定平面上的运动
  GetCharacterMovement()->bConstrainToPlane = true;
  // 在对象初始化时，它会被立即捕捉到指定平面上
  GetCharacterMovement()->bSnapToPlaneAtStart = true;
  
  // 创建组件
  CameraBoom = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
  check(CameraBoom);
  FollowCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
  check(FollowCamera);

  // 绑定到胶囊体
  CameraBoom->SetupAttachment(GetCapsuleComponent());
  CameraBoom->bUsePawnControlRotation = false;
  CameraBoom->bInheritRoll = false;
  CameraBoom->bInheritPitch = false;
  CameraBoom->bInheritYaw = false;
  CameraBoom->TargetArmLength = 750.0f;
  CameraBoom->SetRelativeRotation(FRotator(0.0f, 0.0f, -45.0f));

  // 相机绑定到弹簧臂
  FollowCamera->SetupAttachment(CameraBoom);
  FollowCamera->bUsePawnControlRotation = false;
}

void ARPlayerBase::BeginPlay()
{
  Super::BeginPlay();

  if (ARPlayerState* PS = GetPlayerState<ARPlayerState>())
  {
    AbilitySystemComponent = PS->GetAbilitySystemComponent();
    AttributeSet = PS->GetAttributeSet();
  }
}
