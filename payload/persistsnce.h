#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#ifdef __cplusplus
extern "C" {
#endif

void persist(const char *path);

#ifdef __cplusplus
}
#endif

#endif 
/*
#include <windows.h>
#include "persistence.h"

int main() {
    const char *exePath = "<path you want to persist>"";
    // Call persist to add a Run registry key for startup persistence
    persist(exePath);
    return 0;
}
*/