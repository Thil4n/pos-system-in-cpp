#include "product.h"

class SaleNode
{
public:
    // Product data
    Product product_data;

    // Pointer for next node
    SaleNode *next;

    SaleNode();
    SaleNode(Product);
};