#include "ShapeObject.h"
#include "TextureManager.h"

ShapeObject::ShapeObject(const CircleShapeData& _data)
{
	texture = Texture();
	objectData = ShapeObjectData(SOT_CIRCLE, _data);
	InitCircle(*objectData.data.circleData);	
}

ShapeObject::ShapeObject(const RectangleShapeData& _data)
{
	texture = Texture();
	objectData = ShapeObjectData(SOT_RECTANGLE, _data);
	InitRectangle(*objectData.data.rectangleData);
}

ShapeObject::ShapeObject(const ConvexShapeData& _data)
{
}

ShapeObject::ShapeObject(const ShapeObject& _other)
{
	texture = _other.texture;
	objectData = _other.objectData;

	if (objectData.type == SOT_CIRCLE)
	{
		InitCircle(*objectData.data.circleData);
	}

	else if (objectData.type == SOT_RECTANGLE)
	{
		InitRectangle(*objectData.data.rectangleData);
	}
}

ShapeObject::~ShapeObject()
{
	delete shape;
}


void ShapeObject::InitCircle(const CircleShapeData& _data)
{
	shape = new CircleShape(_data.radius, _data.pointCount);
	M_TEXTURE.Load(this, _data.path, _data.rect);
}

void ShapeObject::InitRectangle(const RectangleShapeData& _data)
{
	shape = new RectangleShape(_data.size);
	M_TEXTURE.Load(this, _data.path, _data.rect, _data.textureType, _data.isRepeated);
}

void ShapeObject::InitConvex(const ConvexShapeData& _data)
{
	u_int _index = 0;
	ConvexShape* _convex = new ConvexShape(_data.point.size());
	for (Vector2f _point : _data.point)
	{
		_convex->setPoint(_index++, _point);
	}
	shape = _convex;
	_convex = nullptr;
	delete _convex;
	M_TEXTURE.Load(this, _data.path, _data.rect, _data.textureType, _data.isRepeated);
}
