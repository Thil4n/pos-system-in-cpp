#include <iostream>
#include <iomanip>
#include <fstream>
#include "product-list.h"
#include <cmath>
#include <sstream>
#include <string>

using namespace std;

#define hash_array_size 100

// Constructor for the Hashtable class
HashTable::HashTable()
{
    this->memory = new Product[hash_array_size];
    this->curr_size = 0;
}

// Function to calculate the ASCII sum of the string
int HashTable::calculate_ascii_sum(string serial)
{
    int sum = 0;
    for (int i = 0; i < serial.size(); i++)
    {
        sum += int(serial[i]);
    }
    return sum;
}

// First function to get the hash
int HashTable::hash_function_one(int ascii_sum)
{
    return floor(2 * ascii_sum % hash_array_size);
}

// Second function to get the hash
int HashTable::hash_function_two(int ascii_sum)
{
    return 5 - ascii_sum % 5;
}

// Function to insert data item into the hash table
bool HashTable::insert_item(struct Product product_data)
{
    // if hash table is full
    if (this->curr_size == hash_array_size)
        return false;

    // get index one from first hash function
    int index_1 = this->hash_function_one(calculate_ascii_sum(product_data.serial));

    // if no collision occurs
    if (!memory[index_1].is_filled)
    {
        memory[index_1] = product_data;
    }

    else
    {
        // get index two from second hash function
        int index_2 = this->hash_function_two(calculate_ascii_sum(product_data.serial));
        int k = 1;

        while (k < hash_array_size)
        {
            // get new index
            int new_index = (index_1 + k * index_2) %
                            hash_array_size;

            // if no collision occurs, store
            if (!memory[new_index].is_filled)
            {
                memory[new_index] = product_data;
                break;
            }
            k++;
        }
    }

    curr_size++;

    return true;
}

int HashTable::search_item(string serial)
{
    int u = hash_function_one(calculate_ascii_sum(serial));
    int v = hash_function_two(calculate_ascii_sum(serial));

    int i = 0;

    while (i < hash_array_size)
    {

        int index = (u + i * v) % hash_array_size;

        if (this->memory[index].is_filled && this->memory[index].serial == serial)
        {

            return index;
        }
        i++;
    }

    return -1;
}

Product HashTable::get_item_by_serial(string serial)
{
    int result = this->search_item(serial);
    if (result > -1)
    {
        Product product_data = this->memory[result];
        return product_data;
    }
}

bool HashTable::delete_item(string serial)
{
    int result = this->search_item(serial);
    if (result > -1)
    {
        this->memory[result].is_filled = false;
        this->memory[result].serial = "";
        this->memory[result].title = "";
        this->memory[result].price = 0;
        this->curr_size--;
        return true;
    }
    else
    {
        return false;
    }
}

bool HashTable::edit_item(string serial, Product product_data)
{
    int result = this->search_item(serial);
    if (result > -1)
    {
        this->memory[result] = product_data;
        return true;
    }
    else
    {
        return false;
    }
}

void HashTable::display()
{
    int number = 1;

    system("clear");

    cout << " -------------------------------------------------------------------" << endl;
    cout << " |                             PRODUCT LIST                         |" << endl;
    cout << " -------------------------------------------------------------------" << endl;
    cout << " | No. |        Title                 |  Serial     | Price [LKR]   |" << endl;
    cout << " -------------------------------------------------------------------" << endl;

    for (int i = 0; i < hash_array_size; i++)
    {

        if (memory[i].is_filled)
        {
            Product product_data = memory[i];

            cout << " | ";
            cout << left << setfill(' ') << setw(4) << number;
            cout << "| ";
            cout << setfill(' ') << setw(29) << product_data.title;
            cout << "| ";
            cout << setfill(' ') << setw(12) << product_data.serial;
            cout << "| ";
            cout << setfill(' ') << setw(14) << product_data.price;
            cout << "|";
            cout << endl;

            number++;
        }
    }
    cout << " -------------------------------------------------------------------" << endl;
}

// Store product list to the database

bool HashTable::store()
{
    ofstream database("./database/products.db");

    for (int i = 0; i < hash_array_size; i++)
    {

        if (memory[i].is_filled)
        {
            Product product_data = memory[i];
            database << product_data.serial << " " << product_data.title << " " << product_data.price << endl;
        }
    }

    return true;
}

// Load product list from the database

bool HashTable::load()
{
    string str;
    ifstream database("./database/products.db");

    while (std::getline(database, str))
    {

        Product product_data;
        stringstream linestream(str);

        linestream >> product_data.serial >> product_data.title >> product_data.price;
        product_data.is_filled = true;

        this->insert_item(product_data);
    }
    return true;
}
