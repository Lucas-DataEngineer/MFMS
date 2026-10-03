# Municipal Financial Management System (MFMS)

## PAP521S - Programming in Practice - Project A

This is the integrated C99 version of the Municipal Financial Management System.

## Files

- `main.c` - main system menu and program entry point
- `employees.c/.h` - employee management and employee report
- `budget.c/.h` - budget management and budget report
- `suppliers.c/.h` - supplier management, search, comparison and supplier report
- `assets.c/.h` - asset register, search and asset report
- `reports.c/.h` - central reports menu
- `types.h` - shared data types
- `utils.c/.h` - safe input functions used by the modules

## Compile with GCC

```bash
gcc -std=c99 -Wall -Wextra -pedantic main.c employees.c budget.c suppliers.c assets.c reports.c utils.c -o MFMS
```

## Run on Windows

```powershell
.\MFMS.exe
```

## Run on Linux/macOS

```bash
./MFMS
```

## Main system flow

`main()` -> `mainMenu()` -> selected module menu -> module functions -> return to main menu.

The Reports module calls the public report functions from the other modules.

## Validation included

- Invalid menu choices are rejected.
- Non-numeric integer input is rejected.
- Invalid numeric input is rejected.
- Negative salaries, allowances, budgets, expenditure and asset values are rejected.
- Empty required text fields are rejected.
- Duplicate employee, supplier, asset and budget identifiers are rejected.

## Important

The program stores records in memory while it is running. Closing the program clears the records because no file/database storage was required for Project A.
