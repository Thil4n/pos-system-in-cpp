#include "product.h"

#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

bool validate_integer(std::string str, bool is_signed);
int get_integer(std::string txt, bool is_signed);
std::string get_string(std::string txt, int min_len, int max_len);
std::string get_suffix(int i);

void welcome();
int login();

int admin_options();
int cashier_options();
int sale_options();
Product get_product_data();
#endif