#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

typedef struct
{
    int day;
    int month;
    int year;
} date;

typedef struct
{
    int id;
    char name[50];
    char company[50];
    char type[50];
    float price;
    int qty;
    date mfg_date;
    date exp_date;
} product_details;

typedef struct
{
    int prod_index;
    int bought_qty;
} purchase;

void add();
void update();
void delete_item();
void display();
void searchById();
void searchByName();
void searchByCompany();
void sortbyPrice();
void lowstock_alert();
void save_inventory();
void load_inventory();
void generate_bill();
void clear_screen();
void clear_input_buffer();
void get_password(char *password, int max_length);


#endif 