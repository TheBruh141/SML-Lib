//
// Created by bruhpc on 10/16/23.
//

#ifndef SML_LIB_FOR_EACH_H
#define SML_LIB_FOR_EACH_H

#include "common_bindings.h"
#include "internal_lib_utils.h"

#define foreach(item, array) \
    for (size_t i = 0; i < sizeof(array) / sizeof(array[0]) && ((item) = (array)[i], 1); ++i)

#define in ,

// infor
// Purpose:
//    The `infor` macro provides a convenient way to iterate over elements of an
//    array, with an optional initialization statement before the loop starts.
//    Think of this as the for i in range(len(array)) in python
//
// Parameters:
//    - type: The type of the array elements.
//    - item: The name of the loop variable.
//    - array: The array to iterate over.
//    - __VA_ARGS__: An optional initialization statement.
// ----------------------------------------------------------------------------
// Usage:
//
//    infor(int, i in myArray)
//    {
//        // Loop body
//    }
//    // or
//
//    infor(int, i in myArray, i += 2)
//    {
//        // Loop body
//    }

#define infor(type, item, array, __VA_ARGS__) (sizeof_va(__VA_ARGS__) == 0) ? for (##type##item = 0;##item < sizeof_arr(array); ++##item) : for (##type(item) = 0;##item < sizeof_arr(array); __VA_ARGS__)


// Macro: efor
// Purpose:
//    The `efor` macro is similar to `infor`, but it's specifically tailored
//    for iterating over associative arrays (arrays with key-value pairs).
//    think of this as the for k,v in enumerate(array) in python
//
// Parameters:
//    - t1: The type of the key.
//    - key: The name of the key loop variable.
//    - t2: The type of the value.
//    - value: The name of the value loop variable.
//    - array: The associative array to iterate over.
//    - __VA_ARGS__: An optional initialization statement.
// ----------------------------------------------------------------------------
// Usage:
//
//    efor(int, i, char, c, myMap, i += 2, c = c[i])
//    {
//        // Loop body
//    }
//    // or
//
//    efor(int, i, char, c, myMap)
//    {
//     // Loop body
//    }
// -------------------
// in the last example the for loop will be expanded to
// for (int i = 0, char c = myMap[0]; i < sizeof(myMap); i += 2, c = myMap[i])

#define efor(t1, key, t2, value, array, __VA_ARGS__) (sizeof_va(__VA_ARGS__) == 0)                                                                      \
                                                             ? for (##t1##key = 0, ##t2##value = array[0];##key < sizeof_arr(array); ++key, value[key]) \
                                                             : for (##t1##key = 0, ##t2##value = array[0];##key < sizeof_arr(array); __VA_ARGS__)

#endif//SML_LIB_FOR_EACH_H
