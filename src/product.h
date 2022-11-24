#ifndef PRODUCT_H_INCLUDED
#define PRODUCT_H_INCLUDED

#include <string>

// Structure for hold data of the race
struct Product
{
    bool is_filled = false;
    std::string serial;
    std::string title;
    float price;
    int sale_quantity = 0;
};

#endif