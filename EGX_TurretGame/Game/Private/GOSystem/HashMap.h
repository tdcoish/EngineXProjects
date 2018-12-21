
#pragma once



#include <list>
#include <string>
#include <functional>		// what's this?

#include "GameObject.h"

typedef unsigned int Hash;

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

	// We take some data and drop it in the correct bucket.
	// In this case the data is usually a GO pointer
	void InsertNoCheck(T& data)
	{
		int index = Translate(data->mHash);
		mBuckets[index].push_back(data);
	}

	// Find the hash in our bucket? Shouldn't we immediately know this
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

	// Why?
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

	// Find the hash and remove it.
	void Remove(Hash hash)
	{
		int index = Translate(hash);
		std::list<T>& bucket = mBuckets[index];

		T toRemove = nullptr;

		// Only if multiple GO's had the same hash, but shouldn't we 
		for (auto& value : bucket)
		{
			if (value->mHash == hash)
			{
				toRemove = value;
				break;
			}
		}

		bucket.remove(toRemove);
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






