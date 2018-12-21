
#pragma once

//#include "Sorting.h"

/***************************************************************************************************
This array wrapper type works with both pointers and raw data. All that is needed is for the programmer
to pass in the correct data type upon initialization. Further, for an array of pointers, we need to use
our discretion when it comes to DeleteItem vs RemoveItem, and calling ~tdcArray() with or without DeleteList
first. This is because some of the time when we remove a pointer to an item we aren't actually deleting it, 
and some of the time when we destroy the list we don't want to destroy the members of the list.

The list can easily be created, and will handle adding and removing items seemlessly.

I remember that this class had some serious bug issues with deletion, so this class should basically 
only ever be used to store raw data, or alternatively not be counted on to actually delete the data inside
of the pointers, should it store pointers. Yes, this needs to get fixed, but until then never call DeleteList(),
and expect it to do what you want.
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
		//list[i] = 0;		//maybe null?
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
