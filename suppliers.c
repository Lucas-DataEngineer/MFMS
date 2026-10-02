/* ============================================================
 * suppliers.c - Supplier Management Module
 * PAP521S - Programming in Practice - Project A
 * ============================================================ */

#include <stdio.h>
#include <string.h>
#include "type.h"
#include "mfms.h"
#include "suppliers.h"
#include "utils.h"

/* ============================================================
 * SUPPLIER DATA (private to this file)
 * ============================================================ */
static int   supplierIDs[MAX_SUPPLIERS];
static char  supplierNames[MAX_SUPPLIERS][NAME_LEN];
static char  supplierEmails[MAX_SUPPLIERS][NAME_LEN];
static char  supplierPhones[MAX_SUPPLIERS][TINY_LEN];
static char  supplierTowns[MAX_SUPPLIERS][SMALL_LEN];
static int   supplierCount = 0;

/* ============================================================
 * ADD SUPPLIER
 * ============================================================ */
void addSupplier(void)
{
    if (supplierCount >= MAX_SUPPLIERS)
    {
        printf("Supplier list is full.\n");
        return;
    }

    int id = readIntSafely("Enter Supplier ID: ");

    for (int i = 0; i < supplierCount; i++)
    {
        if (supplierIDs[i] == id)
        {
            printf("Supplier ID already exists.\n");
            return;
        }
    }

    char name[NAME_LEN];

    do
    {
        readLine("Enter Supplier Name: ", name, NAME_LEN);

        if (strlen(name) == 0)
            printf("Name cannot be empty.\n");

    } while (strlen(name) == 0);

    supplierIDs[supplierCount] = id;
    strcpy(supplierNames[supplierCount], name);

    readLine("Enter Email: ", supplierEmails[supplierCount], NAME_LEN);
    readLine("Enter Telephone: ", supplierPhones[supplierCount], TINY_LEN);
    readLine("Enter Town/Location: ", supplierTowns[supplierCount], SMALL_LEN);

    supplierCount++;
    printf("Supplier added successfully.\n");
}

/* ============================================================
 * DISPLAY SUPPLIERS
 * ============================================================ */
void displaySuppliers(void)
{
    if (supplierCount == 0)
    {
        printf("No suppliers available.\n");
        return;
    }

    for (int i = 0; i < supplierCount; i++)
    {
        printf("\nID: %d\n",      supplierIDs[i]);
        printf("Name: %s\n",      supplierNames[i]);
        printf("Email: %s\n",     supplierEmails[i]);
        printf("Telephone: %s\n", supplierPhones[i]);
        printf("Town: %s\n",      supplierTowns[i]);
    }

    printf("\nTotal Suppliers: %d\n", supplierCount);
}

/* ============================================================
 * SEARCH SUPPLIER (by ID)
 * ============================================================ */
void searchSupplier(void)
{
    int id = readIntSafely("Enter Supplier ID: ");

    for (int i = 0; i < supplierCount; i++)
    {
        if (supplierIDs[i] == id)
        {
            printf("\nSupplier Found\n");
            printf("Name: %s\n",      supplierNames[i]);
            printf("Email: %s\n",     supplierEmails[i]);
            printf("Telephone: %s\n", supplierPhones[i]);
            printf("Town: %s\n",      supplierTowns[i]);
            return;
        }
    }

    printf("Supplier not found.\n");
}

/* ============================================================
 * COMPARE TWO SUPPLIERS (by town)
 * ============================================================ */
void compareSuppliers(void)
{
    int id1 = readIntSafely("Enter first Supplier ID: ");
    int id2 = readIntSafely("Enter second Supplier ID: ");

    int first  = -1;
    int second = -1;

    for (int i = 0; i < supplierCount; i++)
    {
        if (supplierIDs[i] == id1) first  = i;
        if (supplierIDs[i] == id2) second = i;
    }

    if (first == -1 || second == -1)
    {
        printf("Supplier not found.\n");
        return;
    }

    if (strcmp(supplierTowns[first], supplierTowns[second]) == 0)
    {
        printf("Both suppliers are in the same town.\n");
    }
    else
    {
        printf("Suppliers are in different towns.\n");
    }
}
