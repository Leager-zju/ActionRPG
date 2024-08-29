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
  
  // ��ת�����˶�
  GetCharacterMovement()->bOrientRotationToMovement = true;
  // ����ת������
  GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
  // ���ƶ������ض�ƽ���ϵ��˶�
  GetCharacterMovement()->bConstrainToPlane = true;
  // �ڶ����ʼ��ʱ�����ᱻ������׽��ָ��ƽ����
  GetCharacterMovement()->bSnapToPlaneAtStart = true;
  
  // �������
  CameraBoom = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
  check(CameraBoom);
  FollowCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
  check(FollowCamera);

  // �󶨵�������
  CameraBoom->SetupAttachment(GetCapsuleComponent());
  CameraBoom->bUsePawnControlRotation = false;
  CameraBoom->bInheritRoll = false;
  CameraBoom->bInheritPitch = false;
  CameraBoom->bInheritYaw = false;
  CameraBoom->TargetArmLength = 750.0f;
  CameraBoom->SetRelativeRotation(FRotator(0.0f, 0.0f, -45.0f));

  // ����󶨵����ɱ�
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
