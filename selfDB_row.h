#ifndef _ROW_H_
#define _ROW_H_

#include <iostream>
#include <cstdint>

using namespace std;

struct Row{
    uint32_t orderKey;
    uint32_t custKey;
    double totalPrice;
};

#endif
