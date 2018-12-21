#pragma once

typedef unsigned int Hash;

class GameObject;

class GameObjectHandle
{
public:
	Hash mHash;

public:
	bool IsValid() const;
	GameObject* Get() const;

};