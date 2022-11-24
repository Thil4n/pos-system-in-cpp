#include <iostream>
#include <iomanip>
#include "sale-list.h"

using namespace std;

/* Default constructor of the class */

SaleList::SaleList()
{
    this->head = NULL;
    this->tail = NULL;
    this->size = 0;
}

/* Destructor for free memory */

SaleList::~SaleList()
{
    SaleNode *current = this->head;

    while (current != NULL)
    {
        delete current;
        current = current->next;
    }
}

/* Insert element at the end of the list */

bool SaleList::append(Product product_data)
{
    SaleNode *temp = new SaleNode(product_data);

    if (head == NULL) // empty list
    {
        this->head = temp;
        this->tail = temp;
    }
    else
    {
        this->tail->next = temp;
        this->tail = temp;
    }
    this->size++;

    return true;
}

/* Delete an element with a specific value from the list*/

int SaleList::delete_item(string serial)
{

    SaleNode *current = this->head;

    while (current != NULL) // Loop until the end of the list
    {
        if (current->product_data.serial == serial) // Check wether the current element is the finding one
        {
            if (current == this->head)
            {
                this->head = head->next; // Delete the head node
            }

            else if (current == this->tail)
            {
                this->tail->next = NULL;
            }

            delete current;
            this->size--;
        }

        current = current->next;
    }

    return true;
}

/* Print the elements of the list */

void SaleList::display()
{
    system("clear");

    if (this->head == NULL)
    {
        cout << endl
             << " [~] The cart is currently empty" << endl;
    }
    else
    {
        int number = 1;

        cout << " -------------------------------------------------------------" << endl;
        cout << "|                         SHOPING CART                        |" << endl;
        cout << " -------------------------------------------------------------" << endl;
        cout << " | No. |        Title                 |  Quantity     | Price |" << endl;
        cout << " -------------------------------------------------------------" << endl;

        SaleNode *current = this->head;

        while (current != NULL)
        {
            cout << " | ";
            cout << left << setfill(' ') << setw(4) << number;
            cout << "| ";
            cout << setfill(' ') << setw(29) << current->product_data.title;
            cout << "| ";
            cout << setfill(' ') << setw(14) << current->product_data.sale_quantity;
            cout << "| ";
            cout << setfill(' ') << setw(6) << current->product_data.price;
            cout << "|";
            cout << endl;

            number++;
            current = current->next;
        }

        cout << " -------------------------------------------------------------" << endl;

        cout << endl;
    }
}
/* Print the bill */

void SaleList::print_bill(float discount)
{
    if (this->head == NULL)
    {
        cout << endl
             << " [ERROR] Add some products before checkout" << endl;
    }
    else
    {

        int number = 1;
        float net_total = 0, total;

        cout << " -------------------------------------------------------------" << endl;
        cout << "|                         SHOPING CART                        |" << endl;
        cout << " -------------------------------------------------------------" << endl;
        cout << " | No. |        Title                 |  Quantity     | Price |" << endl;
        cout << " -------------------------------------------------------------" << endl;

        SaleNode *current = this->head;

        while (current != NULL)
        {
            cout << " | ";
            cout << left << setfill(' ') << setw(4) << number;
            cout << "| ";
            cout << setfill(' ') << setw(29) << current->product_data.title;
            cout << "| ";
            cout << setfill(' ') << setw(14) << current->product_data.sale_quantity;
            cout << "| ";
            cout << setfill(' ') << setw(6) << current->product_data.price;
            cout << "|";
            cout << endl;

            number++;
            net_total += current->product_data.price * current->product_data.sale_quantity;
            current = current->next;
        }

        cout << " -------------------------------------------------------------" << endl;
        cout << " | Total amount                                 ";
        cout << setfill(' ') << setw(14) << net_total;

        cout << "|" << endl;

        cout
            << " -------------------------------------------------------------" << endl;
        cout << " | Discount                                     ";
        cout << setfill(' ') << setw(14) << discount;

        cout << "|" << endl;

        cout
            << " -------------------------------------------------------------" << endl;
        cout << " | Total                                        ";
        cout << setfill(' ') << setw(14) << net_total - discount;

        cout << "|" << endl;

        cout
            << " -------------------------------------------------------------" << endl;

        cout << endl;
    }
}