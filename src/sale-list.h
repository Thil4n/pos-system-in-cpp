#include "sale-node.h"

class SaleList
{
private:
    SaleNode *head, *tail;
    int size;

public:
    // Default constructor
    SaleList();

    // Distructor
    ~SaleList();

    // Methods
    bool append(Product product_data);
    int delete_item(std::string serial);
    void display();
    void print_bill(float discount);
};
