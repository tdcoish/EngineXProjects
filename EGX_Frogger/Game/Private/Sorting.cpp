
#include "Sorting.h"


template <typename T>
void Swap(T* pOne, T* pTwo) {
	T temp = *pOne;
	*pOne = *pTwo;
	*pTwo = temp;
}