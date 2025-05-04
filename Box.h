#pragma once
#include "Widget.h"

namespace UI
{
	struct BoxData
	{
		float spaceBetween;
		Vector2f size;

		BoxData()
		{
			spaceBetween = 0.0f;
			size = { 0.0f, 0.0f };
		}
		BoxData(const Vector2f& _size, const float _spaceBetween = 20.0f)
		{
			spaceBetween = _spaceBetween;
			size = _size;
		}
	};

	class Box : public AWidget
	{
	protected:
		vector<AWidget*> widgets;
		BoxData data;

	protected:
		FORCEINLINE u_int GetElementCount() const
		{
			return CAST(u_int, GetChildren().size());
		}
	public:
		FORCEINLINE virtual Vector2f GetSize() const override
		{
			return data.size;
		}

	public:
		Box(Level* _level, const BoxData& _data);

	protected:
		virtual void Update() = 0;

	public:
		void AddWidget(AWidget* _widget);
		void RemoveWidget(AWidget* _widget);
	};
}