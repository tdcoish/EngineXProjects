

#include "Game/Private/COG/COGShape.h"
#include "Game\Private\COG\COGTransform.h"

std::vector<COGShape*> COGShape::mShapeComponents;


COGShape::COGShape(GameObject* pGO, GraphicsLayers layer)
	: Component(pGO)
	, layer(layer)
{
}

void COGShape::Initialize()
{
	AddToComponentVector(mShapeComponents);
}

void COGShape::Destroy() {
	RemoveFromComponentVector(mShapeComponents);
}


COGBoxShape::COGBoxShape(GameObject* pGO, float fWidth, float fHeight, GraphicsLayers layer)
	: COGShape(pGO, layer)
	, mWidth(fWidth)
	, mHeight(fHeight)
{
}

// Consider finding center, but would need to do this for logic as well.
void COGBoxShape::Render(exEngineInterface*	pGFX, COGTransform* pTrans)
{
	// tell EngineX to draw me
	CollisionRect rect;
	rect.h = mHeight;
	rect.w = mWidth;
	exVector2 pos = pTrans->GetPosition();
	rect.x = pos.x;
	rect.y = pos.y;

	tdcRenderRectangle(rect, c, layer, pGFX);
}

COGCircleShape::COGCircleShape(GameObject* pGO, float fRadius, GraphicsLayers layer)
	: COGShape(pGO, layer)
	, mRadius(fRadius)
{
}


void COGCircleShape::Render(exEngineInterface*	pGFX, COGTransform* pTrans)
{
	// tell EngineX to draw me
	CollisionRect rect;
	rect.h = mRadius;
	rect.w = mRadius;
	exVector2 pos = pTrans->GetPosition();
	rect.x = pos.x;
	rect.y = pos.y;

	tdcRenderCircle(rect, layer, pGFX);
}
