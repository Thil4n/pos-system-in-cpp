#include <iostream>
#include "sale-node.h"

SaleNode::SaleNode()
{
    this->next = NULL;
}

SaleNode::SaleNode(Product product_data)
{
    this->product_data = product_data;
    this->next = NULL;
}