#include <iostream>
#include "product-list.h"
#include "sale-list.h"
#include "functions.h"

using namespace std;

int main(int argc, char const *argv[])
{
     system("clear");
     welcome();
     int auth_level = 0;
     HashTable product_list;

     auth_level = login();
     product_list.load();

     if (auth_level == 2)
     {
          cout << " -------------------------------------------------------------" << endl;
          cout << "|                                                             |" << endl;
          cout << "|                         ADMIN PORTAL                        |" << endl;
          cout << "|                                                             |" << endl;
          cout << " -------------------------------------------------------------" << endl;

          cout << endl
               << " [DONE] Successfully logged in as Admin!" << endl;

          while (true)
          {
               int choice = admin_options();

               switch (choice)
               {
               case 1: //  View Products

               {
                    product_list.display();
                    break;
               }

               case 2: // Add Product
               {

                    Product product_data = get_product_data();
                    product_data.is_filled = true;

                    system("clear");

                    if (product_list.insert_item(product_data))
                    {
                         cout << endl
                              << " [DONE] Product inserted successfully!" << endl;
                    }
                    else
                    {
                         cout << endl
                              << " [ERROR] There was an error while inserting the product!" << endl;
                    }

                    break;
               }

               case 3: // Delete Product
               {
                    string serial = get_string("Enter the serial of the product", 8, 8);
                    system("clear");

                    if (product_list.delete_item(serial))
                    {
                         cout << endl
                              << " [DONE] Product deleted successfully!" << endl;
                    }
                    else
                    {
                         cout << endl
                              << " [ERROR] There was an error while deleting the product!" << endl;
                    }
                    break;
               }
               case 4: // Edit Product
               {
                    string serial = get_string("Enter the serial of the product", 8, 8);
                    Product product_data = get_product_data();
                    system("clear");

                    if (product_list.edit_item(serial, product_data))
                    {
                         cout << endl
                              << " [DONE] Product updated successfully!" << endl;
                    }
                    else
                    {
                         cout << endl
                              << " [ERROR] There was an error while updating the product!" << endl;
                    }
                    break;
               }
               case 5: // Exit
               {
                    product_list.store();
                    exit(0);
                    break;
               }
               default:
               {
                    system("clear");
                    cout << " [ERROR] Invalid choice" << endl;
                    break;
               }
               }
          }
     }
     else if (auth_level == 1)
     {
          cout << " --------------------------------------------------------------" << endl;
          cout << " |                                                             |" << endl;
          cout << " |                         CASHIER PORTAL                      |" << endl;
          cout << " |                                                             |" << endl;
          cout << " --------------------------------------------------------------" << endl;
          cout << endl
               << " [DONE] Successfully logged in as Cashier!" << endl;

          while (true)
          {
               int choice = cashier_options();

               switch (choice)
               {
               case 1: //  View Products

               {
                    system("clear");
                    product_list.display();
                    break;
               }

               case 2: // New sale
               {
                    system("clear");
                    SaleList cart;

                    while (true)
                    {

                         int sales_choice = sale_options();
                         switch (sales_choice)
                         {
                         case 1: //  View cart

                         {
                              cart.display();
                              break;
                         }
                         case 2: //  Add item to cart

                         {
                              string serial = get_string("Enter the serial of the product", 8, 8);
                              int quantity = get_integer("Enter the quantity", false);

                              Product product_data = product_list.get_item_by_serial(serial);
                              product_data.sale_quantity = quantity;

                              system("clear");

                              if (cart.append(product_data))
                              {
                                   cout << endl
                                        << " [DONE] Product added successfully!" << endl;
                              }
                              else
                              {
                                   cout << endl
                                        << " [ERROR] There was an error while adding the product!" << endl;
                              }

                              break;
                         }

                         case 3: // Remove item from cart
                         {

                              string serial = get_string("Enter the serial of the product", 8, 8);
                              cart.delete_item(serial);
                              break;
                         }
                         case 4: // View product list
                         {
                              system("clear");
                              product_list.display();
                              break;
                         }
                         case 5: // Print the bill
                         {
                              system("clear");
                              float discount = get_integer("Enter the discount", false);
                              cart.print_bill(discount);
                              break;
                         }

                         case 6: // Exit
                         {
                              exit(0);
                              break;
                         }
                         default:
                         {
                              system("clear");
                              cout << " [ERROR] Invalid choice" << endl;
                              break;
                         }
                         }
                    }
               }

               case 3: // Exit
               {
                    product_list.store();
                    exit(0);
                    break;
               }
               default:
               {
                    cout << " [ERROR] Invalid choice" << endl;
                    break;
               }
               }
          }
     }

     return 0;
}
