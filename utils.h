#ifndef UTILS_H
#define UTILS_H

int readIntSafely(const char *prompt);
double readDoubleSafely(const char *prompt);
void readLine(const char *prompt, char *buffer, int size);
void readNonEmptyLine(const char *prompt, char *buffer, int size);

#endif
