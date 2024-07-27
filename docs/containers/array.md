# Array

The array container class (`::microlibrary::Array`) is defined in the `microlibrary`
static library's
[`microlibrary/array.h`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/include/microlibrary/array.h)/[`microlibrary/array.cc`](https://github.com/apcountryman/microlibrary/blob/main/libraries/microlibrary/ANY/ANY/source/microlibrary/array.cc)
header/source file pair.

`::microlibrary::Array` supports the following operations:
- To access the element at a specific position in an array without bounds checking, use
  the `::microlibrary::Array::operator[]()` operator overloads.
- To access the element at a specific position in an array with bounds checking, use the
  `::microlibrary::Array::at()` member functions.
- To access the first element of an array, use the `::microlibrary::Array::front()` member
  functions.
- To access the last element of an array, use the `::microlibrary::Array::back()` member
  functions.
- To access the underlying array, use the `::microlibrary::Array::data()` member
  functions.
- To get an iterator to the first element of an array, use the
  `::microlibrary::Array::begin()` and `::microlibrary::Array::cbegin()` member functions.
- To get an iterator to the element following the last element of an array, use the
  `::microlibrary::Array::end()` and `::microlibrary::Array::cend()` member functions.
- To get an iterator to the first element of a reversed array, use the
  `::microlibrary::Array::rbegin()` and `::microlibrary::Array::crbegin()` member
  functions.
- To get an iterator to the element following the last element of a reversed array, use
  the `::microlibrary::Array::rend()` and `::microlibrary::Array::crend()` member
  functions.
- To check if an array is empty, use the `::microlibrary::Array::empty()` member function.
- To get the number of elements in an array, use the `::microlibrary::Array::size()`
  member function, or the `::microlibrary::array_size` or `::microlibrary::array_size_v`
  meta functions.
- Direct comparison for equality and inequality is supported.
