#include "UtilityLevel.h"
#include "PlayerPawn.h"
#include "CircleActor.h"
#include "CUSTOMGameMode.h"
#include "CanvasWidget.h"
#include "ImageWidget.h"
#include "LabelWidget.h"
#include "ButtonWidget.h"

using namespace UI;

UUtilityLevel::UUtilityLevel(const string& _levelName) : Level(_levelName)
{
	backgroundTheme = nullptr;
}

void UUtilityLevel::InitLevel()
{
	Super::InitLevel();

	window.setMouseCursorVisible(true);
}

AButtonWidget* UUtilityLevel::InitButtonAndLabelData(HUD* _hud, UI::ACanvasWidget* _canva, const FButtonAndLabelData& _data)
{
	ALabelWidget* _label = _hud->SpawnWidget<ALabelWidget>(_data.text, _data.labelName, Screen);
	_label->SetLocation(_data.location);
	_label->SetFont(_data.fontData.first, _data.fontData.second);
	_label->SetCharacterSize(_data.characterSize);
	_label->SetOriginAtMiddle();
	_label->SetZOrder(_data.zOrder);

	AButtonWidget* _button = _hud->SpawnWidget<AButtonWidget>(RectangleShapeData(_data.size, _data.buttonPath), _data.buttonName, Screen);
	_button->SetLocation(_data.location - _data.size / 2.0f);
	_button->SetOriginAtMiddle();
	_button->SetZOrder(_data.zOrder - 1);

	_canva->AddChild(_label);
	_canva->AddChild(_button);

	return _button;
}


void UUtilityLevel::OpenMenu(UI::ACanvasWidget* _canvaToOpen, UI::ACanvasWidget* _canvaToClose)
{
	if (!_canvaToOpen || !_canvaToClose) return;

	LOG(Warning, "Open " + _canvaToOpen->GetName() + " and Close " + _canvaToClose->GetName());

	GetGameMode()->GetHUD()->RemoveFromViewport(_canvaToClose);
	_canvaToClose->SetVisibility(VisibilityType::Hidden);

	GetGameMode()->GetHUD()->AddToViewport(_canvaToOpen);
	_canvaToOpen->SetVisibility(VisibilityType::Visible);
}
