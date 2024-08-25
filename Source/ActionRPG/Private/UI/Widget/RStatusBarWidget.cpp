// Implemented by Leager-zju


#include "UI/Widget/RStatusBarWidget.h"
#include "Components/ProgressBar.h"

void URStatusBarWidget::SetHealthBarPercentage(float Percentage)
{
  HealthBar->SetPercent(Percentage);
}

void URStatusBarWidget::SetManaBarPercentage(float Percentage)
{
  ManaBar->SetPercent(Percentage);
}