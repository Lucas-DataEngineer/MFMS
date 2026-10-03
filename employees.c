#include <stdio.h>
#include <string.h>
#include "employees.h"
#include "utils.h"

static Employee employees[MAX_EMPLOYEES];
static int employeeCount = 0;

static int findEmployeeIndex(const char *searchID)
{
    int i;

    for (i = 0; i < employeeCount; i++) {
        if (strcmp(employees[i].employeeID, searchID) == 0) {
            return i;
        }
    }

    return -1;
}

static double calculateGrossSalary(const Employee *employee)
{
    return employee->basicSalary +
           employee->housingAllowance +
           employee->transportAllowance;
}

static double readNonNegativeAmount(const char *prompt)
{
    double value;

    do {
        value = readDoubleSafely(prompt);
        if (value < 0.0) {
            printf("Amount cannot be negative. Please try again.\n");
        }
    } while (value < 0.0);

    return value;
}

static void addEmployee(void)
{
    Employee newEmployee;

    if (employeeCount >= MAX_EMPLOYEES) {
        printf("Employee list is full.\n");
        return;
    }

    printf("\n--- Add Employee ---\n");
    readNonEmptyLine("Enter Employee ID: ", newEmployee.employeeID,
                     sizeof(newEmployee.employeeID));

    if (findEmployeeIndex(newEmployee.employeeID) != -1) {
        printf("An employee with that ID already exists.\n");
        return;
    }

    readNonEmptyLine("Enter Full Name: ", newEmployee.name,
                     sizeof(newEmployee.name));
    readNonEmptyLine("Enter Department: ", newEmployee.department,
                     sizeof(newEmployee.department));

    newEmployee.basicSalary = (float)readNonNegativeAmount("Enter Basic Salary (N$): ");
    newEmployee.housingAllowance =
        (float)readNonNegativeAmount("Enter Housing Allowance (N$): ");
    newEmployee.transportAllowance =
        (float)readNonNegativeAmount("Enter Transport Allowance (N$): ");

    employees[employeeCount] = newEmployee;
    employeeCount++;

    printf("Employee added successfully.\n");
}

static void displayEmployees(void)
{
    int i;

    if (employeeCount == 0) {
        printf("\nNo employee records found.\n");
        return;
    }

    printf("\n--- Employee List ---\n");
    printf("%-12s %-20s %-18s %-15s\n",
           "ID", "Name", "Department", "Basic Salary");
    printf("---------------------------------------------------------------------\n");

    for (i = 0; i < employeeCount; i++) {
        printf("%-12s %-20s %-18s N$%-12.2f\n",
               employees[i].employeeID,
               employees[i].name,
               employees[i].department,
               employees[i].basicSalary);
    }
}

static void searchEmployee(void)
{
    char searchID[15];
    int index;

    if (employeeCount == 0) {
        printf("\nNo employee records available.\n");
        return;
    }

    readNonEmptyLine("Enter Employee ID to search: ", searchID,
                     sizeof(searchID));
    index = findEmployeeIndex(searchID);

    if (index == -1) {
        printf("Employee with ID '%s' was not found.\n", searchID);
        return;
    }

    printf("\nEmployee found:\n");
    printf("ID: %s\n", employees[index].employeeID);
    printf("Name: %s\n", employees[index].name);
    printf("Department: %s\n", employees[index].department);
    printf("Basic Salary: N$%.2f\n", employees[index].basicSalary);
    printf("Housing Allowance: N$%.2f\n", employees[index].housingAllowance);
    printf("Transport Allowance: N$%.2f\n",
           employees[index].transportAllowance);
}

static void calculateSalary(void)
{
    char searchID[15];
    int index;
    double grossSalary;

    if (employeeCount == 0) {
        printf("\nNo employee records available.\n");
        return;
    }

    readNonEmptyLine("Enter Employee ID for salary calculation: ",
                     searchID, sizeof(searchID));
    index = findEmployeeIndex(searchID);

    if (index == -1) {
        printf("Employee with ID '%s' was not found.\n", searchID);
        return;
    }

    grossSalary = calculateGrossSalary(&employees[index]);

    printf("\n--- Salary Breakdown ---\n");
    printf("Employee Name: %s\n", employees[index].name);
    printf("Basic Salary: N$%.2f\n", employees[index].basicSalary);
    printf("Housing Allowance: N$%.2f\n", employees[index].housingAllowance);
    printf("Transport Allowance: N$%.2f\n", employees[index].transportAllowance);
    printf("Gross Salary: N$%.2f\n", grossSalary);
}

static void displayEmployeeDetails(void)
{
    char searchID[15];
    int index;

    if (employeeCount == 0) {
        printf("\nNo employee records available.\n");
        return;
    }

    readNonEmptyLine("Enter Employee ID for full details: ",
                     searchID, sizeof(searchID));
    index = findEmployeeIndex(searchID);

    if (index == -1) {
        printf("Employee with ID '%s' was not found.\n", searchID);
        return;
    }

    printf("\n--- Complete Employee Record ---\n");
    printf("Employee ID: %s\n", employees[index].employeeID);
    printf("Full Name: %s\n", employees[index].name);
    printf("Department: %s\n", employees[index].department);
    printf("Basic Salary: N$%.2f\n", employees[index].basicSalary);
    printf("Housing Allowance: N$%.2f\n", employees[index].housingAllowance);
    printf("Transport Allowance: N$%.2f\n",
           employees[index].transportAllowance);
    printf("Gross Salary: N$%.2f\n",
           calculateGrossSalary(&employees[index]));
}

void employeeManagementMenu(void)
{
    int choice;

    do {
        printf("\n========================================\n");
        printf("        EMPLOYEE MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Calculate Salary\n");
        printf("5. Employee Details\n");
        printf("6. Return to Main Menu\n");

        choice = readIntSafely("Enter choice: ");

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                displayEmployees();
                break;
            case 3:
                searchEmployee();
                break;
            case 4:
                calculateSalary();
                break;
            case 5:
                displayEmployeeDetails();
                break;
            case 6:
                break;
            default:
                printf("Invalid choice. Please select 1 to 6.\n");
        }
    } while (choice != 6);
}

void employeeReport(void)
{
    int i;
    double totalSalary = 0.0;
    double highestSalary = 0.0;
    double lowestSalary = 0.0;

    printf("\n========== EMPLOYEE REPORT ==========\n");

    if (employeeCount == 0) {
        printf("Total Employees: 0\n");
        printf("No salary data available.\n");
        return;
    }

    lowestSalary = calculateGrossSalary(&employees[0]);
    highestSalary = lowestSalary;

    for (i = 0; i < employeeCount; i++) {
        double salary = calculateGrossSalary(&employees[i]);

        totalSalary += salary;
        if (salary > highestSalary) {
            highestSalary = salary;
        }
        if (salary < lowestSalary) {
            lowestSalary = salary;
        }
    }

    printf("Total Employees: %d\n", employeeCount);
    printf("Average Salary: N$%.2f\n", totalSalary / employeeCount);
    printf("Highest Salary: N$%.2f\n", highestSalary);
    printf("Lowest Salary: N$%.2f\n", lowestSalary);
}
