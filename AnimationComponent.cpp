#include "AnimationComponent.h"

UAnimationComponent::UAnimationComponent(AActor* _owner) : UComponent(_owner)
{
	current = nullptr;
	allAnimations = map<string, Animation*>();
}

UAnimationComponent::UAnimationComponent(AActor* _owner, const UAnimationComponent& _other) : UComponent(_owner)
{
	for (const pair<string, Animation*>& _animation : _other.allAnimations)
	{
		allAnimations[_animation.first] = new Animation(*_animation.second);
	}
	current = allAnimations[_other.current->GetName()];
}

UAnimationComponent::~UAnimationComponent()
{
	for (const pair<string, Animation*>& _animation : allAnimations)
	{
		delete _animation.second;
	}
}


void UAnimationComponent::AddAnimation(Animation* _animation)
{
	const string& _animationName = _animation->GetName();
	if (allAnimations.contains(_animationName)) return;

	allAnimations[_animationName] = _animation;

	if (!current)
	{
		SetCurrentAnimation(_animationName);
	}
}

void UAnimationComponent::AddAnimations(const vector<Animation*>& _animations)
{
	const u_int& _animationsCount = CAST(u_int, _animations.size());

	for (u_int _index = 0; _index < _animationsCount; _index++)
	{
		if (_index == 0)
		{
			SetCurrentAnimation(_animations[_index]->GetName());
		}
			
		AddAnimation(_animations[_index]);
	}
}