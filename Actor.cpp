#include "Actor.h"
#include "ActorManager.h"
#include "TimerManager.h"
#include "Level.h"

AActor::AActor(Level* _level, const string& _name, const TransformData& _transform)
{
	level = _level; // Setup level in first

	isToDelete = false;
	id = 0;
	lifeSpan = 0.0f;
	name = _name;
	zOrder = 0;
	displayName = "Unknown";
	components = set<UComponent*>();
	root = CreateDefaultSubobject<URootComponent>(_transform);
	parent = nullptr;
	attachment = AT_NONE;
	children = set<AActor*>();
}

AActor::AActor(const AActor& _other)
{
	isToDelete = _other.isToDelete;
	id = _other.id;
	lifeSpan = _other.lifeSpan;
	name = _other.name;
	displayName = _other.displayName;
	zOrder = _other.zOrder;
	for (UComponent* _component : _other.components)
	{
		AddComponent(_component->Clone(this));
	}

	root = GetComponent<URootComponent>();
	parent = _other.parent;
	attachment = _other.attachment;
	for (AActor* _child : _other.children)
	{
		children.insert(new AActor(*_child));
	}
	level = _other.level;
}

AActor::~AActor()
{
	for (UComponent* _component : components)
	{
		delete _component;
	}
}


void AActor::Construct()
{
	if (!level)
	{
		LOG(Fatal, "Tried to construct an actor (\"" + name + "\") with no level associated !");
		return;
	}

	id = GetUniqueID();
	displayName = level->GetActorManager().GetAvailableName(name);
	SetActive(true);

	for (UComponent* _component : components)
	{
		_component->Construct();
	}
 }

void AActor::Deconstruct()
{
	for (UComponent* _component : components)
	{
		_component->Deconstruct();
	}

	SetActive(false);
	Unregister();
}

void AActor::BeginPlay()
{
	if (lifeSpan > 0.0f)
	{
		new Timer(bind(&AActor::Destroy, this), seconds(lifeSpan), true);
	}

	for (UComponent* _component : components)
	{
		_component->BeginPlay();
	}
}

void AActor::Tick(const float _deltaTime)
{
	for (UComponent* _component : components)
	{
		_component->Tick(_deltaTime);
	}
}

void AActor::BeginDestroy()
{
	for (UComponent* _component : components)
	{
		_component->BeginDestroy();
	}
}


void AActor::Register()
{
	level->GetActorManager().AddActor(this);
}

void AActor::Unregister()
{
	level->GetActorManager().RemoveActor(this);
}

void AActor::SetName(const string& _name)
{
	if (name == _name) return;

	name = _name;
	displayName = level->GetActorManager().GetDisplayName(this);
}

void AActor::CreateSocket(const string& _name, const TransformData& _transform, const AttachmentType& _type)
{
	AActor* _socket = level->SpawnActor<AActor>(_name, _transform);
	AddChild(_socket, _type);
}

void AActor::Destroy()
{
	SetToDelete();
}

void AActor::AddComponent(UComponent* _component)
{
	components.insert(_component);
	_component->BeginPlay();
}

void AActor::RemoveComponent(UComponent* _component)
{
	components.erase(components.find(_component));
}