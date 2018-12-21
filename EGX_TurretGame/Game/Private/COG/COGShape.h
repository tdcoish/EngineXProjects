#pragma once

#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"
#include "Game\Private\GOSystem\Component.h"

#include "Game\Private\Helpers\GraphicsLayers.h"

class COGTransform;
// COGShape - our baseclass for shapes
class COGShape : public Component
{
public:

	static std::vector<COGShape*> mShapeComponents;

	COGShape(GameObject* pGO, GraphicsLayers layer);

	virtual void Initialize() override;

	virtual void Destroy() override;

	virtual void Render(exEngineInterface* pGFX, COGTransform* pTrans) = 0;

	exColor GetColour() { return c; }
	void SetColour(exColor col) { c = col; }

protected:

	exColor c;
	GraphicsLayers layer;
	// TODO - add a color variable here!

};

// COGBoxShape - box
class COGBoxShape : public COGShape
{
public:

	COGBoxShape(GameObject* pGO, float fWidth, float fHeight, GraphicsLayers layer);

	virtual ComponentType GetType() const { return ComponentType::BoxShape; }

	virtual void Render(exEngineInterface*	pGFX, COGTransform* pTrans) override;

	float GetWidth() { return mWidth; }
	float GetHeight() { return mHeight; }

	void SetWidth(float w) { mWidth = w; }
	void SetHeight(float h) { mHeight = h; }

private:

	float mWidth;
	float mHeight;

};

// COGCircleShape - box
class COGCircleShape : public COGShape
{
public:

	COGCircleShape(GameObject* pGO, float fRadius, GraphicsLayers layer);

	virtual ComponentType GetType() const { return ComponentType::CircleShape; }

	virtual void Render(exEngineInterface*	pGFX, COGTransform* pTrans) override;

	float GetRadius() { return mRadius; }
	void SetRadius(float rad) { mRadius = rad; }

private:
	float mRadius;
};