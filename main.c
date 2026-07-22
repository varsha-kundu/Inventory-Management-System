#include "inventory.h"

product_details inv[100];
int prod_count = 0;

const char *FILENAME = "system_data.dat";
const char *PASSWORD = "varsha@kv549";

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void clear_screen()
{
    system("cls");
}

int main()
{
    char password[51];
    int attempts = 0;
    int max_attempts = 3;

    while (attempts < max_attempts)
    {
        printf("Enter password: ");
        get_password(password, 51);

        if (strcmp(password, PASSWORD) == 0)
        {
            break;
        }

        attempts++;
        if (attempts < max_attempts)
        {
            printf("Wrong password! %d attempts remaining.\n", max_attempts - attempts);
        }
        else
        {
            printf("Wrong password! Access denied. Maximum attempts exceeded.\n");
            return 1;
        }
    }

    load_inventory();

    int choice;
    do
    {
        clear_screen();
        printf("\n====================================================================================================\n");
        printf("\n====================================================================================================\n");
        printf("                            INVENTORY MANAGEMENT SYSTEM           \n");
        printf("                                    Built by Varsha\n");
        printf("\n====================================================================================================\n");
        printf("\n====================================================================================================\n");
        printf("1. Add Product\n");
        printf("2. Update Product\n");
        printf("3. Delete Product\n");
        printf("4. Display Products\n");
        printf("5. Search Product by ID\n");
        printf("6. Search Product by Name\n");
        printf("7. Search Product by Company\n");
        printf("8. Sort Products by Price\n");
        printf("9. Low Stock Alert\n");
        printf("10. Save Inventory\n");
        printf("11. Load Inventory\n");
        printf("12. Generate Bill\n");
        printf("13. Exit\n");

        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Error: Invalid choice. Please enter a number.\n");
            clear_input_buffer();
            printf("\nPress Enter to continue...");
            getchar();
            continue;
        }
        clear_input_buffer();

        switch (choice)
        {
        case 1:
            add();
            break;
        case 2:
            update();
            break;
        case 3:
            delete_item();
            break;
        case 4:
            display();
            break;
        case 5:
            searchById();
            break;
        case 6:
            searchByName();
            break;
        case 7:
            searchByCompany();
            break;
        case 8:
            sortbyPrice();
            break;
        case 9:
            lowstock_alert();
            break;
        case 10:
            save_inventory();
            break;
        case 11:
            load_inventory();
            break;
        case 12:
            generate_bill();
            break;
        case 13:
            save_inventory();
            printf("Exiting the program.\n");
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }

        if (choice != 13)
        {
            printf("\nPress Enter to continue...");
            getchar();
        }
    } while (choice != 13);

    return 0;
}

