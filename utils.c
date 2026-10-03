#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include "utils.h"

static void discardRestOfLine(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* discard */
    }
}

void readLine(const char *prompt, char *buffer, int size)
{
    if (prompt != NULL) {
        printf("%s", prompt);
    }

    if (fgets(buffer, size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }

    if (strchr(buffer, '\n') != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    } else {
        discardRestOfLine();
    }
}

void readNonEmptyLine(const char *prompt, char *buffer, int size)
{
    do {
        readLine(prompt, buffer, size);
        if (buffer[0] == '\0') {
            printf("Input cannot be empty. Please try again.\n");
        }
    } while (buffer[0] == '\0');
}

int readIntSafely(const char *prompt)
{
    char buffer[100];
    char *end;
    long value;

    for (;;) {
        readLine(prompt, buffer, sizeof(buffer));
        errno = 0;
        end = NULL;
        value = strtol(buffer, &end, 10);

        while (end != NULL && (*end == ' ' || *end == '\t')) {
            end++;
        }

        if (buffer[0] != '\0' && end != buffer && *end == '\0' &&
            errno != ERANGE && value >= INT_MIN && value <= INT_MAX) {
            return (int)value;
        }

        printf("Invalid number. Please enter a whole number.\n");
    }
}

double readDoubleSafely(const char *prompt)
{
    char buffer[100];
    char *end;
    double value;

    for (;;) {
        readLine(prompt, buffer, sizeof(buffer));
        errno = 0;
        end = NULL;
        value = strtod(buffer, &end);

        while (end != NULL && (*end == ' ' || *end == '\t')) {
            end++;
        }

        if (buffer[0] != '\0' && end != buffer && *end == '\0' &&
            errno != ERANGE && isfinite(value)) {
            return value;
        }

        printf("Invalid number. Please enter a numeric value.\n");
    }
}
