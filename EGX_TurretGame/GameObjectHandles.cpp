// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <list>
#include <string>
#include <functional>

typedef unsigned int Hash;
std::hash<std::string> s_hash;

//
// a hash map
// you could use std::map or std::unordered_map if you want (but full marks for your own)
//

template<class T, int SIZE>
class HashMap
{
public:

	HashMap()
	{
		// assume SIZE is a power of two
		mMask = SIZE - 1;
	}

	void InsertNoCheck(T& data)
	{
		int index = Translate(data->mHash);
		mBuckets[index].push_back(data);
	}

	T Find(Hash hash)
	{
		int index = Translate(hash);
		std::list<T>& bucket = mBuckets[index];

		for (auto& value : bucket)
		{
			if (value->mHash == hash)
			{
				return value;
			}
		}

		return nullptr;
	}

	const T Find(Hash hash) const
	{
		int index = Translate(hash);
		const std::list<T>& bucket = mBuckets[index];

		for (auto& value : bucket)
		{
			if (value->mHash == hash)
			{
				return value;
			}
		}

		return nullptr;
	}

	void Delete(T data)
	{
		// TODO - delete from hash map
	}

private:

	int Translate(Hash hash) const
	{
		return (hash & mMask);
	}

private:

	Hash mMask;

	// you should use your own linked list class for full marks
	std::list<T> mBuckets[SIZE];
};

//
// a handle for a game object, use this to get a pointer to your game objects
//

class GameObject;

class GameObjectHandle
{
public:
	Hash mHash;

public:
	bool IsValid() const;
	GameObject* Get() const;

};

//
// your game object
//

class GameObject
{
public:
	Hash mHash;

public:
	GameObject(Hash hash);
	~GameObject();

	GameObjectHandle GetHandle()
	{
		GameObjectHandle temp;
		temp.mHash = mHash;

		return temp;
	}

};

//
// your inventory of game objects, it's just a wrapper for the hash map really
//

class GameObjectInventory
{
public:

	void Register(GameObject* pGO)
	{
		mMap.InsertNoCheck(pGO);
	}

	void Unregister(GameObject* pGO)
	{
		mMap.Delete(pGO);
	}

	bool Exists(Hash hash) const
	{
		return (mMap.Find(hash) != nullptr);
	}

	GameObject* Lookup(Hash hash)
	{
		return mMap.Find(hash);
	}

	const GameObject* Lookup(Hash hash) const
	{
		return mMap.Find(hash);
	}

private:
	HashMap<GameObject*, 256> mMap;
};

GameObjectInventory gGameObjectInventory;

//
// impl for GameObjectHandle
//

bool GameObjectHandle::IsValid() const
{
	return gGameObjectInventory.Exists(mHash);
}

GameObject* GameObjectHandle::Get() const
{
	return gGameObjectInventory.Lookup(mHash);
}

//
// impl for GameObject
//

GameObject::GameObject(Hash hash)
{
	mHash = hash;
	gGameObjectInventory.Register(this);
}

GameObject::~GameObject()
{
	gGameObjectInventory.Unregister(this);
}

//
// test code!!
//

int main()
{
	HashMap<GameObjectHandle, 256> gameObjectInventory;

	GameObject* missile = new GameObject(s_hash("MISSILE"));
	GameObjectHandle missileHandle = missile->GetHandle();
	
	if (missileHandle.IsValid())
	{
		// it's true!
	}

	delete missile;

	if (!missileHandle.IsValid())
	{
		// it's true!
	}

    return 0;
}

