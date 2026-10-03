#include <stdio.h>
#include <string.h>
#include "suppliers.h"
#include "utils.h"

typedef struct {
    int id;
    char name[SUPPLIER_NAME_LEN];
    char email[SUPPLIER_NAME_LEN];
    char phone[SUPPLIER_PHONE_LEN];
    char town[SUPPLIER_TOWN_LEN];
} SupplierRecord;

static SupplierRecord suppliers[MAX_SUPPLIERS];
static int supplierCount = 0;

static int findSupplierIndex(int id)
{
    int i;

    for (i = 0; i < supplierCount; i++) {
        if (suppliers[i].id == id) {
            return i;
        }
    }

    return -1;
}

void addSupplier(void)
{
    int id;

    if (supplierCount >= MAX_SUPPLIERS) {
        printf("Supplier list is full.\n");
        return;
    }

    printf("\n--- Add Supplier ---\n");
    id = readIntSafely("Enter Supplier ID: ");

    if (findSupplierIndex(id) != -1) {
        printf("Supplier ID already exists.\n");
        return;
    }

    suppliers[supplierCount].id = id;
    readNonEmptyLine("Enter Supplier Name: ",
                     suppliers[supplierCount].name,
                     sizeof(suppliers[supplierCount].name));
    readLine("Enter Email: ", suppliers[supplierCount].email,
             sizeof(suppliers[supplierCount].email));
    readLine("Enter Telephone: ", suppliers[supplierCount].phone,
             sizeof(suppliers[supplierCount].phone));
    readNonEmptyLine("Enter Town/Location: ",
                     suppliers[supplierCount].town,
                     sizeof(suppliers[supplierCount].town));

    supplierCount++;
    printf("Supplier added successfully.\n");
}

void displaySuppliers(void)
{
    int i;

    if (supplierCount == 0) {
        printf("\nNo suppliers available.\n");
        return;
    }

    printf("\n========== SUPPLIER REPORT ==========\n");

    for (i = 0; i < supplierCount; i++) {
        printf("\nSupplier ID: %d\n", suppliers[i].id);
        printf("Supplier Name: %s\n", suppliers[i].name);
        printf("Email: %s\n", suppliers[i].email);
        printf("Telephone: %s\n", suppliers[i].phone);
        printf("Town/Location: %s\n", suppliers[i].town);
    }

    printf("\nTotal Suppliers: %d\n", supplierCount);
}

void searchSupplier(void)
{
    int id;
    int index;

    if (supplierCount == 0) {
        printf("\nNo suppliers available to search.\n");
        return;
    }

    id = readIntSafely("Enter Supplier ID to search: ");
    index = findSupplierIndex(id);

    if (index == -1) {
        printf("Supplier not found.\n");
        return;
    }

    printf("\nSupplier Found\n");
    printf("ID: %d\n", suppliers[index].id);
    printf("Name: %s\n", suppliers[index].name);
    printf("Email: %s\n", suppliers[index].email);
    printf("Telephone: %s\n", suppliers[index].phone);
    printf("Town: %s\n", suppliers[index].town);
}

void compareSuppliers(void)
{
    int id1;
    int id2;
    int first;
    int second;

    if (supplierCount < 2) {
        printf("At least two suppliers are required for comparison.\n");
        return;
    }

    id1 = readIntSafely("Enter first Supplier ID: ");
    id2 = readIntSafely("Enter second Supplier ID: ");

    first = findSupplierIndex(id1);
    second = findSupplierIndex(id2);

    if (first == -1 || second == -1) {
        printf("One or both supplier IDs were not found.\n");
        return;
    }

    printf("\n--- Supplier Comparison ---\n");
    printf("Supplier 1: %s (%s)\n", suppliers[first].name, suppliers[first].town);
    printf("Supplier 2: %s (%s)\n", suppliers[second].name, suppliers[second].town);

    if (strcmp(suppliers[first].town, suppliers[second].town) == 0) {
        printf("Both suppliers are in the same town.\n");
    } else {
        printf("Suppliers are in different towns.\n");
    }
}

void supplierMenu(void)
{
    int choice;

    do {
        printf("\n========================================\n");
        printf("         SUPPLIER MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Compare Suppliers\n");
        printf("5. Return to Main Menu\n");

        choice = readIntSafely("Enter choice: ");

        switch (choice) {
            case 1:
                addSupplier();
                break;
            case 2:
                displaySuppliers();
                break;
            case 3:
                searchSupplier();
                break;
            case 4:
                compareSuppliers();
                break;
            case 5:
                break;
            default:
                printf("Invalid choice. Please select 1 to 5.\n");
        }
    } while (choice != 5);
}

void supplierReport(void)
{
    displaySuppliers();
}
