// Implemented by Leager-zju


#include "UI/RHUD.h"
#include "UI/Widget/RStatusBarWidget.h"

void ARHUD::InitAndDraw()
{
  StatusBar = CreateWidget<URStatusBarWidget>(GetWorld(), StatusBarClass);
  StatusBar->AddToViewport();
}
