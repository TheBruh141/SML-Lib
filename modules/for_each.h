//
// Created by bruhpc on 10/16/23.
//

#ifndef SML_LIB_FOR_EACH_H
#define SML_LIB_FOR_EACH_H

#define foreach(item, array) \
    for (size_t i = 0; i < sizeof(array) / sizeof(array[0]) && ((item) = (array)[i], 1); ++i)

#endif //SML_LIB_FOR_EACH_H
