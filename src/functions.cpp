#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "functions.h"

using namespace std;

// A custom function to validate the user input

bool validate_integer(string str, bool is_signed = false)
{

    for (size_t i = 0; i < str.size(); i++)
    {

        if (!isdigit(str[i]) && str[i] != '-')
            return false;

        // minus mark should only at 0 index and only if is signed
        else if ((str[i] == '-' && !is_signed) || (str[i] == '-' && i != 0))
            return false;
    }

    return true;
}

// A custom function to get user input

int get_integer(string txt, bool is_signed = false)
{
    bool valid = false;
    string input;

    do
    {

        cout << endl
             << " [~] " << txt << " : ";

        cin >> input;

        if (validate_integer(input, is_signed))
            valid = true;

        else
            cout << endl
                 << " [ERROR] The input is invalid!." << endl;

    } while (!valid);

    return stoi(input);
}

// A custom function to get user input

string get_string(string txt, int min_len, int max_len)
{
    bool valid = false;
    string input;

    do
    {

        cout << endl
             << " [~] " << txt << " : ";

        cin >> input;

        if (min_len <= input.size() && input.size() <= max_len)
            valid = true;

        else
            cout << endl
                 << " [ERROR] The input is invalid!." << endl;

    } while (!valid);

    return input;
}

// A custom function to properly display indexes

string get_suffix(int i)
{
    int j, k;
    j = i % 10;
    k = i % 100;

    if (j == 1 && k != 11)
    {
        return "st";
    }
    if (j == 2 && k != 12)
    {
        return "nd";
    }
    if (j == 3 && k != 13)
    {
        return "rd";
    }
    return "th";
}

void welcome()
{
    cout << "     ________________________________________________________________________________________" << endl;
    cout << "    |                                                                                        |" << endl;
    cout << "    |                               ########      ########       ########                    |" << endl;
    cout << "    |                               #      #      #      #       #                           |" << endl;
    cout << "    |                               #      #      #      #       #                           |" << endl;
    cout << "    |                               ########      #      #       ########                    |" << endl;
    cout << "    |                               #             #      #              #                    |" << endl;
    cout << "    |                               #             #      #              #                    |" << endl;
    cout << "    |                               #       #     ########   #   ########                    |" << endl;
    cout << "    |                                                                                        |" << endl;
    cout << "    |                                                                                        |" << endl;
    cout << "    |                                      POINT OF SALES SYSTEM                             |" << endl;
    cout << "    |                         Developed By EminenceApps (eminenceapps.com)                   |" << endl;
    cout << "    |________________________________________________________________________________________|" << endl;
}

int login()
{
    string username, password, str;
    bool authenticated = false;
    int auth_level = 0;

    ifstream database("./database/users.db");

    struct User
    {
        int id, type;
        string username, password;
    };

    vector<User> db_user_list;

    while (getline(database, str))
    {
        User db_user;
        stringstream linestream(str);
        linestream >> db_user.id >> db_user.username >> db_user.password >> db_user.type;
        db_user_list.push_back(db_user);
    }

    while (!authenticated)
    {
        username = get_string("Enter the username", 3, 20);
        password = get_string("Enter the password", 6, 20);

        for (User db_user : db_user_list)
        {
            if (username == db_user.username && password == db_user.password)
            {
                authenticated = true;
                auth_level = db_user.type;
                break;
            }
        }

        if (!authenticated)
        {
            cout << endl
                 << " [ERROR] Invalid creditionals!" << endl;
        }
    }

    system("clear");
    database.close();

    return auth_level;
}

int admin_options()
{

    cout << endl
         << " [~] Select an option" << endl
         << endl;
    cout << " [1] View Products list" << endl;
    cout << " [2] Add Product" << endl;
    cout << " [3] Delete Product" << endl;
    cout << " [4] Edit Product" << endl;
    cout << " [5] Exit" << endl;

    ;

    int option = get_integer("Enter the option", false);

    return option;
}

int cashier_options()
{
    cout << endl
         << " [~] Select an option" << endl
         << endl;
    cout << " [1] View Products list" << endl;
    cout << " [2] New sale" << endl;
    cout << " [3] Exit" << endl;

    ;

    int option = get_integer("Enter the option", false);

    return option;
}

int sale_options()
{
    cout << endl
         << " [~] Select an option" << endl
         << endl;
    cout << " [1] View cart" << endl;
    cout << " [2] Add product to cart" << endl;
    cout << " [3] Remove product from cart" << endl;
    cout << " [4] View product list" << endl;
    cout << " [5] Print the bill" << endl;
    cout << " [6] Exit" << endl;

    ;

    int option = get_integer("Enter the option", false);

    return option;
}

Product get_product_data()
{
    string serial, title;
    float price;
    Product product_data;

    serial = get_string("Enter the serial key [8 characters]", 8, 8);
    title = get_string("Enter the title", 6, 20);
    price = get_integer("Enter the price", false);

    product_data.serial = serial;
    product_data.title = title;
    product_data.price = price;

    return product_data;
}