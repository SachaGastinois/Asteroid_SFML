#pragma once
#include "Actor.h"
#include "Widget.h"

namespace UI
{
	class HUD : public AActor
	{
		set<AWidget*> allWidgets;
		AWidget* currentWidget;

	private:
		FORCEINLINE void RegisterWidget(AWidget* _widget)
		{
			if (allWidgets.contains(_widget)) return;

			allWidgets.insert(_widget);
			_widget->Register();
		}
		FORCEINLINE void UnregisterWidget(AWidget* _widget)
		{
			if (!allWidgets.contains(_widget)) return;

			allWidgets.erase(_widget);
			_widget->Unregister();
		}

	public:
		#pragma region SpawnWidget

		template <typename Type, typename ...Args, IS_BASE_OF(AWidget, Type)>
		FORCEINLINE Type* SpawnWidget(Args&&... _args)
		{
			Type* _widget = Spawn<Type>(level, forward<Args>(_args)...);
			_widget->Construct();
			RegisterWidget(_widget);

			return _widget;
		}

		template <typename Type, IS_BASE_OF(AWidget, Type)>
		FORCEINLINE Type* SpawnWidget(const SubclassOf<Type> _widgetRef)
		{
			Type* _widget = Spawn<Type>(_widgetRef);
			_widget->Construct();
			RegisterWidget(_widget);

			return _widget;
		}

		#pragma endregion

	public:
		HUD(Level* _level);
		HUD(const HUD& _other);

	public:
		void AddToViewport(AWidget* _widget);
		void RemoveFromViewport(AWidget* _widget);
	};
}