#pragma once
#include "PlayerController.h"
#include "RenderType.h"
#include "Slot.h"

namespace UI
{
	enum VisibilityType
	{
		Hidden,
		Collapsed,
		Disabled,
		UninteractibleSelf,
		UninteractibleSelfAndChildren,
		Visible,
	};

	class HUD;

	class AWidget : public AActor
	{
		u_int renderToken;
		RenderType type;
	protected:
		VisibilityType visibility;
		Slot* slot;
		HUD* hud;

	public:
		FORCEINLINE RenderType GetType() const
		{
			return type;
		}
		FORCEINLINE VisibilityType GetVisibilityType() const
		{
			return visibility;
		}
		FORCEINLINE virtual void AddSlot(Slot* _slot)
		{
			slot = _slot;
		}
		FORCEINLINE virtual void RemoveSlot()
		{
			delete slot;
		}
		FORCEINLINE virtual Slot* GetSlot() const
		{
			return slot;
		}
		FORCEINLINE virtual void SetVisibility(const VisibilityType& _visibility)
		{
			visibility = _visibility;
		}
		FORCEINLINE virtual void SetZOrder(const int _zOrder) override;
		FORCEINLINE virtual Vector2f GetSize() const = 0;

	public:
		AWidget(Level* _level, const string& _name = "AWidget", const RenderType& _type = Screen);
		~AWidget();

		virtual void Construct() override;
		virtual void Render(RenderWindow& _window) = 0;
		virtual void BindActions(Input::InputManager& _inputManager) {};
		virtual void BindViewport();
		virtual void UnbindViewport();
	};
}