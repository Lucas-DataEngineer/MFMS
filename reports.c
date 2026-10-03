#include <stdio.h>
#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"
#include "utils.h"

void reportsMenu(void)
{
    int choice;

    do {
        printf("\n========================================\n");
        printf("              REPORTS\n");
        printf("========================================\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Full MFMS Report\n");
        printf("6. Return to Main Menu\n");

        choice = readIntSafely("Enter choice: ");

        switch (choice) {
            case 1:
                employeeReport();
                break;
            case 2:
                budgetReport();
                break;
            case 3:
                supplierReport();
                break;
            case 4:
                assetReport();
                break;
            case 5:
                printf("\n========== FULL MFMS REPORT ==========\n");
                employeeReport();
                budgetReport();
                supplierReport();
                assetReport();
                printf("========== END OF FULL REPORT ==========\n");
                break;
            case 6:
                break;
            default:
                printf("Invalid choice. Please select 1 to 6.\n");
        }
    } while (choice != 6);
}
