#include <string>
#include "product.h"

// Hash Table class
class HashTable
{
private:
    Product *memory;
    int curr_size;

    int calculate_ascii_sum(std::string race);
    int hash_function_one(int ascii_sum);
    int hash_function_two(int ascii_sum);

public:
    HashTable();
    bool insert_item(struct Product race_data);
    int search_item(std::string race);
    bool delete_item(std::string race);
    bool edit_item(std::string serial, Product product_data);
    Product get_item_by_serial(std::string serial);
    void display();
    bool load();
    bool store();
};
