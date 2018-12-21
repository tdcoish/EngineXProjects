
#pragma once

#include "Sorting.h"

/***************************************************************************************************
This array wrapper type works with both pointers and raw data. All that is needed is for the programmer
to pass in the correct data type upon initialization. Further, for an array of pointers, we need to use
our discretion when it comes to DeleteItem vs RemoveItem, and calling ~tdcArray() with or without DeleteList
first. This is because some of the time when we remove a pointer to an item we aren't actually deleting it, 
and some of the time when we destroy the list we don't want to destroy the members of the list.

The list can easily be created, and will handle adding and removing items seemlessly.
***************************************************************************************************/
template <class T>
struct tdcArray {
	int				maxSize;		// for now, they're all limited to 256 size
	int				numActive;
	T*				list;			// an array of type T		
									// pass in a pointer type for the pointer array.
									// theoretically scalable

	tdcArray();

	~tdcArray();					// de-allocates list memory, but does not delete individual items by itself
									// instead call DeleteList.

	void AddItem(T entity);

	void RemoveItem(T entity);
	void DeleteItem(T entity);		// pointer array specific

	void ClearList();
	void DeleteList();				// pointer array specific
};


template <typename T>
tdcArray<T>::tdcArray() {
	numActive = 0;
	maxSize = 256;
	list = new T[maxSize];
}

template <typename T>
tdcArray<T>::~tdcArray() {
	delete list;
}

template <typename T>
void tdcArray<T>::AddItem(T entity) {
	if (numActive < maxSize) {
		list[numActive] = entity;

		numActive++;
	}
}

template <typename T>
void tdcArray<T>::RemoveItem(T entity) {
	for (int i = 0; i < numActive; i++) {
		if (list[i] == entity) {
			// be careful. The item doesn't get reset to a default value.
			
			T temp = list[i];
			list[i] = list[numActive - 1];
			list[numActive - 1] = temp;

			// Not sure about why I was getting the compiler errors I was getting here
			//Swap<T>(&list[i], &list[numActive - 1]);

			numActive--;
		}
	}
}

// only call this for pointer arrays
template <typename T>
void tdcArray<T>::DeleteItem(T entity) {
	for (int i = 0; i < numActive; i++) {
		if (list[i] == entity) {
			// in this case, we actually do reset the value 
			delete list[i];
			list[i] = nullptr;

			Swap<T>(&list[i], &list[numActive - 1]);
			numActive--;
		}
	}
}

template <typename T>
void tdcArray<T>::ClearList() {
	for (int i = 0; i < maxSize; i++) {
		list[i] = 0;		//maybe null?
						// possibly call HandleItemDeletion here

		numActive = 0;
	}
}

// A wrapper around the destructor. We can't just delete list memory, or the objects won't be deleted
template <typename T>
void tdcArray<T>::DeleteList() {
	for (int i = 0; i < numActive; i++) {
		// alright it gives memory leaks, but I'm having some errors here, so I'm not freeing for now
		// I think it has to do with me not correctly using inherited constructors/destructors
		// do fix
		//~list[i];
		//delete list[i];
		list[i] = nullptr;

		// now delete the list itself
		this->~tdcArray();
	}
}







// Got this code from James. 
//template<class T>
//struct tdcElement
//{
//	T data;
//};
//
//template<class T, class K>
//struct tdcArrayNew {
//
//	typedef tdcElement<T> SomethingElementType;
//
//	int maxSize;
//	int numActive;
//	// data is the array that stores our items. But why is it a different type?
//	tdcElement<T>** data;
//
//	tdcArrayNew();
//	~tdcArrayNew();
//
//	void AddEntity(K key) {
//		if (numActive < maxSize) {
//			CreateInstance(key, data[numActive]);
//		}
//
//		numActive++;
//	}
//
//protected:
//	// we've already found the slot. We're trying to overwrite the memory at &element
//	virtual void CreateInstance(K key, SomethingElementType& element) = 0;
//
//};
//
//// for the event, we just pass in the event and set it. Things are more complicated for our entity list.
//template<class T, class K>
//class EventHolder : SomethingSomethingBase {
//	void CreateInstance(K key, SomethingElementType& element) {
//		element = key;
//	}
//};
//
//// For our entities list we are passing in a pointer to an Entity. So we need to store the address?
//template<class T, class K>
//class EntityArray : SomethingSomethingBase {
//	void CreateInstance(K key, SomethingElementType& element) {
//		element = EntityFactory::CreateEntity(key);
//	}
//};
//
//void EntityList::AddEntity(EntityType type) {
//	// if the numActive isn't bigger than our maxSize, add there.
//	if (numActive < maxSize) {
//		obj[numActive] = EntityFactory::CreateEntity(type);
//	}
//
//	numActive++;
//}
