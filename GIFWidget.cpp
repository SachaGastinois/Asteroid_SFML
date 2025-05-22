#include "GIFWidget.h"

UI::GIFWidget::GIFWidget(Level* _level, const RectangleShapeData& _data, const string& _name, const RenderType& _type)
					   : AImageWidget(_level, _data, _name, _type)
{
	animation = CreateDefaultSubobject<UAnimationComponent>();
}

UI::GIFWidget::GIFWidget(Level* _level, const CircleShapeData& _data, const string& _name, const RenderType& _type)
					   : AImageWidget(_level, _data, _name, _type)
{
	animation = CreateDefaultSubobject<UAnimationComponent>();
}

UI::GIFWidget::GIFWidget(const GIFWidget& _other) : AImageWidget(_other)
{
	animation = _other.animation;
}


void UI::GIFWidget::BeginPlay()
{
	Super::BeginPlay();

	animation->StartAnimation();
}