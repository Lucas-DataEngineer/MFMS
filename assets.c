#include <stdio.h>
#include <string.h>
#include "assets.h"
#include "utils.h"

static Asset assets[MAX_ASSETS];
static int assetCount = 0;

static int findAssetById(int id)
{
    int i;

    for (i = 0; i < assetCount; i++) {
        if (assets[i].assetId == id) {
            return i;
        }
    }

    return -1;
}

static double readNonNegativeAssetValue(const char *prompt)
{
    double value;

    do {
        value = readDoubleSafely(prompt);
        if (value < 0.0) {
            printf("Purchase value cannot be negative. Please try again.\n");
        }
    } while (value < 0.0);

    return value;
}

void addAsset(void)
{
    Asset newAsset;

    if (assetCount >= MAX_ASSETS) {
        printf("Asset list is full.\n");
        return;
    }

    printf("\n--- Add Asset ---\n");
    newAsset.assetId = readIntSafely("Enter Asset ID: ");

    if (findAssetById(newAsset.assetId) != -1) {
        printf("Asset ID already exists.\n");
        return;
    }

    readNonEmptyLine("Enter Asset Name: ", newAsset.assetName,
                     sizeof(newAsset.assetName));
    readNonEmptyLine("Enter Asset Type: ", newAsset.assetType,
                     sizeof(newAsset.assetType));
    newAsset.purchaseValue =
        readNonNegativeAssetValue("Enter Purchase Value (N$): ");
    readNonEmptyLine("Enter Department: ", newAsset.department,
                     sizeof(newAsset.department));
    readNonEmptyLine("Enter Condition: ", newAsset.condition,
                     sizeof(newAsset.condition));

    assets[assetCount] = newAsset;
    assetCount++;

    printf("Asset added successfully.\n");
}

void displayAssets(void)
{
    int i;

    if (assetCount == 0) {
        printf("\nNo assets recorded.\n");
        return;
    }

    printf("\n========== ASSET REGISTER ==========\n");
    printf("%-6s %-18s %-15s %-14s %-15s %-15s\n",
           "ID", "Name", "Type", "Value", "Department", "Condition");
    printf("--------------------------------------------------------------------------------\n");

    for (i = 0; i < assetCount; i++) {
        printf("%-6d %-18s %-15s N$%-11.2f %-15s %-15s\n",
               assets[i].assetId,
               assets[i].assetName,
               assets[i].assetType,
               assets[i].purchaseValue,
               assets[i].department,
               assets[i].condition);
    }
}

void searchAsset(void)
{
    char query[NAME_LEN];
    int searchId;
    int idIsValid;
    int i;
    int found = 0;

    if (assetCount == 0) {
        printf("\nNo assets available to search.\n");
        return;
    }

    readNonEmptyLine("Enter Asset ID or Asset Name: ", query, sizeof(query));
    idIsValid = sscanf(query, "%d", &searchId) == 1;

    for (i = 0; i < assetCount; i++) {
        if ((idIsValid && assets[i].assetId == searchId) ||
            strcmp(assets[i].assetName, query) == 0) {
            printf("\nAsset Found\n");
            printf("ID: %d\n", assets[i].assetId);
            printf("Name: %s\n", assets[i].assetName);
            printf("Type: %s\n", assets[i].assetType);
            printf("Purchase Value: N$%.2f\n", assets[i].purchaseValue);
            printf("Department: %s\n", assets[i].department);
            printf("Condition: %s\n", assets[i].condition);
            found = 1;
        }
    }

    if (!found) {
        printf("No matching asset found.\n");
    }
}

void assetMenu(void)
{
    int choice;

    do {
        printf("\n========================================\n");
        printf("           ASSET MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add Asset\n");
        printf("2. Display Assets\n");
        printf("3. Search Asset\n");
        printf("4. Return to Main Menu\n");

        choice = readIntSafely("Enter choice: ");

        switch (choice) {
            case 1:
                addAsset();
                break;
            case 2:
                displayAssets();
                break;
            case 3:
                searchAsset();
                break;
            case 4:
                break;
            default:
                printf("Invalid choice. Please select 1 to 4.\n");
        }
    } while (choice != 4);
}

void assetReport(void)
{
    displayAssets();
}
