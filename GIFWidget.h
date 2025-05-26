#pragma once
#include "ImageWidget.h"
#include "AnimationComponent.h"

namespace UI
{
	class AGIFWidget : public AImageWidget
	{
		UAnimationComponent* animation;

	public:
		FORCEINLINE void AddAnimation(Animation* _animation)
		{
			animation->AddAnimation(_animation);
		}
		FORCEINLINE void AddAnimations(const vector<Animation*>& _animations)
		{
			animation->AddAnimations(_animations);
		}

	public:
		AGIFWidget(Level* _level, const RectangleShapeData& _data, const string& _name = "Image", const RenderType& _type = Screen);
		AGIFWidget(Level* _level, const CircleShapeData& _data, const string& _name = "Image", const RenderType& _type = Screen);
		AGIFWidget(const AGIFWidget& _other);

		virtual void BeginPlay() override;
	};
}