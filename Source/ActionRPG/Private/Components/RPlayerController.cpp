// Implemented by Leager-zju


#include "Components/RPlayerController.h"
#include "Interface/RHighLightable.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ARPlayerController::ARPlayerController()
{
  bReplicates = true; // �ÿ�������ʵ������������Ϸ�н��и��ƣ��Ա��ڲ�ͬ�ͻ���֮��ͬ����������״̬����Ϊ
}

void ARPlayerController::BeginPlay()
{
  Super::BeginPlay();

  // ���� IMC �����ȼ�(0)
  UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
  // check �걣֤�����ָ��ǿ�
  check(SubSystem);
  check(PlayerInputCtx);
  SubSystem->AddMappingContext(PlayerInputCtx, 0);

  // ��ʾ���
  bShowMouseCursor = true;
  // ���������ʽ
  DefaultMouseCursor = EMouseCursor::Default;

  FInputModeGameAndUI InputMode;
  // ����ҽ�����ƶ�����Ļ��Եʱ����Ϸ������ֹ������뿪��Ϸ����
  InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
  // �����ڲ������ʱ�����������
  // ���и��ߵ����ȼ��������ڲ����������ʱ���� bShowMouseCursor ���趨
  InputMode.SetHideCursorDuringCapture(false);
  SetInputMode(InputMode);
}

void ARPlayerController::PlayerTick(float DeltaTime)
{
  Super::PlayerTick(DeltaTime);

  CursorTrace();
}

void ARPlayerController::SetupInputComponent()
{
  Super::SetupInputComponent();

  // �� Move() �󶨵� Action �ϣ�CastChecked ��֤����ǿ�
  UEnhancedInputComponent* EnhancedInputComp = CastChecked<UEnhancedInputComponent>(InputComponent);
  EnhancedInputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARPlayerController::Move);
}

void ARPlayerController::CursorTrace()
{
  FHitResult CursorHit;
  if (!GetHitResultUnderCursor(ECC_Visibility, false, CursorHit)) return;

  Last = Cur;
  Cur = Cast<IRHighLightable>(CursorHit.GetActor());

  if (Last == Cur) return;
  if (Last) Last->UnHighlight();
  if (Cur) Cur->Highlight();
}

void ARPlayerController::Move(const FInputActionValue& Value)
{
  // ���ݿ�����ƫ�ǣ���ȡ xOy ƽ���ϵķ�������
  const FRotator& GroundRotation = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
  const FRotationMatrix& GroundRotationMatrix(GroundRotation);

  const FVector& ForwardVector = GroundRotationMatrix.GetUnitAxis(EAxis::X);
  const FVector& RightVector = GroundRotationMatrix.GetUnitAxis(EAxis::Y);

  // ����ֵ�е� X Ӧ�õ�ǰ����Y Ӧ�õ����ҷ���
  const FVector2D& InputAxis = Value.Get<FVector2D>();
  if (APawn* MyPawn = GetPawn<APawn>())
  {
    MyPawn->AddMovementInput(ForwardVector, InputAxis.X);
    MyPawn->AddMovementInput(RightVector, InputAxis.Y);
  }
}