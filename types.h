#ifndef TYPES_H
#define TYPES_H

#define NAME_LEN 50
#define SMALL_LEN 50
#define TINY_LEN 30

/* Employee record */
typedef struct {
    char employeeID[15];
    char name[NAME_LEN];
    char department[NAME_LEN];
    float basicSalary;
    float housingAllowance;
    float transportAllowance;
} Employee;

/* Supplier record */
typedef struct {
    int supplierId;
    char supplierName[NAME_LEN];
    char email[NAME_LEN];
    char phone[TINY_LEN];
    char town[SMALL_LEN];
} Supplier;

/* Asset record */
typedef struct {
    int assetId;
    char assetName[NAME_LEN];
    char assetType[NAME_LEN];
    double purchaseValue;
    char department[NAME_LEN];
    char condition[NAME_LEN];
} Asset;

#endif
