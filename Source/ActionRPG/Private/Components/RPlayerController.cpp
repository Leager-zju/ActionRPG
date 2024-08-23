// Implemented by Leager-zju


#include "Components/RPlayerController.h"
#include "Interface/RHighLightable.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ARPlayerController::ARPlayerController()
{
  bReplicates = true; // 该控制器的实例将在网络游戏中进行复制，以便在不同客户端之间同步控制器的状态和行为
}

void ARPlayerController::BeginPlay()
{
  Super::BeginPlay();

  // 设置 IMC 与优先级(0)
  UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
  // check 宏保证后面的指针非空
  check(SubSystem);
  check(PlayerInputCtx);
  SubSystem->AddMappingContext(PlayerInputCtx, 0);

  // 显示鼠标
  bShowMouseCursor = true;
  // 设置鼠标样式
  DefaultMouseCursor = EMouseCursor::Default;

  FInputModeGameAndUI InputMode;
  // 当玩家将鼠标移动到屏幕边缘时，游戏不会阻止鼠标光标离开游戏窗口
  InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
  // 设置在捕获鼠标时不隐藏鼠标光标
  // 具有更高的优先级，可以在捕获鼠标输入时覆盖 bShowMouseCursor 的设定
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

  // 将 Move() 绑定到 Action 上，CastChecked 保证结果非空
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
  // 根据控制器偏角，获取 xOy 平面上的方向向量
  const FRotator& GroundRotation = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
  const FRotationMatrix& GroundRotationMatrix(GroundRotation);

  const FVector& ForwardVector = GroundRotationMatrix.GetUnitAxis(EAxis::X);
  const FVector& RightVector = GroundRotationMatrix.GetUnitAxis(EAxis::Y);

  // 输入值中的 X 应用到前后方向，Y 应用到左右方向
  const FVector2D& InputAxis = Value.Get<FVector2D>();
  if (APawn* MyPawn = GetPawn<APawn>())
  {
    MyPawn->AddMovementInput(ForwardVector, InputAxis.X);
    MyPawn->AddMovementInput(RightVector, InputAxis.Y);
  }
}