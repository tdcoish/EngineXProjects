
#pragma once
//#include "Engine\Public\EngineInterface.h"

// james's code below

#pragma once

#include "GameObject.h"
#include "ComponentTypes.h"
#include "Engine\Public\EngineInterface.h"
#include <vector>

#include "Collision.h"
#include "GraphicsHelpers.h"

#include <algorithm>

class GameObject;
class COGPhysics;

// our base component class
class Component
{
public:

	Component(GameObject* pGO);

	//virtual ComponentType GetType();
	virtual ComponentType GetType() const = 0;

	virtual void Initialize() { }
	virtual void Destroy() { }

//protected:

	template<class T>
	void AddToComponentVector(std::vector<T*>& componentVector)
	{
		componentVector.push_back((T*)this);
	}

	template<class T>
	void RemoveFromComponentVector(std::vector<T*>& componentVector)
	{
		componentVector.erase(std::remove(componentVector.begin(), componentVector.end(), this), componentVector.end());
	}

//protected:

	GameObject * mGO;

};

// COGTransform - where we are in space
class COGTransform : public Component
{
public:

	COGTransform(GameObject* pGO)
		: Component(pGO)
	{
	}

	virtual ComponentType GetType() const { return ComponentType::Transform; }

	exVector2& GetPosition() { return mPosition; }

	// sometimes we just have to manually set a position
	void SetPosition(float x, float y) {
		mPosition.x = x;
		mPosition.y = y;
	}

private:

	exVector2 mPosition;

};

// COGShape - our baseclass for shapes
class COGShape : public Component
{
public:

	static std::vector<COGShape*> mShapeComponents;

public:

	COGShape(GameObject* pGO)
		: Component(pGO)
	{
	}

	virtual void Initialize() override;

	virtual void Destroy() override;

	virtual void Render(exEngineInterface* pGFX, COGTransform* pTrans) = 0;

private:

	exColor c;
	// TODO - add a color variable here!

};

class COGTransform;
// COGBoxShape - box
class COGBoxShape : public COGShape
{
public:

	COGBoxShape(GameObject* pGO, float fWidth, float fHeight)
		: COGShape(pGO)
		, mWidth(fWidth)
		, mHeight(fHeight)
	{
	}

	virtual ComponentType GetType() const { return ComponentType::BoxShape; }

	virtual void Render(exEngineInterface*	pGFX, COGTransform* pTrans) override
	{
		// tell EngineX to draw me
		CollisionRect rect;
		rect.h = mHeight;
		rect.w = mWidth;
		exVector2 pos = pTrans->GetPosition();
		rect.x = pos.x;
		rect.y = pos.y;
		
		tdcRenderRectangle(rect, pGFX);
	}

	float GetWidth() { return mWidth; }
	float GetHeight() { return mHeight; }


private:

	float mWidth;
	float mHeight;

};

// COGCircleShape - box
class COGCircleShape : public COGShape
{
public:

	COGCircleShape(GameObject* pGO, float fRadius)
		: COGShape(pGO)
		, mRadius(fRadius)
	{
	}

	virtual ComponentType GetType() const { return ComponentType::CircleShape; }

	virtual void Render(exEngineInterface*	pGFX, COGTransform* pTrans) override
	{
		// tell EngineX to draw me
		CollisionRect rect;
		rect.h = mRadius;
		rect.w = mRadius;
		exVector2 pos = pTrans->GetPosition();
		rect.x = pos.x;
		rect.y = pos.y;

		tdcRenderCircle(rect, pGFX);
	}

	float GetRadius() { return mRadius; }

private:

	float mRadius;

};

// our interface that allows COGPhysics to talk to anyone

class IPhysicsCollisionEvent
{
public:

	virtual void OnCollision(COGPhysics* pMe, COGPhysics* pOther) = 0;

};

// COGBounce - where we make the ball bounce
class COGBounce : public Component, public IPhysicsCollisionEvent
{
public:

	COGBounce(GameObject* pGO)
		: Component(pGO)
	{
	}

	virtual ComponentType GetType() const { return ComponentType::Bounce; }

	virtual void OnCollision(COGPhysics* pMe, COGPhysics* pOther) override
	{
		// tell pMe to bounce by setting our velocity to a new amount
	}

};
