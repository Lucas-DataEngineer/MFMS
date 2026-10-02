#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "employees.h"

static void clearInputBuffer(void);
static int isValidSalary(float salary);
static int findEmployeeIndex(const Employee employees[], int count, const char *searchID);


static void addEmployee(Employee employees[], int *count) {
    if (*count >= MAX_EMPLOYEES) {
        printf("\n[Error] Maximum capacity reached (%d).\n", MAX_EMPLOYEES);
        return;
    }

    Employee newEmp;

    printf("\n*** Add New Employee ***\n");

    printf("Enter Employee ID: ");
    if (scanf("%14s", newEmp.employeeID) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (findEmployeeIndex(employees, *count, newEmp.employeeID) != -1) {
        printf("An employee with ID '%s' already exists!\n", newEmp.employeeID);
        return;
    }

    printf("Enter Full Name: ");
    if (fgets(newEmp.name, sizeof(newEmp.name), stdin) != NULL) {
        newEmp.name[strcspn(newEmp.name, "\n")] = 0;
    }
    if (strlen(newEmp.name) == 0) {
        printf("Employee name cannot be empty!\n");
        return;
    }

    printf("Enter Department: ");
    if (fgets(newEmp.department, sizeof(newEmp.department), stdin) != NULL) {
        newEmp.department[strcspn(newEmp.department, "\n")] = 0;
    }
    if (strlen(newEmp.department) == 0) {
        strcpy(newEmp.department, "General");
    }

    printf("Enter Basic Salary: ");
    if (scanf("%f", &newEmp.basicSalary) != 1 || !isValidSalary(newEmp.basicSalary)) {
        printf("Invalid basic salary entered. Must be a positive number.\n");
        clearInputBuffer();
        return;
    }

    printf("Enter Housing Allowance: ");
    if (scanf("%f", &newEmp.housingAllowance) != 1 || !isValidSalary(newEmp.housingAllowance)) {
        printf("Invalid housing allowance entered.\n");
        clearInputBuffer();
        return;
    }

    printf("Enter Transport Allowance: ");
    if (scanf("%f", &newEmp.transportAllowance) != 1 || !isValidSalary(newEmp.transportAllowance)) {
        printf("Invalid transport allowance entered.\n");
        clearInputBuffer();
        return;
    }

   
    clearInputBuffer();

    employees[*count] = newEmp;
    (*count)++;
    printf("\n[Success] Employee added successfully!\n");
}

static void displayEmployees(const Employee employees[], int count) {
    if (count == 0) {
        printf("\nNo employee records found.\n");
        return;
    }

    printf("\n*** EMPLOYEE LIST ***\n");
    printf("%-12s | %-20s | %-15s | %-12s\n", "ID", "Name", "Department", "Basic Salary");

    for (int i = 0; i < count; i++) {
        printf("%-12s | %-20s | %-15s | N$%-10.2f\n",employees[i].employeeID,employees[i].name,employees[i].department,employees[i].basicSalary);
    }
}

static void searchEmployee(const Employee employees[], int count) {
    if (count == 0) {
        printf("\n[Info] No employee records available to search.\n");
        return;
    }

    char searchID[15];
    printf("\nEnter Employee ID to search: ");
    if (scanf("%14s", searchID) != 1) {
        printf("[Error] Invalid input.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    int index = findEmployeeIndex(employees, count, searchID);
    if (index != -1) {
        printf("\n[Found] Employee record located:\n");
        printf("*****************************************\n");
        printf("ID:         %s\n", employees[index].employeeID);
        printf("Name:       %s\n", employees[index].name);
        printf("Department: %s\n", employees[index].department);
        printf("Basic:      N$%.2f\n", employees[index].basicSalary);
        printf("*****************************************\n");
    } else {
        printf("\n[Result] Employee with ID '%s' was not found.\n", searchID);
    }
}

static void calculateSalary(const Employee employees[], int count) {
    if (count == 0) {
        printf("\n[Info] No employee records available for salary calculations.\n");
        return;
    }

    char searchID[15];
    printf("\nEnter Employee ID for salary calculation: ");
    if (scanf("%14s", searchID) != 1) {
        printf("[Error] Invalid input.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    int index = findEmployeeIndex(employees, count, searchID);
    if (index != -1) {
        float grossSalary = employees[index].basicSalary +
                            employees[index].housingAllowance +
                            employees[index].transportAllowance +

        printf("\n*************** SALARY BREAKDOWN ******************\n");
        printf("Employee Name: %s\n", employees[index].name);
        printf("Basic Salary:  N$%.2f\n", employees[index].basicSalary);
        printf("Housing Allowance:  N$%.2f\n", employees[index].housingAllowance);
        printf("Transport Allowance:N$%.2f\n", employees[index].transportAllowance);
        printf("*****************************************************\n");
        printf("Gross Salary:       N$%.2f\n", grossSalary);
    } else {
        printf("\n[Result] Employee with ID '%s' was not found.\n", searchID);
    }
}

static void displayEmployeeDetails(const Employee employees[], int count) {
    if (count == 0) {
        printf("\n[Info] No employee records available.\n");
        return;
    }

    char searchID[15];
    printf("\nEnter Employee ID to view full details: ");
    if (scanf("%14s", searchID) != 1) {
        printf("[Error] Invalid input.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    int index = findEmployeeIndex(employees, count, searchID);
    if (index != -1) {
        printf("\n**************** COMPLETE EMPLOYEE RECORD ******************\n");
        printf("Employee ID: %s\n", employees[index].employeeID);
        printf("Full Name: %s\n", employees[index].name);
        printf("Department: %s\n", employees[index].department);
        printf("Basic Salary: N$%.2f\n", employees[index].basicSalary);
        printf("Housing Allowance: N$%.2f\n", employees[index].housingAllowance);
        printf("Transport Allowance: N$%.2f\n", employees[index].transportAllowance);
        printf("**************************************************************\n");
    } else {
        printf("\n[Result] Employee with ID '%s' was not found.\n", searchID);
    }
}


static void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static int isValidSalary(float salary) {
    return salary >= 0.0f;
}

static int findEmployeeIndex(const Employee employees[], int count, const char *searchID) {
    for (int i = 0; i < count; i++) {
        if (strcmp(employees[i].employeeID, searchID) == 0) {
            return i; 
        }
    }
    return -1;
}

void employeeManagementMenu(void) {
    Employee employees[MAX_EMPLOYEES];
    int employeeCount = 0;
    int choice;

    do {
        printf("\n*** EMPLOYEE MANAGEMENT ***\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Calculate Salary\n");
        printf("5. Employee Details\n");
        printf("6. Return to Main Menu\n");

        printf("Enter choice (1-6): ");

        if (scanf("%d", &choice) != 1) {
            printf("\n[Error] Invalid choice. Please enter a number between 1 and 6.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                addEmployee(employees, &employeeCount);
                break;
            case 2:
                displayEmployees(employees, employeeCount);
                break;
            case 3:
                 searchEmployee(employees, employeeCount); 
                 break;
            case 4:
                calculateSalary(employees, employeeCount);
                break;
            case 5:
                displayEmployeeDetails(employees, employeeCount);
                break;
            case 6:
                printf("\nReturning to Main Menu...\n");
                break;
            default:
                printf("\n[Error] Invalid option! Please choose between 1 and 6.\n");
        }
    } while (choice != 6);
}