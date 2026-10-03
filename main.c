#include <stdio.h>
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "reports.h"
#include "utils.h"

static void mainMenu(void)
{
    int choice;

    do {
        printf("\n========================================\n");
        printf(" MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
        printf("========================================\n");
        printf("1. Employee Management\n");
        printf("2. Budget Management\n");
        printf("3. Supplier Management\n");
        printf("4. Asset Management\n");
        printf("5. Reports\n");
        printf("6. Exit\n");

        choice = readIntSafely("Enter your choice: ");

        switch (choice) {
            case 1:
                employeeManagementMenu();
                break;
            case 2:
                budgetMenu();
                break;
            case 3:
                supplierMenu();
                break;
            case 4:
                assetMenu();
                break;
            case 5:
                reportsMenu();
                break;
            case 6:
                printf("\nThank you for using the MFMS.\n");
                break;
            default:
                printf("Invalid choice. Please select 1 to 6.\n");
        }
    } while (choice != 6);
}

int main(void)
{
    mainMenu();
    return 0;
}
