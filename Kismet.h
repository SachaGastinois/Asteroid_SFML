#pragma once
#include "Utilities.h"

class AActor;

struct HitInfo
{
	Vector2f position;
	float distance;
	AActor* actor;

	bool operator!=(const HitInfo& _hitInfo) const
	{
		return (actor != _hitInfo.actor && distance != _hitInfo.distance && position != _hitInfo.position);
	}
};

bool Raycast(const Vector2f& _origin, const Vector2f& _direction, const float _maxDistance,
			 HitInfo& _hitInfo, const vector<AActor*>& _ignoredActors = vector<AActor*>(),
			 const float _precision = 0.01f);

vector<HitInfo> RaycastAll(const Vector2f& _origin, const Vector2f& _direction, const float _maxDistance,
						   const vector<Shape*>& _ignoredShapes, const float _precision = 0.01f);
 
bool BoxCast(const FloatRect& _boxRect, HitInfo& _hitInfo, const vector<AActor*>& _ignoredActors);