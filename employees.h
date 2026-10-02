#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#define MAX_EMPLOYEES 100
#define MAX_STRING_LEN 50

typedef struct {
    char employeeID[15];
    char name[MAX_STRING_LEN];
    char department[MAX_STRING_LEN];
    float basicSalary;
    float housingAllowance;
    float transportAllowance;
} Employee;

void employeeManagementMenu(void);

#endif