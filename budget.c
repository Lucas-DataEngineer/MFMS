#include <stdio.h>
#include <string.h>
#include "budget.h"
#include "utils.h"

char departments[MAX_BUDGETS][BUDGET_DEPARTMENT_LEN];
double allocatedBudgets[MAX_BUDGETS];
double expenditures[MAX_BUDGETS];
double remainingBudgets[MAX_BUDGETS];
int budgetCount = 0;

double calculateRemaining(double allocated, double expenditure)
{
    return allocated - expenditure;
}

static double readNonNegativeBudgetValue(const char *prompt)
{
    double value;

    do {
        value = readDoubleSafely(prompt);
        if (value < 0.0) {
            printf("Value cannot be negative. Please try again.\n");
        }
    } while (value < 0.0);

    return value;
}

static int findDepartment(const char *department)
{
    int i;

    for (i = 0; i < budgetCount; i++) {
        if (strcmp(departments[i], department) == 0) {
            return i;
        }
    }

    return -1;
}

void addBudget(void)
{
    char department[BUDGET_DEPARTMENT_LEN];

    if (budgetCount >= MAX_BUDGETS) {
        printf("Budget list is full.\n");
        return;
    }

    printf("\n--- Add Departmental Budget ---\n");
    readNonEmptyLine("Enter Department: ", department, sizeof(department));

    if (findDepartment(department) != -1) {
        printf("A budget for that department already exists.\n");
        return;
    }

    strcpy(departments[budgetCount], department);
    allocatedBudgets[budgetCount] =
        readNonNegativeBudgetValue("Enter Allocated Budget (N$): ");
    expenditures[budgetCount] =
        readNonNegativeBudgetValue("Enter Expenditure (N$): ");
    remainingBudgets[budgetCount] =
        calculateRemaining(allocatedBudgets[budgetCount], expenditures[budgetCount]);

    budgetCount++;
    printf("Budget saved successfully.\n");
}

void displayBudgets(void)
{
    int i;

    if (budgetCount == 0) {
        printf("\nNo budgets recorded.\n");
        return;
    }

    printf("\n========== BUDGET INFORMATION ==========\n");

    for (i = 0; i < budgetCount; i++) {
        printf("\nDepartment: %s\n", departments[i]);
        printf("Allocated Budget: N$%.2f\n", allocatedBudgets[i]);
        printf("Expenditure: N$%.2f\n", expenditures[i]);
        printf("Remaining Budget: N$%.2f\n", remainingBudgets[i]);

        if (expenditures[i] <= allocatedBudgets[i]) {
            printf("Status: WITHIN BUDGET\n");
        } else {
            printf("Status: EXCEEDED\n");
        }
    }
}

void checkExceeding(void)
{
    int i;
    int found = 0;

    printf("\n========== DEPARTMENTS EXCEEDING BUDGET ==========\n");

    for (i = 0; i < budgetCount; i++) {
        if (expenditures[i] > allocatedBudgets[i]) {
            printf("%s - Over by N$%.2f\n",
                   departments[i],
                   expenditures[i] - allocatedBudgets[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("No departments are currently exceeding their budgets.\n");
    }
}

void budgetMenu(void)
{
    int choice;

    do {
        printf("\n========================================\n");
        printf("          BUDGET MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Budget\n");
        printf("2. Display Budgets\n");
        printf("3. Check Exceeding Budgets\n");
        printf("4. Return to Main Menu\n");

        choice = readIntSafely("Enter choice: ");

        switch (choice) {
            case 1:
                addBudget();
                break;
            case 2:
                displayBudgets();
                break;
            case 3:
                checkExceeding();
                break;
            case 4:
                break;
            default:
                printf("Invalid choice. Please select 1 to 4.\n");
        }
    } while (choice != 4);
}

void budgetReport(void)
{
    int i;
    int exceedingCount = 0;
    double totalAllocated = 0.0;
    double totalExpenditure = 0.0;

    printf("\n========== BUDGET REPORT ==========\n");

    for (i = 0; i < budgetCount; i++) {
        totalAllocated += allocatedBudgets[i];
        totalExpenditure += expenditures[i];
        if (expenditures[i] > allocatedBudgets[i]) {
            exceedingCount++;
        }
    }

    printf("Total Allocated Budget: N$%.2f\n", totalAllocated);
    printf("Total Expenditure: N$%.2f\n", totalExpenditure);
    printf("Remaining Budget: N$%.2f\n", totalAllocated - totalExpenditure);
    printf("Departments Exceeding Budget: %d\n", exceedingCount);

    if (exceedingCount > 0) {
        checkExceeding();
    }
}
