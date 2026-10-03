#ifndef BUDGET_H
#define BUDGET_H

#define MAX_BUDGETS 100
#define BUDGET_DEPARTMENT_LEN 50

extern char departments[MAX_BUDGETS][BUDGET_DEPARTMENT_LEN];
extern double allocatedBudgets[MAX_BUDGETS];
extern double expenditures[MAX_BUDGETS];
extern double remainingBudgets[MAX_BUDGETS];
extern int budgetCount;

void addBudget(void);
void displayBudgets(void);
void checkExceeding(void);
double calculateRemaining(double allocated, double expenditure);
void budgetMenu(void);
void budgetReport(void);

#endif