void add()
{
    if (prod_count >= 100)
    {
        printf("\nError: Inventory system data is full!\n");
        return;
    }
    printf("\n--- Add New Product ---\n");

    int target_id;
    int id_exists;
    do
    {
        id_exists = 0;
        printf("Enter Product ID: ");
        if (scanf("%d", &target_id) != 1)
        {
            printf("Error: Invalid input.\n");
            clear_input_buffer();
            id_exists = 1;
            continue;
        }
        clear_input_buffer();

        if (target_id <= 0)
        {
            printf("Error: ID must be a number greater than 0.\n");
            id_exists = 1;
            continue;
        }

        for (int i = 0; i < prod_count; i++)
        {
            if (inv[i].id == target_id)
            {
                printf("Error: This ID is already taken! Try another one.\n");
                id_exists = 1;
                break;
            }
        }
    } while (id_exists);

    inv[prod_count].id = target_id;

    printf("Enter Product Name: ");
    if (scanf(" %49[^\n]", inv[prod_count].name) != 1)
    {
        printf("Error: Invalid input.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    printf("Enter Company Name: ");
    if (scanf(" %49[^\n]", inv[prod_count].company) != 1)
    {
        printf("Error: Invalid input.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    printf("Enter Category/Type: ");
    if (scanf(" %49[^\n]", inv[prod_count].type) != 1)
    {
        printf("Error: Invalid input.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    do
    {
        printf("Enter Price: ");
        if (scanf("%f", &inv[prod_count].price) != 1)
        {
            printf("Error: Invalid input. Please enter a number.\n");
            clear_input_buffer();
            inv[prod_count].price = -1;
            continue;
        }
        clear_input_buffer();
        if (inv[prod_count].price < 0)
        {
            printf("Error: Price cannot be negative.\n");
        }
    } while (inv[prod_count].price < 0);

    do
    {
        printf("Enter Quantity: ");
        if (scanf("%d", &inv[prod_count].qty) != 1)
        {
            printf("Error: Invalid input. Please enter a number.\n");
            clear_input_buffer();
            inv[prod_count].qty = -1;
            continue;
        }
        clear_input_buffer();
        if (inv[prod_count].qty < 0)
        {
            printf("Error: Quantity cannot be negative.\n");
        }
    } while (inv[prod_count].qty < 0);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int current_year = tm.tm_year + 1900;
    int current_month = tm.tm_mon + 1;
    int current_day = tm.tm_mday;
    int valid_dates = 0;

    do
    {
        printf("Enter Mfg Date (DD MM YYYY): ");
        if (scanf("%d %d %d", &inv[prod_count].mfg_date.day, &inv[prod_count].mfg_date.month, &inv[prod_count].mfg_date.year) != 3)
        {
            printf("Error: Invalid input. Please enter three numbers.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        printf("Enter Exp Date (DD MM YYYY): ");
        if (scanf("%d %d %d", &inv[prod_count].exp_date.day, &inv[prod_count].exp_date.month, &inv[prod_count].exp_date.year) != 3)
        {
            printf("Error: Invalid input. Please enter three numbers.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        if (inv[prod_count].mfg_date.year < 2000 || inv[prod_count].mfg_date.year > 2099 ||
            inv[prod_count].exp_date.year < 2000 || inv[prod_count].exp_date.year > 2099)
        {
            printf("Error: Year must be between 2000 and 2099. Try again.\n");
            continue;
        }

        if (inv[prod_count].mfg_date.year > current_year ||
           (inv[prod_count].mfg_date.year == current_year && inv[prod_count].mfg_date.month > current_month) ||
           (inv[prod_count].mfg_date.year == current_year && inv[prod_count].mfg_date.month == current_month && inv[prod_count].mfg_date.day > current_day))
        {
            printf("Error: Manufacturing date cannot be in the future! Try again.\n");
            continue;
        }

        if (inv[prod_count].exp_date.year < current_year ||
           (inv[prod_count].exp_date.year == current_year && inv[prod_count].exp_date.month < current_month) ||
           (inv[prod_count].exp_date.year == current_year && inv[prod_count].exp_date.month == current_month && inv[prod_count].exp_date.day < current_day))
        {
            printf("Error: This item is already expired! We do not accept it. Try again.\n");
            continue;
        }

        if (inv[prod_count].exp_date.year < inv[prod_count].mfg_date.year ||
           (inv[prod_count].exp_date.year == inv[prod_count].mfg_date.year && inv[prod_count].exp_date.month < inv[prod_count].mfg_date.month) ||
           (inv[prod_count].exp_date.year == inv[prod_count].mfg_date.year && inv[prod_count].exp_date.month == inv[prod_count].mfg_date.month && inv[prod_count].exp_date.day < inv[prod_count].mfg_date.day))
        {
            printf("Error: Expiry date cannot be before manufacturing date! Try again.\n");
            continue;
        }

        valid_dates = 1;

    } while (!valid_dates);

    prod_count++;

    save_inventory();
    printf("\nSuccess! Product added to the system.\n");
}

void update()
{
    if (prod_count == 0)
    {
        printf("\nInventory system data is empty! Nothing to update.\n");
        return;
    }
    int search_id, found = 0;
    printf("\nEnter Product ID to update: ");
    if (scanf("%d", &search_id) != 1)
    {
        printf("Error: Invalid input.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    for (int i = 0; i < prod_count; i++)
    {
        if (inv[i].id == search_id)
        {
            printf("\nProduct Found: %s\n", inv[i].name);

            do
            {
                printf("Enter New Price: ");
                if (scanf("%f", &inv[i].price) != 1)
                {
                    printf("Error: Invalid input. Please enter a number.\n");
                    clear_input_buffer();
                    inv[i].price = -1;
                    continue;
                }
                clear_input_buffer();
                if (inv[i].price < 0)
                {
                    printf("Error: Price cannot be negative.\n");
                }
            } while (inv[i].price < 0);

            do
            {
                printf("Enter New Quantity: ");
                if (scanf("%d", &inv[i].qty) != 1)
                {
                    printf("Error: Invalid input. Please enter a number.\n");
                    clear_input_buffer();
                    inv[i].qty = -1;
                    continue;
                }
                clear_input_buffer();
                if (inv[i].qty < 0)
                {
                    printf("Error: Quantity cannot be negative.\n");
                }
            } while (inv[i].qty < 0);

            printf("\nSuccess! Product updated successfully.\n");
            found = 1;
            save_inventory();
            break;
        }
    }
    if (!found)
    {
        printf("\nProduct with ID %d not found.\n", search_id);
    }
}

void delete_item()
{
    if (prod_count == 0)
    {
        printf("\nInventory system data is empty! Nothing to delete.\n");
        return;
    }
    int search_id, found = 0;
    printf("\nEnter Product ID to delete: ");
    if (scanf("%d", &search_id) != 1)
    {
        printf("Error: Invalid input.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    for (int i = 0; i < prod_count; i++)
    {
        if (inv[i].id == search_id)
        {
            found = 1;
            for (int j = i; j < prod_count - 1; j++)
            {
                inv[j] = inv[j + 1];
            }
            prod_count--;
            save_inventory();
            printf("\nProduct deleted successfully.\n");
            break;
        }
    }
    if (!found)
    {
        printf("\nProduct with ID %d not found.\n", search_id);
    }
}

void display()
{
    if (prod_count == 0)
    {
        printf("\nInventory system data is empty!\n");
        return;
    }
    printf("\n====================================================================================================\n");
    printf("%-5s | %-15s | %-15s | %-10s | %-8s | %-5s | %-11s | %-11s\n",
           "ID", "Name", "Company", "Type", "Price", "Qty", "Mfg Date", "Exp Date");
    printf("====================================================================================================\n");
    for (int i = 0; i < prod_count; i++)
    {
        printf("%-5d | %-15s | %-15s | %-10s | %-8.2f | %-5d | %02d/%02d/%04d  | %02d/%02d/%04d\n",
               inv[i].id, inv[i].name, inv[i].company, inv[i].type,
               inv[i].price, inv[i].qty,
               inv[i].mfg_date.day, inv[i].mfg_date.month, inv[i].mfg_date.year,
               inv[i].exp_date.day, inv[i].exp_date.month, inv[i].exp_date.year);
    }
    printf("====================================================================================================\n");
}

void searchById()
{
    int search_id, found = 0;
    printf("\nEnter Product ID to search: ");
    if (scanf("%d", &search_id) != 1)
    {
        printf("Error: Invalid input.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    for (int i = 0; i < prod_count; i++)
    {
        if (inv[i].id == search_id)
        {
            printf("\nProduct Found! ID: %d | Name: %s | Company: %s | Price: %.2f | Qty: %d\n",
                   inv[i].id, inv[i].name, inv[i].company, inv[i].price, inv[i].qty);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("\nProduct not found.\n");
    }
}

void searchByName()
{
    char search_name[50];
    int found = 0;
    printf("\nEnter Product Name to search: ");
    if (scanf(" %49[^\n]", search_name) != 1)
    {
        printf("Error: Invalid input.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    for (int i = 0; i < prod_count; i++)
    {
        if (strcmp(inv[i].name, search_name) == 0)
        {
            printf("\nProduct Found! ID: %d | Name: %s | Company: %s | Price: %.2f | Qty: %d\n",
                   inv[i].id, inv[i].name, inv[i].company, inv[i].price, inv[i].qty);
            found = 1;
        }
    }
    if (!found)
    {
        printf("\nProduct not found.\n");
    }
}

void searchByCompany()
{
    char search_comp[50];
    int found = 0;
    printf("\nEnter Company Name to search: ");
    if (scanf(" %49[^\n]", search_comp) != 1)
    {
        printf("Error: Invalid input.\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    for (int i = 0; i < prod_count; i++)
    {
        if (strcmp(inv[i].company, search_comp) == 0)
        {
            printf("\nProduct Found! ID: %d | Name: %s | Company: %s | Price: %.2f | Qty: %d\n",
                   inv[i].id, inv[i].name, inv[i].company, inv[i].price, inv[i].qty);
            found = 1;
        }
    }
    if (!found)
    {
        printf("\nNo products found from that company.\n");
    }
}

void sortbyPrice()
{
    if (prod_count < 2)
    {
        printf("\nNot enough products to sort.\n");
        return;
    }

    product_details temp_inv[100];
    for (int i = 0; i < prod_count; i++)
    {
        temp_inv[i] = inv[i];
    }

    for (int i = 0; i < prod_count - 1; i++)
    {
        for (int j = 0; j < prod_count - i - 1; j++)
        {
            if (temp_inv[j].price > temp_inv[j + 1].price)
            {
                product_details temp = temp_inv[j];
                temp_inv[j] = temp_inv[j + 1];
                temp_inv[j + 1] = temp;
            }
        }
    }

    printf("\nProducts sorted by price (low to high).\n");
    printf("\n====================================================================================================\n");
    printf("%-5s | %-15s | %-15s | %-10s | %-8s | %-5s | %-11s | %-11s\n",
           "ID", "Name", "Company", "Type", "Price", "Qty", "Mfg Date", "Exp Date");
    printf("====================================================================================================\n");
    for (int i = 0; i < prod_count; i++)
    {
        printf("%-5d | %-15s | %-15s | %-10s | %-8.2f | %-5d | %02d/%02d/%04d  | %02d/%02d/%04d\n",
               temp_inv[i].id, temp_inv[i].name, temp_inv[i].company, temp_inv[i].type,
               temp_inv[i].price, temp_inv[i].qty,
               temp_inv[i].mfg_date.day, temp_inv[i].mfg_date.month, temp_inv[i].mfg_date.year,
               temp_inv[i].exp_date.day, temp_inv[i].exp_date.month, temp_inv[i].exp_date.year);
    }
    printf("====================================================================================================\n");
}

void lowstock_alert()
{
    int found = 0;
    printf("\n--- Low Stock Alert (Qty < 20) ---\n");
    for (int i = 0; i < prod_count; i++)
    {
        if (inv[i].qty < 20)
        {
            printf(" Warning: ID %d | Name: %s | Qty: %d (Low Stock!)\n",
                   inv[i].id, inv[i].name, inv[i].qty);
            found = 1;
        }
    }
    if (!found)
    {
        printf("\nAll products have enough stock.\n");
    }
}

void save_inventory()
{
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL)
    {
        printf("\nError: Could not open file for writing.\n");
        return;
    }

    fwrite(&prod_count, sizeof(int), 1, file);
    int write_count = fwrite(inv, sizeof(product_details), prod_count, file);

    fflush(file); 

    if (fclose(file) != 0)
    {
        printf("\nError: Could not close file.\n");
        return;
    }

    printf("\nInventory saved successfully (%d products).\n", write_count);
}

void load_inventory()
{
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL)
    {
        printf("\nNo previous inventory file found. Starting with empty inventory.\n");
        prod_count = 0;
        return;
    }

    if (fread(&prod_count, sizeof(int), 1, file) != 1)
    {
        printf("\nNo products found in inventory file.\n");
        prod_count = 0;
        fclose(file);
        return;
    }

    if (prod_count > 100)
    {
        prod_count = 100;
    }

    int read_count = fread(inv, sizeof(product_details), prod_count, file);

    if (fclose(file) != 0)
    {
        printf("\nWarning: Could not properly close file.\n");
    }

    if (read_count > 0)
    {
        printf("\nInventory loaded successfully (%d products).\n", read_count);
    }
    else
    {
        printf("\nNo products found in inventory file.\n");
        prod_count = 0;
    }
}

void generate_bill()
{
    if (prod_count == 0)
    {
        printf("\nInventory system data is empty!\n");
        return;
    }

    purchase purchases[100];
    int purchase_count = 0;
    float grand_total = 0;
    int add_more = 1;

    printf("\n--- Generate Bill ---\n");

    while (add_more && purchase_count < 100)
    {
        int search_id, bought_qty, found = 0;

        printf("\nEnter Product ID to purchase (or 0 to finish): ");
        if (scanf("%d", &search_id) != 1)
        {
            printf("Error: Invalid input.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        if (search_id == 0)
        {
            break;
        }

        for (int i = 0; i < prod_count; i++)
        {
            if (inv[i].id == search_id)
            {
                found = 1;
                printf("Product: %s | Price: %.2f | Available Qty: %d\n",
                       inv[i].name, inv[i].price, inv[i].qty);

                printf("Enter quantity to buy: ");
                if (scanf("%d", &bought_qty) != 1 || bought_qty <= 0)
                {
                    printf("Error: Invalid quantity.\n");
                    clear_input_buffer();
                    break;
                }
                clear_input_buffer();

                if (bought_qty > inv[i].qty)
                {
                    printf("Error: Not enough stock available.\n");
                    break;
                }
                purchases[purchase_count].prod_index = i;
                purchases[purchase_count].bought_qty = bought_qty;
                purchase_count++;

                printf("Product added to bill.\n");
                break;
            }
        }

        if (!found && search_id != 0)
        {
            printf("Product with ID %d not found.\n", search_id);
        }
    }

    if (purchase_count == 0)
    {
        printf("\nNo products added to bill.\n");
        return;
    }

    for (int i = 0; i < purchase_count; i++)
    {
        int idx = purchases[i].prod_index;
        inv[idx].qty -= purchases[i].bought_qty;
        grand_total += inv[idx].price * purchases[i].bought_qty;
    }

    FILE *bill_file = fopen("bill.txt", "w");
    if (bill_file == NULL)
    {
        printf("\nError: Could not create bill.\n");
        return;
    }

    fprintf(bill_file, "============================================================\n");
    fprintf(bill_file, "                     CUSTOMER INVOICE                       \n");
    fprintf(bill_file, "============================================================\n");
    fprintf(bill_file, "%-5s | %-20s | %-8s | %-4s | %-10s\n", "S.No", "Item Name", "Price", "Qty", "Total");
    fprintf(bill_file, "------------------------------------------------------------\n");

    for (int i = 0; i < purchase_count; i++)
    {
        int idx = purchases[i].prod_index;
        float item_total = inv[idx].price * purchases[i].bought_qty;
        fprintf(bill_file, "%-5d | %-20s | %-8.2f | %-4d | %-10.2f\n",
                i + 1, inv[idx].name, inv[idx].price, purchases[i].bought_qty, item_total);
    }

    fprintf(bill_file, "============================================================\n");
    fprintf(bill_file, "GRAND TOTAL:                                     %-10.2f\n", grand_total);
    fprintf(bill_file, "============================================================\n");
    fprintf(bill_file, "Thank you for shopping with us!\n");

    fflush(bill_file); 
    fclose(bill_file);

    save_inventory();

    printf("Success! Bill generated as 'bill.txt'\n");
    printf("\n========================================================\n");
    printf("Total Items: %d\n", purchase_count);
    printf("Grand Total: %.2f\n", grand_total);
    printf("Inventory updated.\n");
    printf("========================================================\n");
}

void get_password(char *password, int max_length)
{
    int i = 0;
    int ch;
    while ((ch = getch()) != '\r' && i < max_length - 1)
    {
        if (ch == '\b')
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
}
