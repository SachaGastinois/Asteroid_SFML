#include "GIFWidget.h"

UI::AGIFWidget::AGIFWidget(Level* _level, const RectangleShapeData& _data, const string& _name, const RenderType& _type)
					   : AImageWidget(_level, _data, _name, _type)
{
	animation = CreateDefaultSubobject<UAnimationComponent>();
}

UI::AGIFWidget::AGIFWidget(Level* _level, const CircleShapeData& _data, const string& _name, const RenderType& _type)
					   : AImageWidget(_level, _data, _name, _type)
{
	animation = CreateDefaultSubobject<UAnimationComponent>();
}

UI::AGIFWidget::AGIFWidget(const AGIFWidget& _other) : AImageWidget(_other)
{
	animation = _other.animation;
}


void UI::AGIFWidget::BeginPlay()
{
	Super::BeginPlay();

	animation->StartAnimation();
}