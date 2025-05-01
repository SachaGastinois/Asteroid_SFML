#pragma once
#include "Actor.h"
#include "InputManager.h"
#include "CameraManager.h"

class Level;
class UCameraManager;
class APawn;

class PlayerController : public AActor
{
	Input::InputManager inputManager;
	RenderWindow* window;
	Camera::UCameraManager* cameraManager;
	APawn* pawn;

public:
	FORCEINLINE void SetShowMouseCursor(const bool _status)
	{
		window->setMouseCursorVisible(_status);
	}
	FORCEINLINE Input::InputManager& GetInputManager()
	{
		return inputManager;
	}
		
public:
	PlayerController(Level* _level, const string& _name = "PlayerController");
	PlayerController(const PlayerController& _other);

public:
	virtual void Tick(const float _deltaTime) override;
	void Enable();
	void Disable();

	#pragma region Pawn

	template<typename Type = APawn, IS_BASE_OF(APawn, Type)>
	FORCEINLINE Type* GetPawn()
	{
		if (!pawn)
		{
			Type* _type = SpawnPawn<Type>();
			pawn = _type;
			return _type;
		}

		return Cast<Type>(pawn);
	}

	template<typename Type, IS_BASE_OF(APawn, Type)>
	FORCEINLINE Type* SpawnPawn()
	{
		APawn* _pawn = GetPawnRef();
		const SubclassOf<Type>& _pawnRef = *Cast<Type>(_pawn);

		Type* _type = Spawn<Type>(_pawnRef);
		_type->Register();
		_type->Construct();

		delete _pawn;
		return _type;
	}

	FORCEINLINE virtual APawn* GetPawnRef() const;
	FORCEINLINE Vector2f GetPixelToCoords() const;

	#pragma endregion
};